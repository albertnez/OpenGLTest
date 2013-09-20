#ifndef TOOLS_HPP
#define TOOLS_HPP

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <list>

//GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtc/type_ptr.hpp"

extern int SCREENWIDTH;
extern int SCREENHEIGHT;
extern int NUMPARTICLES;
extern float CAMZ;
extern float G;
extern float FRICTION;

float frand(int n);

/*
struct Vertex {
        Vertex(float px, float py, float pz, float cr, float cg, float cb)
            : px(px), py(py), pz(pz), cr(cr), cg(cg), cb(cb) {}
        ~Vertex() {}
        float px, py, pz;
        float cr, cg, cb;
};
*/
#endif // TOOLS_HPP
