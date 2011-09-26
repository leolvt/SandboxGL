#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <string>
#include <exception>

/* ==================================== */

class BaseException : public std::exception
{
    public:
        BaseException(std::string msg);
        virtual ~BaseException() throw ();
        virtual const char* what() const throw();
    private:
        std::string msg;
};

/* ==================================== */

class IOException: public BaseException
{
    public: 
        IOException(std::string msg) : BaseException(msg) {};
};

/* ==================================== */

class OpenGLException: public BaseException
{
    public: 
        OpenGLException(std::string msg) : BaseException(msg) {};
};

/* ==================================== */

class GLFWException: public BaseException
{
    public: 
        GLFWException(std::string msg) : BaseException(msg) {};
};

/* ==================================== */

#endif /* EXCEPTIONS_H_INCLUDED */
