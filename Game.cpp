#include "Game.hpp"
#include "Shader.hpp"

Game::Game() : isRunning(true), VBO(0), angle(0), time(0) {
	std::cout << "Init Game" << std::endl;
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
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
        std::cout << "time: " << time << std::endl;
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
            default:
                break;
        }
    }
	angle += dt*100;
}

void Game::draw() {
	window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans,glm::vec3(0,0,-1));
    //trans = glm::rotate(trans, angle, glm::detail::tvec3<float>(0, 0, 1));
	glUseProgram(programHandle);
//    GLint loc = glGetUniformLocation(programHandle, std::string("modelViewProjectionMatrix").c_str());
//    glUniformMatrix4fv(loc,1,GL_FALSE,(GLfloat*)&trans[0][0]);

    GLint timeLoc = glGetUniformLocation(programHandle, std::string("time").c_str());
    glUniform1f(timeLoc, time);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3*sizeof(float)));
    glDrawArrays(GL_TRIANGLES,0,6);
    //glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	window.display();
}
