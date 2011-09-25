#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <GL/glew.h>
#include <GL/glut.h>

/* ==================================== */

class Util
{
    public:
        std::string static readFile(std::string filename);
        void static printLog(GLuint object);
        GLint static createShader(std::string filename, GLenum type);
};

/* ==================================== */

#endif /* UTIL_H_INCLUDED */
