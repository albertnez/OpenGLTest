#ifndef GAME_HPP
#define GAME_HPP

#include "Tools.hpp"

class Game
{
  public:
    Game();
    bool init();
    void run();
   private:
    void update(float dt);
    void draw();

	float angle;
    float time;

    sf::RenderWindow window;
    bool isRunning;

    GLuint VBO;
    GLuint programHandle;
	sf::Clock clock;
	glm::detail::tmat4x4<float> trans;
};

#endif // GAME_HPP
