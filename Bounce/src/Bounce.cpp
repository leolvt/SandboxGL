#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include "Bounce.h"

// ========================== //

Bounce::Bounce(unsigned int numBalls)
{
    // Set Up a GL Context
    std::cout << ">> Setting OpenGL Context via GLFW...   " << std::flush;
    glfwInit();
    std::cout << "[DONE]" << std::endl;

    // Create Balls
    std::cout << ">> Creating " << numBalls << " ball(s)...   " << std::flush;
    srand48( time(NULL) );
    for (int i = 0; i < numBalls; i++) {
        this->balls.push_back(Ball(0, 0, 0.05));
    }
    std::cout << "[DONE]" << std::endl;
}

// ========================== //

Bounce::~Bounce()
{
    std::cout << ">> Freeing resources...   " << std::flush;
    this->balls.clear();
    std::cout << "[DONE]" << std::endl;
}

// ========================== //

void Bounce::run()
{
    // Open a new window
    std::cout << ">> Opening OpenGL Window via GLFW...   " << std::flush;
    glfwOpenWindow(800, 400, 8, 8, 8, 0, 0, 0, GLFW_WINDOW);
    glClearColor(1,1,1,1);
    glfwSetWindowTitle("Bouce v1.0");
    std::cout << "[DONE]" << std::endl;

    // Create Program
    //Program prog = Renderer::createProgram("vshader.glsl", "fshader.glsl");
    
    // Setting Projection Matrix
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D(-2, 2, -1, 1);
    glMatrixMode( GL_MODELVIEW );

    // Main loop
    bool running = true;
    bool paused = false;
    bool lmb = false;
    while( running )
    {
        // Check for mouse button for pause and velocity randomize
        if ( glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE )
        {
            if (lmb)
            {
                paused = !paused;
            }
            lmb = false;
        }
        else lmb = true;

        if ( glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS )
        {
            for (int i = 0; i < balls.size(); i++) {
                balls[i].randomizeSpeed();
            }
        }
        if (glfwGetKey('R') == GLFW_PRESS) 
        {
            for (int i = 0; i < balls.size(); i++) {
                balls[i].reset();
            }
        }

        if (!paused)
        {
            // Clear Frame
            glClear(GL_COLOR_BUFFER_BIT);

            // Update Balls and draw balls
            for (int i = 0; i < balls.size(); i++) {
                balls[i].update();
                balls[i].draw();
            }
            
            // Render Final Image
            glfwSwapBuffers();
        }

        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) && !glfwGetKey('Q') && 
            glfwGetWindowParam( GLFW_OPENED );

        glfwPollEvents();
        glfwSleep(0.02);
    }

}

// ========================== //

