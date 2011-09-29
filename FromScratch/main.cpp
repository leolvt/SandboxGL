#include <iostream>
#include <cstdio>
#include <string>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/gtc/type_ptr.hpp>

#define B_OFFSET(i, type) ((char *)NULL + (i)*sizeof(type))
 
using namespace std;

typedef struct {
    GLfloat x, y;
    GLfloat r, g, b;
} Vertex;

GLuint program;
GLuint VBO;
GLuint VAO;
Vertex triangle[3] = {
    {-0.8, -0.8,  1.0, 0.5, 0.0},
    { 0.8, -0.8,  0.0, 1.0, 0.5},
    { 0.0,  0.8,  0.5, 0.0, 1.0},
};

int shaderStuff()
{
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vs_source = 
        "#version 120                           \n"
        "attribute vec2 InVertex;                 "
        "attribute vec3 InColor;                  "
        "varying vec3 f_color;                    "
        "void main(void) {                        "
        "  gl_Position = vec4(InVertex, 0.0, 1.0);" 
        "  f_color = InColor;         "
        "}";
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Error in vertex shader\n");
        return 0;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs_source =
    "#version 120 \n"
    "varying vec3 f_color; "
    "void main(void) { "
    "    gl_FragColor = vec4(f_color.x, f_color.y, f_color.z, 1.0); "
    "}";
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Error in fragment shader\n");
        return 0;
    }

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        return 0;
    }

    glBindAttribLocation(program, 0, "InVertex");
    glBindAttribLocation(program, 1, "InColor");

    return 1;
}

void init()
{
    glfwInit();
    glfwOpenWindow(800,600,8,8,8,0,0,0,GLFW_WINDOW);
    glewInit();
//    glfwSwapInterval(1);

    cout << glGetString(GL_VENDOR) << endl;
    cout << glGetString(GL_RENDERER) << endl;
    cout << glGetString(GL_VERSION) << endl;
    cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void define()
{
    // Shaders
    shaderStuff();

    // Background Color
    glClearColor(1.0, 1.0, 1.0, 1.0);

    GLfloat triangle_vertices[] = {
        0.0,  0.8,    1.0, 0.0, 0.0,
        -0.8, -0.8,   0.0, 1.0, 0.0,
        0.8, -0.8,    0.0, 0.0, 1.0,
    };

    // Create and Bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and populate VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*3, triangle, 
        GL_STATIC_DRAW);
//    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexAttribPointer(
            0,                 // attribute
            2,                 // number of elements per vertex, here (x,y)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            sizeof(Vertex),    // no extra data between each position
            B_OFFSET(0, float) // pointer to the C array
    );
    
    glVertexAttribPointer(
            1,                 // attribute
            3,                 // number of elements per vertex, here (x,y)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            sizeof(Vertex),    // no extra data between each position
            B_OFFSET(2,float)  // pointer to the C array
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void draw()
{
    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT);

    // Define vertices
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void drawGlfw()
{
    draw();
    glfwSwapBuffers();
    glfwSleep(0.02);
}

bool checkExit()
{
    return glfwGetKey( GLFW_KEY_ESC ) || ! glfwGetWindowParam(GLFW_OPENED);

}

void end()
{
    glfwTerminate();
}

int main(int argc, char *argv[]) {
   
    init();

    define();
    
    while (true)
    {
        drawGlfw();
        if (checkExit()) break;
    }
    end();
    

    return 0;
}
