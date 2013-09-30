#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Tools.hpp"

class Particle
{
private:
	glm::vec2 pos;
	glm::vec2 vel;
    glm::vec3 initColor, finalColor;
    float life;
	const static float maxVel = 1.0f;

    float initSize, finalSize;
    float initAlpha, finalAlpha;
    float initLife;

public:
    Particle();
    Particle(glm::vec2 pos, glm::vec2 vel, float initLife, glm::vec3 initColor=glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 finalColor=glm::vec3(0.0f, 0.0f, 0.0f));
    ~Particle();
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, GLuint colorLoc, GLuint alphaLoc) const;
    void update(float dt, glm::vec2 mpos);
    bool isDead() const;
};

#endif // PARTICLE_HPP
