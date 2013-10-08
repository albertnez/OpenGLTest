#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(glm::vec2 pos, glm::vec2 vel, float life, float frequency, glm::vec3 initColor, glm::vec3 finalColor) :
	pos(pos),
	vel(vel),
	life(life),
	frequency(frequency),
	initColor(initColor),
	finalColor(finalColor),
	initSize(0.02f),
	finalSize(0.1f),
	initAlpha(1.0f),
	finalAlpha(0.05f),
	spawnTime(0),
	angle(0),
    angleStep(2*M_PI/frequency),
    oldPos(pos),
    hit(false)
{
}

ParticleEmitter::ParticleEmitter(glm::vec2 pos, float frequency) :
    pos(pos),
    frequency(frequency),
    hit(false)
{
}

void ParticleEmitter::emitParticle(glm::vec2 pos, glm::vec2 vel, float life)
{
	particlesList.push_back( Particle(pos, vel, life, initSize, finalSize, initAlpha, finalAlpha, initColor, finalColor));
}

void ParticleEmitter::emitParticle(glm::vec2 pos, glm::vec2 vel, float life, float initSize, float finalSize, float initAlpha, float finalAlpha, glm::vec3 initColor, glm::vec3 finalColor)
{
    particlesList.push_back(Particle(pos, vel, life, initSize, finalSize, initAlpha, finalAlpha, initColor, finalColor));
}

void ParticleEmitter::explosion()
{
    for (float a = 0; a <= 2*M_PI; a += angleStep) {
		emitParticle(pos, glm::vec2(sin(a), cos(a)), 0.3f, 0.1f, 0.01f, 0.1f, 0.1f, initColor, finalColor);
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

void ParticleEmitter::setColor(glm::vec3 initColor, glm::vec3 finalColor)
{
    this->initColor = initColor;
	this->finalColor = finalColor;
}

void ParticleEmitter::setSize(float initSize, float finalSize)
{
	this->initSize = initSize;
	this->finalSize = finalSize;
}

void ParticleEmitter::update(float dt, glm::vec2 mpos) {
    for (std::list<Particle>::iterator it = particlesList.begin(); it != particlesList.end();) {
        std::list<Particle>::iterator it2 = it;
        it2++;
        if (it->isDead())
            particlesList.erase(it);
        else it->update(dt, mpos);
        it = it2;
    }

    pos += vel*dt;
	if (pos.x < -1) {
		vel.x *= -1;
		pos.x = -1 + (-1 -pos.x);
        explosion();
	}
	else if (pos.x > 1) {
		vel.x *= -1;
		pos.x = 1 - (pos.x -1);
        explosion();
	}
	if (pos.y < -1) {
		vel.y *= -1;
		pos.y = -1 + (-1 -pos.y);
        explosion();
	}
	else if (pos.y > 1) {
		vel.y *= -1;
		pos.y = 1 - (pos.y -1);
        explosion();
	}

    //collision with mouse
    if (module(pos.x-mpos.x,pos.y-mpos.y) < 0.08) {
        if (!hit) {
            hit = true;
            explosion();
            setColor(1.0f-initColor, 1.0f-finalColor);
        }
    }
    else {
        hit = false;
    }

	if (dt > spawnTime) {
        float totalDt = dt;
		while (dt > 0) {
            glm::vec2 interpolatePos = oldPos + (1-dt/totalDt) * (pos-oldPos);
            dt -= spawnTime;
			emitParticle(interpolatePos, glm::vec2(0.0f, 0.0f), life-dt);
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

