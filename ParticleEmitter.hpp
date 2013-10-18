#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Tools.hpp"
#include "Particle.hpp"

class ParticleEmitter {
private:
    glm::vec2 pos;
	glm::vec2 vel;
    float life;
    float frequency;
    glm::vec3 initColor;
    glm::vec3 finalColor;
	float initSize;
	float finalSize;
	float initAlpha;
	float finalAlpha;

	float spawnTime;
    float angle;
    float angleStep;
    std::list<Particle> particlesList;
    glm::vec2 oldPos;

    bool hit;

	void emitParticle(glm::vec2 pos, glm::vec2 vel, float life);
    void emitParticle(glm::vec2 pos, glm::vec2 vel, float life, float initSize, float finalSize, float initAlpha, float finalAlpha, glm::vec3 initColor, glm::vec3 finalColor);
	void emitParticle(const Particle &p);

public:
	ParticleEmitter(glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec2 vel = glm::vec2(0.0f, 0.0f), float life = 1.0f, float frequency = 1.0f, glm::vec3 initColor=glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 finalColor=glm::vec3(1.0f, 1.0f, 1.0f));
    ParticleEmitter(glm::vec2 pos, float frequency);

    const glm::vec2 getPos() const;
    const glm::vec2 getVel() const;

    void setPosition(glm::vec2 pos);
    void setPosition(float x, float y);
    void setColor(glm::vec3 initColor, glm::vec3 finalColor);
	void setSize(float initSize, float finalSize);
    void setVel(glm::vec2 vel);


	void update(float dt, glm::vec2 mpos);
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, GLuint colorLoc, GLuint alphaLoc) const;

	void explosion();
	void clear();
};

#endif // PARTICLEEMITTER_HPP
