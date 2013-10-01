
#ifndef GAME_HPP
#define GAME_HPP

#include "Tools.hpp"
#include "Particle.hpp"
#include "ParticleEmitter.hpp"

class Game
{
  public:
    Game();
    bool init();
    void run();
   private:

    void update(float dt);
    void draw();


    sf::RenderWindow window;
    bool isRunning;



	sf::Clock clock;

    float time;

	int FPS;
	float timeFPS;
};

#endif // GAME_HPP
