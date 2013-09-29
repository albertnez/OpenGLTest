#include "Game.hpp"
#include "Shader.hpp"

Game::Game() : isRunning(true), VBO(0), time(0) {
	std::cout << "Init Game" << std::endl;

    //PARTICLES
	PE = ParticleEmitter(glm::vec2(0), NUMPARTICLES, 10);



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

	//modelViewProjection = glm::rotate(modelViewProjection, 10.0f, glm::vec3(0,1,0));

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

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
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                isRunning = false;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R) REPULSION = !REPULSION;
                if (event.key.code == sf::Keyboard::Escape) isRunning = false;
                break;
        }
    }
	sf::Vector2i mpos = mouse.getPosition(window);
	mousepos = glm::vec2(
                (float(mpos.x)/float(SCREENWIDTH)-0.5)*2,
                (float(-mpos.y)/float(SCREENHEIGHT)+0.5)*2
                );


    //PARTICLE EMITER

    PE.setPosition(mousepos.x, mousepos.y);
    PE.update(dt, mousepos);

}

void Game::draw() {
	window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programHandle);

    GLint loc = glGetUniformLocation(programHandle, std::string("modelViewProjectionMatrix").c_str());
    GLint alphaLoc = glGetUniformLocation(programHandle, std::string("alpha").c_str());
    GLint timeLoc = glGetUniformLocation(programHandle, std::string("time").c_str());
    GLint mouseLoc = glGetUniformLocation(programHandle, std::string("mousePosition").c_str());
    glUniform1f(timeLoc, time);
    glUniform2f (mouseLoc, mousepos.x, mousepos.y);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    // Particle draw
    PE.draw(loc, trans, mousepos, alphaLoc);

    //glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
}
