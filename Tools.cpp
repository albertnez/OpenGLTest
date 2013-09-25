#include "Tools.hpp"

int SCREENWIDTH = 700;
int SCREENHEIGHT = 700;
float CAMZ = -1.73;
int NUMPARTICLES = 5000;
float G = 1000;
float FRICTION = 0.001;

float frand() {
	return float(rand())/float(RAND_MAX);
}

float frand(int n) {
	return n*float(rand())/float(RAND_MAX);
}

float frand(int lo, int hi) {
	return lo + float(rand())/(float(RAND_MAX)/(hi-lo));
}

