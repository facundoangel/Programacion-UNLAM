#ifndef CUSTOMEXCEPTION_H_INCLUDED
#define CUSTOMEXCEPTION_H_INCLUDED

#include <string.h>

class ErrorPersonalizado
{
private:
    char* msg;


public:
    ErrorPersonalizado(const char* msg);
    char* getMessage()const{return this->msg;}
    ~ErrorPersonalizado(){delete [] this->msg;}

};


#endif // CUSTOMEXCEPTION_H_INCLUDED
