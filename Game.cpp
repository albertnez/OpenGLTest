#include "Game.hpp"
#include "Shader.hpp"

Game::Game() : isRunning(true), VBO(0), time(0) {
	std::cout << "Init Game" << std::endl;

	//PARTICLE EMITTER

    PE = ParticleEmitter(glm::vec2(0), glm::vec2(frand(1), frand(1))*5.0f, 0.5f, 200.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));

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

bool Game::init()
{
}

void Game::run()
{
	sf::Clock clock;
	while(isRunning) {
        float dt = clock.restart().asSeconds();
        time += dt;
        update(dt);
        draw();
	}
}

void Game::update(float dt)
{

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
	//PE.setPosition(mousepos);
    PE.update(dt, mousepos);

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
