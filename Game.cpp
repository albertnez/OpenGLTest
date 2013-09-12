#include "Game.hpp"
#include "Shader.hpp"

Game::Game() : isRunning(true), VBO(0) {
	std::cout << "Init Game" << std::endl;
	window.create(sf::VideoMode(600, 400), "test", sf::Style::Default, sf::ContextSettings(32, 32, 0, 4, 2));
	glClearColor(0,0,0,1);
	std::cout << "Init Succesful" << std::endl;
}

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
	glm::detail::tmat4x4<float> modelViewProjection = glm::perspective(60.0f,600.0f/400.0f,0.001f,1000.0f);

	GLint loc = glGetUniformLocation(programHandle, std::string("modelViewProjectionMatrix").c_str());
	glUniformMatrix4fv(0,1,GL_FALSE,(GLfloat*)&modelViewProjection[0][0]);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<Vertex> data;
	data.push_back( Vertex(-1, -1, -2, 0, 0, 1) );
	data.push_back( Vertex(1, -1, -2, 0, 1, 0) );
	data.push_back( Vertex(0, 1, -2, 1, 0, 0) );

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*data.size(), &data[0], GL_STATIC_DRAW);
	return true;
}

void Game::run() {
	sf::Clock clock;
	while(isRunning) {
		float dt = clock.restart().asSeconds();
		update(dt);
		draw();
	}
}

void Game::update(float dt) {}

void Game::draw() {
	window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3*sizeof(float)));
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	window.display();
}

