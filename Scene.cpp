#include "Scene.hpp"
#include "Game.hpp"


Scene::Scene(Game &parent) : parent(parent), VBO(0), time(0)
{
	std::cout << "creating scene" << std::endl;

	for (int i = 0; i < NUMPARTICLES; ++i) {
        PEvector.push_back( ParticleEmitter(glm::vec2(frand(-1,1),frand(-1,1)), glm::vec2(frand(1), frand(1))*2.0f, 0.5f, 200.0f, glm::vec3(frand(1.0f), frand(1.0f), frand(1.0f)), glm::vec3(frand(1.0f), frand(1.0f), frand(1.0f))));
	}

//	PEvector.push_back( ParticleEmitter(glm::vec2(0), glm::vec2(frand(1), frand(1))*5.0f, 0.5f, 200.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.05f, 1.0f, 0.05f)) );
//	PEvector.push_back( ParticleEmitter(glm::vec2(0), glm::vec2(frand(1), frand(1))*5.0f, 0.5f, 200.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.05f, 0.05f)) );


}

bool Scene::init()
{
	std::cout << "Scene init" << std::endl;
    std::string vp_filename("shaders/Test.vert"), fp_filename("shaders/Test.frag");
    //LOAD AND COMPILE VERTEX SHADER
    std::cout << "* Loading new vertex shader from " << vp_filename << std::endl;
    Shader vertex(GL_VERTEX_SHADER);
    vertex.load(vp_filename);
    if (!vertex.compile()) {
        vertex.printInfoLog();
        std::cout << "#ERROR Compile failed for vertex shader '" << vp_filename << "'." << std::endl;;
        return false;
    }
    else std::cout << " - Compiled " << vp_filename << " successfully." << std::endl;;

    //LOAD AND COMPILE FRAGMENT SHADER
    std::cout << "* Loading new fragment shader from " << fp_filename << std::endl;;
    Shader fragment(GL_FRAGMENT_SHADER);
    fragment.load(fp_filename);
    if (!fragment.compile()) {
        fragment.printInfoLog();
        std::cout << "#ERROR Compile failed for fragment shader '" << fp_filename << "'." << std::endl;
        return false;
    }
    else std::cout <<  " - Compiled " << fp_filename << " successfully." << std::endl;

    //CREATE THE PROGRAM
    std::cout << "* Creating new shaderProgram with " << vp_filename << " and " << fp_filename << std::endl;
    programHandle = glCreateProgram();

    //ATTACH AND LINK
    vertex.attach(programHandle);
    fragment.attach(programHandle);
    glLinkProgram(programHandle);

    glGenBuffers(1, &VBO);
    glUseProgram(programHandle);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Simple quad
    std::vector<Vertex> data;
    data.push_back( Vertex(-1, 1) );
    data.push_back( Vertex(-1, -1) );
    data.push_back( Vertex(1, -1) );

    data.push_back( Vertex(-1, 1) );
    data.push_back( Vertex(1, -1) );
    data.push_back( Vertex(1, 1) );

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*data.size(), &data[0], GL_STATIC_DRAW);
	std::cout << "scene init success" << std::endl;
    return true;
}

void Scene::update(float dt)
{
	time += dt;
    sf::Event event;
	while(parent.getWindow().pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
				parent.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R) REPULSION = !REPULSION;
                else if (event.key.code == sf::Keyboard::G) GRAVITY = !GRAVITY;
				else if (event.key.code == sf::Keyboard::Escape) parent.close();
                break;
            case sf::Event::MouseButtonPressed:
            if (event.key.code == sf::Mouse::Left) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                else if (event.key.code == sf::Mouse::Right) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case sf::Event::Resized:
				SCREENWIDTH = parent.getWindow().getSize().x;
				SCREENHEIGHT = parent.getWindow().getSize().y;
                glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
                break;
        }
    }

	sf::Vector2i mpos = mouse.getPosition(parent.getWindow());
    mousepos = glm::vec2(
                (float(mpos.x)/float(SCREENWIDTH)-0.5)*2,
                (float(-mpos.y)/float(SCREENHEIGHT)+0.5)*2
                );


    //Repulsion test!

    for (int i = 0; i < PEvector.size(); ++i) {
        for (int j = 0; j < PEvector.size(); ++j) {
            if (i != j) {
                glm::vec2 pos1 = PEvector[i].getPos(), pos2 = PEvector[j].getPos();
                if (pos1.x != pos2.x and pos1.y != pos2.y) {
                    float dist = module(pos1.x-pos2.x, pos1.y-pos2.y);
                    glm::vec2 uvect = glm::vec2(pos1.x-pos2.x, pos1.y-pos2.y)/dist;
                    glm::vec2 force = uvect / (dist*dist);
                    PEvector[i].setVel(PEvector[i].getVel() + force*dt);
                }
            }
        }
    }


    for (int i = 0; i < PEvector.size(); ++i)  PEvector[i].update(dt, mousepos);
}

void Scene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programHandle);

    GLuint loc = glGetUniformLocation(programHandle, std::string("modelViewProjectionMatrix").c_str());
    GLuint alphaLoc = glGetUniformLocation(programHandle, std::string("alpha").c_str());
    GLuint timeLoc = glGetUniformLocation(programHandle, std::string("time").c_str());
    GLuint colorLoc = glGetUniformLocation(programHandle, std::string("color").c_str());

    glUniform1f(timeLoc, time);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Draw
    trans = glm::perspective(60.0f,float(SCREENWIDTH)/ float(SCREENHEIGHT), 0.001f,1000.0f);
    trans = glm::translate(trans, glm::vec3(0, 0, CAMZ));

    for (int i = 0; i < PEvector.size(); ++i) PEvector[i].draw(loc, trans, colorLoc, alphaLoc);

    glDisableVertexAttribArray(0);
}


