#include "Exceptions.h"

/* =========================================== */

BaseException::BaseException(std::string msg)
{
    this->msg = msg;
}

/* =========================================== */

BaseException::~BaseException() throw()
{

}

/* =========================================== */

const char* BaseException::what() const throw()
{
    return this->msg.c_str();
}

/* =========================================== */


