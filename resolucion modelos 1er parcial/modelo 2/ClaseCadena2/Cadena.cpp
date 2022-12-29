#include "Cadena.h"
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;


Cadena::Cadena()
{
    this->palabra = new char[1];
    this->palabra[0]='\0';

}

Cadena::Cadena(const Cadena& cad)
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

Cadena operator +( const Cadena& cad1, const Cadena& cad2)
{
    Cadena nuevaCadena;


    nuevaCadena.palabra = new char[strlen(cad1.palabra)+strlen(cad2.palabra)+1];
    strcpy(nuevaCadena.palabra,cad1.palabra);
    strcat(nuevaCadena.palabra,cad2.palabra);



    return nuevaCadena;

}



int Cadena::longitud()
{
    int longitud = strlen(this->palabra);
    return longitud;
}


istream& operator >>(istream& is, Cadena& cad)
{

    queue<char> colaCaracteres;
    char c;
    int cont=0;

    while((c = is.get()) != '\n')
        colaCaracteres.push(c);

    if((int)colaCaracteres.size() != cad.longitud())
    {
        delete [] cad.palabra;
        cad.palabra = new char[colaCaracteres.size()+1];

    }

    while(!colaCaracteres.empty())
    {
        cad.palabra[cont] = colaCaracteres.front();
        colaCaracteres.pop();
        cont++;

    }

    cad.palabra[cont] =  '\0';


    return is;
}



ostream& operator << (ostream& os, Cadena& cad){

    os << cad.palabra;

    return os;
}
