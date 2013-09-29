#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Tools.hpp"
#include "Particle.hpp"

class ParticleEmitter {
private:
    float frequency;
    float life;
	int numParticles;
    glm::vec2 pos;
    std::list<Particle> particlesList;

public:
	ParticleEmitter(glm::vec2 pos = glm::vec2(0.0f, 0.0f), int numParticles = NUMPARTICLES, float frequency = 1.0f);
    ParticleEmitter(glm::vec2 pos, float frequency);

    void setPosition(glm::vec2 pos);
    void setPosition(float x, float y);
    const glm::vec2 getPosition() const;

	void update(float dt, glm::vec2 mpos);
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, glm::vec2 mpos, GLuint alphaLoc) const;
};

#endif // PARTICLEEMITTER_HPP
