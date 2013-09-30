#include "ParticleEmitter.hpp"


ParticleEmitter::ParticleEmitter(glm::vec2 pos, float life, float frequency, glm::vec3 initColor, glm::vec3 finalColor) :
    pos(pos),
    life(life),
    frequency(frequency),
    initColor(initColor),
    finalColor(finalColor),
    spawnTime(0),
    angle(0),
    angleStep(2*M_PI/frequency),
    oldPos(pos)
{
}

ParticleEmitter::ParticleEmitter(glm::vec2 pos, float frequency) :
    pos(pos),
    frequency(frequency) {
}

void ParticleEmitter::emitParticle(glm::vec2 pos, glm::vec2 vel, float life)
{
    particlesList.push_back( Particle(pos, vel, life, initColor, finalColor));
}

void ParticleEmitter::explosion()
{
    //float angleStep = 360.0f/numParticles;
    for (float a = 0; a <= 2*M_PI; a += angleStep) {
        emitParticle(pos, glm::vec2(sin(a), cos(a)), life);
	}
}

void ParticleEmitter::clear()
{
	particlesList.clear();
	spawnTime = 1.0/frequency;
}

void ParticleEmitter::setPosition(glm::vec2 pos) {
    this->pos = pos;
}

void ParticleEmitter::setPosition(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
}

const glm::vec2 ParticleEmitter::getPosition() const { return pos;}

void ParticleEmitter::update(float dt, glm::vec2 mpos) {
    for (std::list<Particle>::iterator it = particlesList.begin(); it != particlesList.end();) {
        std::list<Particle>::iterator it2 = it;
        it2++;
        if (it->isDead())
            particlesList.erase(it);
        else it->update(dt, mpos);
        it = it2;
    }

    if (pos == oldPos) std::cout << "pos = oldPos" << std::endl;
    else std::cout << " ~~~~pos != oldPos" << std::endl;


	if (dt > spawnTime) {
//        std::cout << oldPos.x << " " << pos.x << std::endl;
        float totalDt = dt;
		while (dt > 0) {
            glm::vec2 interpolatePos = oldPos + (1-dt/totalDt) * (pos-oldPos);
            dt -= spawnTime;
            emitParticle(interpolatePos, glm::vec2(sin(angle),cos(angle)), life-dt);
//            emitParticle(pos, glm::vec2(sin(angle),cos(angle)), life-dt);
            angle += angleStep;

			spawnTime = 1.0f/frequency;

		}
	}
	else spawnTime -= dt;

    oldPos = pos;
}

void ParticleEmitter::draw(GLuint location, glm::detail::tmat4x4<float> &trans, GLuint colorLoc, GLuint alphaLoc) const {
    for (std::list<Particle>::const_iterator it = particlesList.begin(); it != particlesList.end(); ++it)
        it->draw(location, trans, colorLoc, alphaLoc);
}

