#include <GL/glew.h>
#include <GL/glfw.h>

#include "Bounce.h"
#include "Exceptions.h"

// ========================== //

Bounce::Bounce()
{
}

// ========================== //

Bounce::~Bounce()
{
}

// ========================== //

void Bounce::run()
{
    // Open a new window
    renderer.createWindow();

    // Create Program
    Program prog = Renderer::createProgram("vshader.glsl", "fshader.glsl");
    Vertex v1 = {-1, -1, 1, 0, 0};
    Vertex v2 = {1, -1, 0, 0, 1};
    Vertex v3 = {0, 1, 0, 1, 0};
    std::vector<Vertex> vList;
    vList.push_back(v1);
    vList.push_back(v2);
    vList.push_back(v3);
    Object triangle = Renderer::createObject(vList);

    // Main loop
    running = true;
    while( running )
    {
        // for obj in list of obj:
        //    obj.draw();
        glm::mat4 matriz(1.0f);
        renderer.drawObject(prog, triangle, matriz);
       
        // Render Final Image
        renderer.render();

        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
            glfwGetWindowParam( GLFW_OPENED );
    }

}

// ========================== //

