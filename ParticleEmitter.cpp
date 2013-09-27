#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter() {
    pos = glm::vec2(0.0f, 0.0f);
    frequency = 10;
    life = NUMPARTICLES/frequency;
    for (int i = 0; i < NUMPARTICLES; ++i) particlesList.push_back(Particle(pos, glm::vec2(frand(-1.0f, 1.0f), frand(-1.0f, 1.0f)), i*life/NUMPARTICLES));
}

ParticleEmitter::ParticleEmitter(glm::vec2 pos, float frequency) {
    this->pos = pos;
    this->frequency = frequency;
}

void ParticleEmitter::setPosition(glm::vec2 pos) {
    this->pos = pos;
}

void ParticleEmitter::setPosition(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
}

const glm::vec2 ParticleEmitter::getPosition() const { return pos;}

void ParticleEmitter::update(float dt, sf::Vector2f mpos) {
    for (std::list<Particle>::iterator it = particlesList.begin(); it != particlesList.end();) {
        std::list<Particle>::iterator it2 = it;
        it2++;
        if (it->isDead()) {
            particlesList.erase(it);
            particlesList.push_back(Particle(pos, glm::vec2(frand(-1.0f, 1.0f), frand(-1.0f, 1.0f)), life));
        }
        else it->update(dt, mpos);
        it = it2;
    }
}

void ParticleEmitter::draw(GLuint location, glm::detail::tmat4x4<float> &trans, sf::Vector2f mpos, GLuint alphaLoc) const {
    for (std::list<Particle>::const_iterator it = particlesList.begin(); it != particlesList.end(); ++it)
        it->draw(location, trans, mpos, alphaLoc);
}

