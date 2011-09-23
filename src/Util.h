#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <exception>

class BadFileException: public std::exception
{
    public:
        BadFileException(std::string msg) 
        {
            this->msg = msg;
        }

        virtual const char* what() const throw()
        {
            return msg.c_str();
        }

        virtual ~BadFileException() throw() {}
    private:
        std::string msg;
};

std::string ReadFileIntoString(std::string filename);

#endif  /* UTIL_H_INCLUDED */

