#include "Game.hpp"
#include "Shader.hpp"

Game::Game() : isRunning(true), VBO(0), time(0) {
	std::cout << "Init Game" << std::endl;

	//PARTICLE EMITTER
<<<<<<< HEAD
	PE = ParticleEmitter(glm::vec2(0), NUMPARTICLES, 100);
=======
    PE = ParticleEmitter(glm::vec2(0), 2.0f, 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));
    angle = 0.0f;
>>>>>>> 41af60fc07fc3937c8a42c6601225a9b70d46c73

	FPS = timeFPS = 0;

	window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "test", sf::Style::Default, sf::ContextSettings(32, 32, 0, 4, 2));
	glClearColor(0,0,0,1);

	std::cout << "Init Succesful" << std::endl;
}


struct Vertex {
        Vertex(float px, float py)
            : px(px), py(py) {}
        ~Vertex() {}
        float px, py;
};

bool Game::init() {
	std::string vp_filename("shaders/Test.vert"), fp_filename("shaders/Test.frag");
	//LOAD AND COMPILE VERTEX SHADER
	std::cout << "* Loading new vertex shader from " << vp_filename << std::endl;;
	Shader vertex(GL_VERTEX_SHADER);
	vertex.load(vp_filename);
	if (!vertex.compile()) {
        vertex.printInfoLog();
		std::cout << "#ERROR Compile failed for vertex shader '" << vp_filename << "'." << std::endl;;
		return false;
	}
	else std::cout << " - Compiled " << vp_filename << " successfully." << std::endl;;

	//LOAD AND COMPILE FRAGMENT SHADER
	std::cout << "* Loading new fragment shader from " << fp_filename << std::endl;;
	Shader fragment(GL_FRAGMENT_SHADER);
	fragment.load(fp_filename);
	if (!fragment.compile()) {
		fragment.printInfoLog();
		std::cout << "#ERROR Compile failed for fragment shader '" << fp_filename << "'." << std::endl;
		return false;
	}
	else std::cout <<  " - Compiled " << fp_filename << " successfully." << std::endl;

	//CREATE THE PROGRAM
	std::cout << "* Creating new shaderProgram with " << vp_filename << " and " << fp_filename << std::endl;
	programHandle = glCreateProgram();

	//ATTACH AND LINK
	vertex.attach(programHandle);
	fragment.attach(programHandle);
	glLinkProgram(programHandle);

	glGenBuffers(1, &VBO);
	glUseProgram(programHandle);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Simple quad
    std::vector<Vertex> data;
    data.push_back( Vertex(-1, 1) );
    data.push_back( Vertex(-1, -1) );
    data.push_back( Vertex(1, -1) );

    data.push_back( Vertex(-1, 1) );
    data.push_back( Vertex(1, -1) );
    data.push_back( Vertex(1, 1) );

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*data.size(), &data[0], GL_STATIC_DRAW);
    return true;
}

void Game::run() {
	sf::Clock clock;
	while(isRunning) {
        float dt = clock.restart().asSeconds();
        time += dt;
        update(dt);
        draw();
	}
}

void Game::update(float dt) {

	++FPS;
	timeFPS += dt;
	if (timeFPS >= 1.0f) {
		std::stringstream ss;
		ss << "FPS: " << FPS;
		window.setTitle(ss.str());
		timeFPS = FPS = 0;
	}


    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                isRunning = false;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R) REPULSION = !REPULSION;
                else if (event.key.code == sf::Keyboard::G) GRAVITY = !GRAVITY;
				else if (event.key.code == sf::Keyboard::Escape) isRunning = false;
                break;
			case sf::Event::MouseButtonPressed:
				if (event.key.code == sf::Mouse::Left) PE.explosion();
				else if (event.key.code == sf::Mouse::Right) PE.clear();
				break;
			case sf::Event::Resized:
				SCREENWIDTH = window.getSize().x;
				SCREENHEIGHT = window.getSize().y;
				glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
				break;
        }
    }

	sf::Vector2i mpos = mouse.getPosition(window);
	mousepos = glm::vec2(
                (float(mpos.x)/float(SCREENWIDTH)-0.5)*2,
                (float(-mpos.y)/float(SCREENHEIGHT)+0.5)*2
                );

	//PARTICLE EMITTER
	PE.setPosition(mousepos);
    PE.update(dt, mousepos);

    //ANGLE
    angle += 2*3.1416f*dt*20;

}

void Game::draw() {
	window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programHandle);

    GLuint loc = glGetUniformLocation(programHandle, std::string("modelViewProjectionMatrix").c_str());
    GLuint alphaLoc = glGetUniformLocation(programHandle, std::string("alpha").c_str());
    GLuint timeLoc = glGetUniformLocation(programHandle, std::string("time").c_str());
    GLuint colorLoc = glGetUniformLocation(programHandle, std::string("color").c_str());

    glUniform1f(timeLoc, time);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Particle draw
    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans, glm::vec3(0, 0, CAMZ));
    //trans = glm::rotate(trans, angle, glm::vec3(0, 0, 0));

    PE.draw(loc, trans, colorLoc, alphaLoc);

	glDisableVertexAttribArray(0);

	window.display();
}
