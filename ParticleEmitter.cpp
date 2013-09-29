#include "ParticleEmitter.hpp"


ParticleEmitter::ParticleEmitter(glm::vec2 pos, int numParticles, float frequency) {
    pos = glm::vec2(0.0f, 0.0f);
	this->numParticles = numParticles;
	this->frequency = frequency;
	life = float(numParticles)/frequency;

	spawnTime = 0;

//	for (int i = 0; i < numParticles; ++i)
//		particlesList.push_back( Particle(
//									 pos,
//									 glm::vec2(frand(-1.0f, 1.0f),frand(-1.0f, 1.0f)),
//									 life * (i/float(numParticles))
//									 ));
}

ParticleEmitter::ParticleEmitter(glm::vec2 pos, float frequency) {
    this->pos = pos;
    this->frequency = frequency;
}

void ParticleEmitter::emitParticle(glm::vec2 pos, glm::vec2 vel, float life)
{
	particlesList.push_back( Particle(pos, vel, life));
}

void ParticleEmitter::explosion()
{
	float angleStep = 360.0f/numParticles;
	for (float a = 0; a <= 360.0f; a += angleStep) {
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
        if (it->isDead()) {
            particlesList.erase(it);
		   // particlesList.push_back(Particle(pos, glm::vec2(frand(-1.0f, 1.0f), frand(-1.0f, 1.0f)), life));
        }
        else it->update(dt, mpos);
        it = it2;
    }
	if (dt > spawnTime) {
		while (dt > 0) {
			dt -= spawnTime;
			emitParticle(pos, glm::vec2(frand(-1.0f, 1.0f), frand(-1.0f, 1.0f)), life-dt);
			spawnTime = 1.0f/frequency;

		}
	}
	else spawnTime -= dt;
}

void ParticleEmitter::draw(GLuint location, glm::detail::tmat4x4<float> &trans, glm::vec2 mpos, GLuint alphaLoc) const {
    for (std::list<Particle>::const_iterator it = particlesList.begin(); it != particlesList.end(); ++it)
        it->draw(location, trans, mpos, alphaLoc);
}

