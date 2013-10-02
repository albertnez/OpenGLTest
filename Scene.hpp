#ifndef SCENE_HPP
#define SCENE_HPP

#include "Tools.hpp"
#include "ParticleEmitter.hpp"
#include "Shader.hpp"

class Game;
class Scene
{
public:
    Scene(Game &parent);
    bool init();
    void update(float dt);
    void draw();
private:
	Game& parent;


    GLuint VBO;
    GLuint programHandle;

	float time;

    glm::detail::tmat4x4<float> trans;

    ParticleEmitter PE;

    sf::Mouse mouse;
    glm::vec2 mousepos;
};

#endif // SCENE_HPP
