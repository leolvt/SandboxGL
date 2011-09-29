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
#include <iostream>
void Bounce::run()
{
    // Open a new window
    renderer.createWindow();

    // Create Program
    Program prog = Renderer::createProgram("vshader.glsl", "fshader.glsl");

    // Center at (0,0), radius of 0.5
    std::vector<Vertex> vList;
    Vertex Center = {0.0, 0.0, 1.0, 1.0, 1.0};
    vList.push_back(Center);
    const float PI = 3.1415926f;
    const float radius = 0.85;
    const int nVertices = 36;
    for (int i = 0; i <= nVertices; i++) {
        float deg = 2*PI / nVertices * i;
        std::cout << "Degree: " << deg << std::endl;
        Vertex v;
        v.X = radius * glm::cos(deg);
        v.Y = radius * glm::sin(deg);

        std::cout << "X: " << v.X << std::endl;
        std::cout << "Y: " << v.Y << std::endl;
        v.R = 0.5 + sin(deg/4 - PI/2)/2;
        v.G = 0;//0.5 + sin(deg/4)/2;
        v.B = 0;//0.5 + sin(deg/4)/2;
        std::cout << "R: " << v.R << " ";
        std::cout << "G: " << v.G << " ";
        std::cout << "B: " << v.B << std::endl << std::endl;
        vList.push_back(v);
    }
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

        glfwSleep(0.02);
    }

}

// ========================== //

