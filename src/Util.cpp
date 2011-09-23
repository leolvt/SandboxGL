#include <string>
#include <sstream>
#include <fstream>
#include "Util.h"

/* =========================================== */

std::string 
ReadFileIntoString(std::string filename)
{
    std::stringstream ss;
    std::ifstream iFile;
    iFile.open(filename.c_str());

    if (iFile.is_open()) 
    {
        while (!iFile.eof()) 
        {
            std::string line;
            iFile >> line;
            ss << line;
            if (!iFile.eof())
            {
                ss << std::endl;
            }
        }
    }
    else 
    {
        throw BadFileException("Erro ao abrir arquivo!");
    }

    return ss.str();
}

/* =========================================== */
