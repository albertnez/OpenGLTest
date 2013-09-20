#include "Particle.hpp"

Particle::Particle()
{
    pos = glm::vec3( float((rand()%2000-1000)/1000), float((rand()%2000-1000)/1000), 0.0);
    vel = glm::vec3(float(rand()%3000)/1000, float(rand()%3000)/1000, 0);
    if (rand()%2) vel.x *= -1;
    if (rand()%2) vel.y *= -1;
}

void Particle::update(float dt, sf::Vector2f mpos) {
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


    float dist = sqrt(pow(pos.x-mpos.x, 2) + pow(pos.y-mpos.y, 2));
    float Force = G/(dist*dist);
/*
    vel.x += Force*((mpos.x-pos.x)/dist)*dt*FRICTION;
    vel.y -= Force*((mpos.y-pos.y)/dist)*dt*FRICTION;
*/
}

void Particle::draw(GLuint location, glm::detail::tmat4x4<float> & trans) {
    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans, glm::vec3(0, 0, CAMZ));
    trans = glm::translate(trans, pos);
    trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0));
    glUniformMatrix4fv(location,1,GL_FALSE,(GLfloat*)&trans[0][0]);
    glDrawArrays(GL_TRIANGLES,0,6);
}


