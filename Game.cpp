#include "Game.hpp"

Game::Game() : isRunning(true) {
	std::cout << "Init Game" << std::endl;

	//PARTICLE EMITTER
	FPS = timeFPS = 0;

	window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "test", sf::Style::Default, sf::ContextSettings(32, 32, 0, 4, 2));
	glClearColor(0,0,0,1);

	std::cout << "Init Succesful" << std::endl;
}


bool Game::init()
{
}

void Game::setScene(Scene *scene)
{
	this->scene = scene;
	this->scene->init();
}

void Game::run()
{
	sf::Clock clock;
	while(isRunning) {
        float dt = clock.restart().asSeconds();
        update(dt);
        draw();
	}
}

void Game::close()
{
//	scene->close();  // No need for this
	delete scene;
	isRunning = false;
}

sf::RenderWindow &Game::getWindow()
{
	return window;
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

	if (scene != NULL)
		scene->update(dt);
}

void Game::draw() {
	window.clear();

	if (scene != NULL)
		scene->draw();

	window.display();
}
