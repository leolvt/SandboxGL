#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstring>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Util.h"

/* =========================================== */

std::string Util::readFile(std::string filename)
{
    std::stringstream result;
    std::ifstream iFile;
    iFile.open(filename.c_str());

    if (iFile.is_open()) 
    {
        while (!iFile.eof()) 
        {
            std::string line;
            getline(iFile, line);
            result << line << std::endl;
        }
    }
    else 
    {
        throw std::string("Erro ao abrir arquivo!");
    }

    return result.str();
}

/* =========================================== */

/**
 * Display compilation errors from the OpenGL shader compiler
 */
void Util::printLog(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        std::cerr << "Error: Not a shader or a program\n" << std::endl;
        return;
    }

    char* log = (char*)malloc(log_length);

    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);

    std::cerr << log << std::endl;
    free(log);
}

/* =========================================== */

/**
 * Compile the shader from file 'filename', with error handling
 */
GLint Util::createShader(std::string filename, GLenum type)
{
    std::string fileContent = readFile(filename);
    const GLchar* source = fileContent.c_str();

    
    GLuint res = glCreateShader(type);
    
    glShaderSource(res, 1, &source, NULL);

    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        std::cerr << filename << ": ";
        printLog(res);
        glDeleteShader(res);
        return 0;
    }

    return res;
}

/* =========================================== */

