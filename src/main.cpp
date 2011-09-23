#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Util.h"

GLuint program;
GLint attribute_coord2d;


/*
 * Display compilation errors from the OpenGL shader compiler
 *
void print_log(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        fprintf(stderr, "printlog: Not a shader or a program\n");
        return;
    }

    char* log = (char*)malloc(log_length);

    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);

    fprintf(stderr, "%s", log);
    free(log);
}
*/

/* 
 * Compile the shader from file 'filename', with error handling
 */
GLint create_shader(const char* filename, GLenum type)
{
    const GLchar* source = ReadFileIntoString(filename).c_str();
    if (source == NULL) {
        fprintf(stderr, "Error opening %s: ", filename); perror("");
        return 0;
    }
    GLuint res = glCreateShader(type);
    glShaderSource(res, 1, &source, NULL);
    free((void*)source);

    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        fprintf(stderr, "%s:", filename);
    //    print_log(res);
        glDeleteShader(res);
        return 0;
    }

    return res;
}

int init_resources()
{
    GLuint vs, fs;
    if ((vs = create_shader("v.glsl", GL_VERTEX_SHADER))   == 0) return 0;
    if ((fs = create_shader("f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0;
    if (!true) {
        fprintf(stderr, "glLinkProgram:");
        //print_log(program);
    }

}

void display()
{
    glUseProgram(program);

    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
        0.0,  0.8,
        -0.8, -0.8,
        0.8, -0.8,
    };
    /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
    glVertexAttribPointer(
            attribute_coord2d, // attribute
            2,                 // number of elements per vertex, here (x,y)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            0,                 // no extra data between each position
            triangle_vertices  // pointer to the C array
            );

    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);

    /* Display the result */
    glutSwapBuffers();
}

void free_resources()
{
    glDeleteProgram(program);
}

#include <iostream>

int main(int argc, char* argv[]) {
    
    std::cout << ReadFileIntoString("file.txt");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("My First Triangle");

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        return 1;
    }

    if (init_resources()) {
        glutDisplayFunc(display);
        glutMainLoop();
    }

    free_resources();
    
    return 0;
}

