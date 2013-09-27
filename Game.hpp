#ifndef GAME_HPP
#define GAME_HPP

#include "Tools.hpp"
#include "Particle.hpp"
class Game
{
  public:
    Game();
    bool init();
    void run();
   private:
    void update(float dt);
    void draw();

    float time;

    sf::RenderWindow window;
    bool isRunning;

    GLuint VBO;
    GLuint programHandle;
	sf::Clock clock;
	glm::detail::tmat4x4<float> trans;

    std::list<Particle> particles;

    sf::Mouse mouse;
    sf::Vector2f mousepos;
};

#endif // GAME_HPP
