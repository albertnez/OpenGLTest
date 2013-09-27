#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Tools.hpp"
#include "Particle.hpp"

class ParticleEmitter {
private:
    float frequency;
    float life;
    glm::vec2 pos;
    std::list<Particle> particlesList;

public:
    ParticleEmitter();
    ParticleEmitter(glm::vec2 pos, float frequency);

    void setPosition(glm::vec2 pos);
    void setPosition(float x, float y);
    const glm::vec2 getPosition() const;

    void update(float dt, sf::Vector2f mpos);
    void draw(GLuint location, glm::detail::tmat4x4<float> & trans, sf::Vector2f mpos, GLuint alphaLoc) const;
};

#endif // PARTICLEEMITTER_HPP
