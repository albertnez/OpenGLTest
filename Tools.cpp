#include "Tools.hpp"

int SCREENWIDTH = 800;
int SCREENHEIGHT = 800;
float CAMZ = -1.73;
int NUMPARTICLES = 5000;
float G = 1000;
float FRICTION = 0.001;

float frand(int n) {
    return (rand()%(2*n)-n)/(2*n);
}
