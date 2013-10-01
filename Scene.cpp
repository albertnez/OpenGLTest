#include "Scene.hpp"


Scene::Scene()
{
}

void Scene::init()
{
    std::string vp_filename("shaders/Test.vert"), fp_filename("shaders/Test.frag");
    //LOAD AND COMPILE VERTEX SHADER
    std::cout << "* Loading new vertex shader from " << vp_filename << std::endl;;
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
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
    return true;
}

void Scene::update(float dt)
{

}

void Scene::draw()
{
}


