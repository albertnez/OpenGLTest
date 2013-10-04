#include "Particle.hpp"

Particle::Particle()
{
    pos = glm::vec2( frand(-1.0f, 1.0f), frand(-1.0f, 1.0f));
    vel = glm::vec2( frand(-1.0f, 1.0f), frand(-1.0f, 1.0f));

    initColor = glm::vec3(0.0f, 0.0f,1.0f);
    finalColor = glm::vec3(0.0f, 1.0f, 0.0f);

    initSize = 0.01, finalSize = 0.1;
    initAlpha = 0.1f, finalAlpha = 0.0f;

    initLife = life = frand(10);
}

Particle::Particle(glm::vec2 pos, glm::vec2 vel, float initLife, glm::vec3 initColor, glm::vec3 finalColor) :
    pos(pos),
    vel(vel),
    initLife(initLife),
    life(initLife),
    initColor(initColor),
    finalColor(finalColor),
    initSize(0.05f),
	finalSize(0.1f),
    initAlpha(0.05f),
    finalAlpha(1.0f) {
}

Particle::Particle(glm::vec2 pos, glm::vec2 vel, float initLife, float initSize, float finalSize, float initAlpha, float finalAlpha, glm::vec3 initColor, glm::vec3 finalColor) :
    pos(pos),
    vel(vel),
    initLife(initLife),
    life(initLife),
    initSize(initSize),
    finalSize(finalSize),
    initAlpha(initAlpha),
    finalAlpha(finalAlpha),
    initColor(initColor),
    finalColor(finalColor)
{

}

Particle::~Particle(){}

void Particle::setPos(glm::vec2 pos)
{
    this->pos = pos;
}

void Particle::setVel(glm::vec2 vel)
{
    this->vel = vel;
}

void Particle::setSize(float initSize, float finalSize)
{
    this->initSize = initSize;
    this->finalSize = finalSize;
}

void Particle::setColor(glm::vec3 initColor, glm::vec3 finalColor)
{
    this->initColor = initColor;
    this->finalColor = finalColor;
}

void Particle::setAlpha(float initAlpha, float finalAlpha)
{
    this->initAlpha = initAlpha;
    this->finalAlpha = finalAlpha;
}

void Particle::update(float dt, glm::vec2 mpos) {

    if (REPULSION) {
        if (pos.x != mpos.x and pos.y != mpos.y) {
            float dist = module(pos.x-mpos.x, pos.y-mpos.y);
            glm::vec2 uvect = glm::vec2(pos.x-mpos.x, pos.y-mpos.y)/dist;
            glm::vec2 force = uvect / (dist*dist);
            vel += force*dt;
            //if (module(vel) > maxVel) vel = uvect * maxVel;
        }
    }


    if (GRAVITY) {
        vel.y -= dt*5;
    }

	pos += vel*dt;

    if (pos.x < -1) {
        vel.x *= -1;
        pos.x = -1 + (-1 -pos.x);
    }
    else if (pos.x > 1) {
        vel.x *= -1;
        pos.x = 1 - (pos.x -1);
    }
    if (pos.y < -1) {
        vel.y *= -0.9;
        pos.y = -1 + (-1 -pos.y);
    }
    else if (pos.y > 1) {
        vel.y *= -1;
        pos.y = 1 - (pos.y -1);
    }

    //LIFE UPDATE
    life = std::max(0.0f, life-dt);
}

void Particle::draw(GLuint location, glm::detail::tmat4x4<float> & trans, GLuint colorLoc, GLuint alphaLoc) const{

    //COPY MATRIX TEST
    glm::detail::tmat4x4<float> copy = trans;

	trans = glm::translate(trans, glm::vec3(pos, 0));

	//SCALE PARTICLES
    float scale = initSize + (1-life/initLife)*(finalSize-initSize);
    float alpha = initAlpha + (1-life/initLife)*(finalAlpha-initAlpha);
    glm::vec3 color = initColor + (1-life/initLife)*(finalColor-initColor);

	trans = glm::scale(trans, glm::vec3(scale, scale, 0));
    glUniformMatrix4fv(location,1,GL_FALSE,(GLfloat*)&trans[0][0]);
    glUniform3f(colorLoc, color.x, color.y, color.z);

    glUniform1f(alphaLoc, alpha);
    glDrawArrays(GL_TRIANGLES,0,6);

    //Backup trans
    trans = copy;
}

bool Particle::isDead() const {
    return life <= 0.0f;
}
