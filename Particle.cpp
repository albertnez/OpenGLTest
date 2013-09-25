#include "Particle.hpp"

Particle::Particle()
{
	pos = glm::vec3( frand(-1, 1), frand(-1, 1), 0.0f);
	vel = glm::vec3( frand(-5, 5), frand(-5, 5), 0.0f);

	//life = frand(1000,10000);
	life = frand(1,10);
}

Particle::~Particle(){}

void Particle::update(float dt, sf::Vector2f mpos) {
    float dist = sqrt(pow(pos.x-mpos.x, 2) + pow(pos.y-mpos.y, 2));
    dist *= 5;
    pos += vel*dt*std::min(1.0f,(1/(dist*dist)));


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

void Particle::draw(GLuint location, glm::detail::tmat4x4<float> & trans, sf::Vector2f mpos) {
    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans, glm::vec3(0, 0, CAMZ));
    trans = glm::translate(trans, pos);

    float dist = sqrt(pow(pos.x-mpos.x, 2) + pow(pos.y-mpos.y, 2));
    dist *= 50;
    float scale = std::min(0.1f, std::max(0.01f, 1/(dist)));
    // SCALE BASED ON LIFE
    scale *= life/10;

    trans = glm::scale(trans, glm::vec3(scale, scale, 0));
    glUniformMatrix4fv(location,1,GL_FALSE,(GLfloat*)&trans[0][0]);
    glDrawArrays(GL_TRIANGLES,0,6);
}

bool Particle::isDead() {
    return life <= 0.0f;
}
