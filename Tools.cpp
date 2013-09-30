#include "Tools.hpp"

int SCREENWIDTH = 500;
int SCREENHEIGHT = 500;
float CAMZ = -1.73;

int NUMPARTICLES = 100;

bool REPULSION = true;

float frand() {
	return float(rand())/float(RAND_MAX);
}

float frand(int n) {
	return n*float(rand())/float(RAND_MAX);
}

float frand(float lo, float hi) {
	return lo + float(rand())/(float(RAND_MAX)/(hi-lo));
}

float module(float x, float y) {
	return(sqrt(x*x + y*y));
}
float module(const glm::vec2 &v) {
	return (sqrt(v.x*v.x + v.y*v.y));
}

