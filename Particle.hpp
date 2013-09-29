#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Tools.hpp"

class Particle
{
private:
	glm::vec2 pos;
	glm::vec2 vel;
    float life;
	const static float maxVel = 1.0f;

    float initSize, finalSize;
    float initAlpha, finalAlpha;
    float initLife;

public:
    Particle();
    Particle(glm::vec2 pos, glm::vec2 vel, float initLife);
    ~Particle();
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, glm::vec2 mpos, GLuint alphaLoc) const;
    void update(float dt, glm::vec2 mpos);
    bool isDead() const;
};

#endif // PARTICLE_HPP
