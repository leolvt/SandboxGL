#include <iostream>

#include <GL/glfw.h>

int main(int argc, const char *argv[]) {
    std::cout << "Hello World!" << std::endl;

    // Init GLFW (Window-Independent stuff)
    GLboolean res = glfwInit();
    if (res == GL_FALSE) return 1;

    // Open a window
    res = glfwOpenWindow(
        800, // Width
        600, // Height
        8, 8, 8, // # of RGB bits
        0, 0, 0, // # of Alpha, Depth and Stencil bits
        GLFW_WINDOW // Window Mode
    );
    glfwSetWindowTitle("Super Bounce with OpenGL");
    glfwSetWindowPos(0, 0);

    if (res == GL_FALSE) return 1;

    // Main loop
    GLboolean running = GL_TRUE;
    while( running )
    {
        // OpenGL rendering goes here...
        glClear( GL_COLOR_BUFFER_BIT );

        // Swap front and back rendering buffers
        glfwSwapBuffers();

        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
            glfwGetWindowParam( GLFW_OPENED );
    }

    // Terminate GLFW - no more GLFW calls
    glfwTerminate();

    // ANSI C requires this!
    return 0;
}
