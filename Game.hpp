
#ifndef GAME_HPP
#define GAME_HPP

#include "Tools.hpp"
#include "Particle.hpp"
#include "ParticleEmitter.hpp"
#include "Scene.hpp"

class Game
{
  public:
	Game();
    bool init();
	void setScene(Scene * scene);
    void run();
	void close();

	sf::RenderWindow& getWindow();
   private:

    void update(float dt);
    void draw();


    sf::RenderWindow window;
    bool isRunning;

    Scene * scene;


	sf::Clock clock;

	int FPS;
	float timeFPS;
};

#endif // GAME_HPP
