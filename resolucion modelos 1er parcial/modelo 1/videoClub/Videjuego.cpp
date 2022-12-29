#include <iostream>
#include <string.h>


#include "Videojuego.h"


Videojuego::Videojuego()
{
    this->Titulo=NULL;
    strcpy(this->Genero,"Sin Género");
    this->Fabricante = NULL;
    this->Entregado=false;
    this->DiasDePrestamo=0;

}

Videojuego::Videojuego(const char* titulo,const char* genero,const char* fabricante, bool entregado,int diasDePrestamo)
{

    this->Titulo = new char[strlen(titulo)+1];
    this->Fabricante = new char[strlen(fabricante)+1];

    strcpy(this->Titulo,titulo);
    strcpy(this->Genero,genero);
    strcpy(this->Fabricante,fabricante);
    this->Entregado=entregado;
    this->DiasDePrestamo=diasDePrestamo;

}


Videojuego::Videojuego(const Videojuego& vj)
{
    this->Titulo = new char[strlen(vj.Titulo)+1];
    this->Fabricante = new char[strlen(vj.Fabricante)+1];

    strcpy(this->Titulo,vj.Titulo);
    strcpy(this->Genero,vj.Genero);
    strcpy(this->Fabricante,vj.Fabricante);
    this->Entregado=vj.Entregado;
    this->DiasDePrestamo=vj.DiasDePrestamo;

}


Videojuego::Videojuego(char* titulo)
{
    this->Titulo = new char[strlen(titulo)+1];


    strcpy(this->Titulo,titulo);
    strcpy(this->Genero,"Sin Género");
    this->Fabricante = NULL;
    this->Entregado=false;
    this->DiasDePrestamo=0;

}

Videojuego::~Videojuego()
{
    delete [] this->Titulo;
    delete [] this->Fabricante;
}

Videojuego& Videojuego::operator =(Videojuego& vj)
{
    this->DiasDePrestamo = vj.DiasDePrestamo;
    this->Entregado = vj.Entregado;
    strcpy(this->Fabricante,vj.Fabricante);
    strcpy(this->Genero,vj.Genero);
    strcpy(this->Titulo,vj.Titulo);

    return *this;
}

Videojuego& Videojuego::operator ++()
{
    this->DiasDePrestamo++;

    return *this;

}




ostream& operator << (ostream& os, Videojuego& vj)
{
    char salida[50]="Sin nombre";

    if(vj.Titulo)
        strcpy(salida,vj.Titulo);


    os << " |"<< salida << "| ";

    return os;

}

void Videojuego::remplazarTitulo(Videojuego& vj, char* entrada)
{
    if(!vj.Titulo || strlen(vj.Titulo)!=strlen(entrada))
    {
        delete [] vj.Titulo;
        vj.Titulo = new char[strlen(entrada)+1];
        strcpy(vj.Titulo,entrada);
        return;
    }

    strcpy(vj.Titulo,entrada);

}

istream& operator >> (istream& is, Videojuego& vj)
{


    char respuesta[100];

    cout << "Ingrese Titulo videojuego: " << endl;
    //is >> respuesta;
    gets(respuesta);
    Videojuego::remplazarTitulo(vj,respuesta);

    return is;
}






