
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

    GLuint VBO;
	float time;
    GLuint programHandle;

	sf::Clock clock;
	glm::detail::tmat4x4<float> trans;

    ParticleEmitter PE;

	int FPS;
	float timeFPS;

    float angle;

    sf::Mouse mouse;
	glm::vec2 mousepos;
};

#endif // GAME_HPP
