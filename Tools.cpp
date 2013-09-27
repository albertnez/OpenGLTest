#include "Tools.hpp"

int SCREENWIDTH = 700;
int SCREENHEIGHT = 700;
float CAMZ = -1.73;
int NUMPARTICLES = 5000;
float G = 100;
float FRICTION = 0.1;
bool atraction = true;

float frand() {
	return float(rand())/float(RAND_MAX);
}

float frand(int n) {
	return n*float(rand())/float(RAND_MAX);
}

float frand(int lo, int hi) {
	return lo + float(rand())/(float(RAND_MAX)/(hi-lo));
}

float module(float x, float y) {
	return(sqrt(x*x + y*y));
}
float module(const glm::vec2 &v) {
	return (sqrt(v.x*v.x + v.y*v.y));
}

