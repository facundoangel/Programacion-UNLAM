#include "Cadena.h"


Cadena::Cadena()
{
   this->cad=new char[1];
   this->cad[0]='\0';

}


Cadena::Cadena(const char* param)
{
   this->cad=new char[strlen(param)+1];
   strcpy(this->cad,param);

}

Cadena::~Cadena()
{
    delete [] this->cad;
}


ostream& operator <<(ostream& os, Cadena ca)
{

    os << ca.cad;

    return os;
}
