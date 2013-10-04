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
    Particle(glm::vec2 pos, glm::vec2 vel);
    Particle(glm::vec2 pos, glm::vec2 vel, float initLife, glm::vec3 initColor, glm::vec3 finalColor);
    Particle(glm::vec2 pos, glm::vec2 vel, float initLife, float initSize, float finalSize, float initAlpha, float finalAlpha, glm::vec3 initColor, glm::vec3 finalColor);
    ~Particle();
    void setPos(glm::vec2 pos);
    void setVel(glm::vec2 vel);
    void setSize(float initSize, float finalSize);
    void setColor(glm::vec3  initColor, glm::vec3 finalColor);
    void setAlpha(float initAlpha, float finalAlpha);
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, GLuint colorLoc, GLuint alphaLoc) const;
    void update(float dt, glm::vec2 mpos);
    bool isDead() const;
};

#endif // PARTICLE_HPP
