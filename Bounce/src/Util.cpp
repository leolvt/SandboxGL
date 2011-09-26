#include <string>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <GL/glfw.h>

#include "Util.h"
#include "Exceptions.h"

/* =========================================== */

/*
 * readFile - Read *filename* into a string.
 */
std::string Util::readFile(std::string filename) 
{
    // Result will be stored in a stringstream for easy manipulation
    std::stringstream result;

    // Try to open the file
    std::ifstream iFile;
    iFile.exceptions(std::ifstream::failbit);
    try
    {
        iFile.open(filename.c_str());
        result << iFile.rdbuf();
    }
    catch (std::exception& e) {
        iFile.close();
        std::string msg = "Erro ao carregar arquivo '"+filename+"'";
        throw IOException(msg);
    }
    iFile.close();
    return result.str();
}

/* =========================================== */

