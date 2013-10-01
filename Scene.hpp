#ifndef SCENE_HPP
#define SCENE_HPP

#include "Tools.hpp"
#include "ParticleEmitter.hpp"

class Scene
{
public:
    Scene();
    void update(float dt);
    void draw();
private:

    GLuint VBO;
    GLuint programHandle;

    glm::detail::tmat4x4<float> trans;

    ParticleEmitter PE;

    sf::Mouse mouse;
    glm::vec2 mousepos;
};

#endif // SCENE_HPP
