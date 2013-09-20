#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Tools.hpp"

class Particle
{
private:
    glm::vec3 pos;
    glm::vec3 vel;
    float life;

public:
    Particle();
    ~Particle();
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, sf::Vector2f mpos);
    void update(float dt, sf::Vector2f mpos);
    bool isDead();
};

#endif // PARTICLE_HPP
