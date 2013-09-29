#include "Particle.hpp"

Particle::Particle()
{
	pos = glm::vec2( frand(-1, 1), frand(-1, 1));
	vel = glm::vec2( frand(-1, 1), frand(-1, 1));


    initSize = 0.01, finalSize = 0.1;
    initAlpha = 1, finalAlpha = 0.0f;

    //life = initLife = frand(1, 10);
    initLife = life = frand(10);
}

Particle::Particle(glm::vec2 pos, glm::vec2 vel, float initLife)
{

    this->pos = pos;
    this->vel = vel;
    this->initLife = this->life = initLife;
    initSize = 0.01f, finalSize = 0.1f;
    initAlpha = 1.0f, finalAlpha = 0.0f;
}

Particle::~Particle(){}

void Particle::update(float dt, glm::vec2 mpos) {
    if (pos.x != mpos.x and pos.y != mpos.y and REPULSION) {
        float dist = module(pos.x-mpos.x, pos.y-mpos.y);
        glm::vec2 uvect = glm::vec2(pos.x-mpos.x, pos.y-mpos.y)/dist;
        glm::vec2 force = uvect / (dist*dist);


        vel += force*dt;
        if (module(vel) > maxVel) vel = uvect * maxVel;
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
        vel.y *= -1;
        pos.y = -1 + (-1 -pos.y);
    }
    else if (pos.y > 1) {
        vel.y *= -1;
        pos.y = 1 - (pos.y -1);
    }

    //LIFE UPDATE
    life = std::max(0.0f, life-dt);
}

void Particle::draw(GLuint location, glm::detail::tmat4x4<float> & trans, glm::vec2 mpos, GLuint alphaLoc) const{

    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans, glm::vec3(0, 0, CAMZ));
	trans = glm::translate(trans, glm::vec3(pos, 0));

	//SCALE PARTICLES
    float scale = initSize + (1-life/initLife)*(finalSize-initSize);
    float alpha = initAlpha + (1-life/initLife)*(finalAlpha-initAlpha);


	trans = glm::scale(trans, glm::vec3(scale, scale, 0));
    glUniformMatrix4fv(location,1,GL_FALSE,(GLfloat*)&trans[0][0]);
    glUniform1f(alphaLoc, alpha);
    glDrawArrays(GL_TRIANGLES,0,6);
}

bool Particle::isDead() const {
    return life <= 0.0f;
}
