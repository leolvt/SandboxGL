#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <GL/glfw.h>

// ==================================== //

class Util
{
    public:
        std::string static readFile(std::string filename);
};

// ==================================== //

#endif /* UTIL_H_INCLUDED */
