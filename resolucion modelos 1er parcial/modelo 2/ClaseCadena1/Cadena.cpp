#include "Cadena.h"
#include <string.h>




Cadena::Cadena()
{
    this->palabra = new char[1];
    this->palabra[0]='\0';

}

Cadena::Cadena(Cadena& cad)
{

    this->palabra = new char[strlen(cad.palabra)+1];
    strcpy(this->palabra,cad.palabra);
}

Cadena::Cadena(const char* cad)
{

    this->palabra = new char[strlen(cad)+1];
    strcpy(this->palabra,cad);

}

Cadena::~Cadena()
{
    delete [] this->palabra;
}


Cadena& Cadena::operator =(const Cadena& cad){

    if(strlen(this->palabra)!=strlen(cad.palabra))
    {
        delete [] this->palabra;
        this->palabra = new char[strlen(cad.palabra)+1];

    }

    strcpy(this->palabra,cad.palabra);

    return *this;
}


int Cadena::longitud()
{
    int longitud = strlen(this->palabra);
    return longitud;
}
