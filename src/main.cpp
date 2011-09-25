#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Util.h"

/* ==================================== */

GLuint program;
GLuint vbo_triangle, vbo_triangle_colors;
GLint attribute_coord2d, attribute_v_color;
GLint uniform_fade;

/* ==================================== */

bool initResources()
{
    std::cout << "===== Init Resources =====" << std::endl;

    std::cout << ">> Checking OpenGL Version..." << std::endl;
    if (!GLEW_VERSION_2_0) {
        std::cerr << "Error: your graphic card does not support OpenGL 2.0" << std::endl;
        return false;
    }
    std::cout << ">> Done." << std::endl;

    // Compile shaders from files
    std::cout << ">> Compiling shaders ..." << std::endl;
    GLuint vs = Util::createShader("vshader.glsl", GL_VERTEX_SHADER) ;
    std::cout << ">> Vertex Shader Compiled!" << std::endl << std::flush;
    GLuint fs = Util::createShader("fshader.glsl", GL_FRAGMENT_SHADER) ;
    std::cout << ">> Fragment Shader Compiled!" << std::endl << std::flush;
    if (vs == 0 || fs == 0) return false;
    std::cout << ">> Done." << std::endl;

    // Link Shaders to the program
    std::cout << ">> Linking Program ..." << std::endl;
    GLint link_ok = GL_FALSE;
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        std::cerr << "Error linking shaders!" << std::endl; 
        Util::printLog(program);
    }
    std::cout << ">> Done." << std::endl;

    // Create VBO for our triangle
    std::cout << ">> Creating triangle VBO ..." << std::endl;
    GLfloat triangle_vertices[] = {
        0.0,  0.8,
        -0.8, -0.8,
        0.8, -0.8,
    };
    glGenBuffers(1, &vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat triangle_colors[] = {
        1.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
    };
    glGenBuffers(1, &vbo_triangle_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << ">> Done." << std::endl;

    // Bind attribute to program
    std::cout << ">> Binding coord2d ..." << std::endl;
    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord2d == -1) {
        std::cerr << "Could not bind attribute " << attribute_name << std::endl;
        return false;
    }
    const char* attribute_color_name = "v_color";
    attribute_v_color = glGetAttribLocation(program, attribute_color_name);
    if (attribute_v_color == -1) {
        std::cerr << "Could not bind attribute " << attribute_color_name << std::endl;
        return false;
    }
    glDisableVertexAttribArray(attribute_v_color);
    std::cout << ">> Done." << std::endl;

    // Define Uniform attribute
    const char* uniform_name;
    uniform_name = "fade";
    uniform_fade = glGetUniformLocation(program, uniform_name);
    if (uniform_fade == -1) {
        std::cerr << "Could not bind uniform " << uniform_name << std::endl;
        return false;
    }

    std::cout << std::endl;
    return true;
}

/* ==================================== */

void freeResources()
{
    std::cout << "Free Resources" << std::endl;\
        glDeleteProgram(program);
    glDeleteBuffers(1, &vbo_triangle);
}

/* ==================================== */

void display()
{
    glUseProgram(program);

    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glUniform1f(uniform_fade, 0.1);

    /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
    glEnableVertexAttribArray(attribute_coord2d);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glVertexAttribPointer(
            attribute_coord2d, // attribute
            2,                 // number of elements per vertex, here (x,y)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            0,                 // no extra data between each position
            0                  // offset of first element
            );
    
    glEnableVertexAttribArray(attribute_v_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
    glVertexAttribPointer(
        attribute_v_color, // attribute
        3,                 // number of elements per vertex, here (r,g,b)
        GL_FLOAT,          // the type of each element
        GL_FALSE,          // take our values as-is
        0,                 // no extra data between each position
        0                  // offset of first element
     );

    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);

    /* Display the result */
    glutSwapBuffers();
}

/* ==================================== */

void
idle()
{
    float cur_fade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2*3.14) / 2) / 2 + 0.5; // 0->1->0 every 5 seconds
    glUniform1f(uniform_fade, cur_fade);
    glutPostRedisplay();
}

/* ==================================== */

int main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("My First Triangle");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) 
    {
        std::cerr << "Error: " << glewGetErrorString(glew_status) << std::endl;
        return 1;
    }

    if (initResources()) 
    {
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutMainLoop();
    }

    freeResources();
    return 0;
}
/* ==================================== */
