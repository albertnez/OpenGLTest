#ifndef GAME_HPP
#define GAME_HPP

#include "Tools.hpp"
struct Vertex {
		Vertex(float px, float py, float pz, float cr, float cg, float cb)
			: px(px), py(py), pz(pz), cr(cr), cg(cg), cb(cb) {}
		~Vertex() {}
		float px, py, pz;
		float cr, cg, cb;
};
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
    GLuint programHandle;

};

#endif // GAME_HPP
