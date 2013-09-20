#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Tools.hpp"

class Particle
{
private:
    glm::vec3 pos;
    glm::vec3 vel;

public:
    Particle();
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans);
    void update(float dt, sf::Vector2f mpos);
};

#endif // PARTICLE_HPP
