
#include "customException.h"

ErrorPersonalizado::ErrorPersonalizado(const char* msg)
{
    this->msg = new char[strlen(msg)+1];
    strcpy(this->msg,msg);
}

