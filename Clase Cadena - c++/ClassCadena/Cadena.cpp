#include <string.h>
#include <queue>
#include <iostream>
#include "Cadena.h"
#include <string.h>

using namespace std;

//constructores==============================================================================================
Cadena::Cadena()
{
    this->cadenaC = new char[1];
    strcpy(this->cadenaC,"\0");
}

Cadena::Cadena(const char* cadEntrada)
{
    this->cadenaC = new char[strlen(cadEntrada + 1 )];
    strcpy(this->cadenaC, cadEntrada);

}


Cadena::Cadena(char character)
{
    this->cadenaC = new char[2];
    this->cadenaC[0] = character;
    this->cadenaC[1] = '\0';

}


Cadena::Cadena(int num)
{
    this->cadenaC = new char[cantDigitos(num)+1];
    sprintf(this->cadenaC,"%d",num);

}


Cadena::Cadena(long int num)
{
    this->cadenaC = new char[cantDigitos(num)+1];
    sprintf(this->cadenaC,"%ld",num);

}

Cadena::Cadena(Cadena& cad)
{
    this-> cadenaC = new char[strlen(cad.cadenaC)+1];
    strcpy(this->cadenaC,cad.cadenaC);

}



//constructores==============================================================================================

Cadena::~Cadena()
{
    delete [] this->cadenaC;
}

Cadena& Cadena::operator =(const Cadena& cadena)
{

    delete[] this->cadenaC;
    this->cadenaC = new char[strlen(cadena.cadenaC)+1];
    strcpy(this->cadenaC,cadena.cadenaC);


    return *this;
}


Cadena Cadena::operator +(const Cadena& cadena)
{
    Cadena cadResultado;


    delete[] cadResultado.cadenaC;
    cadResultado.cadenaC = new char[strlen(this->cadenaC) + strlen(cadena.cadenaC) + 1];
    strcpy(cadResultado.cadenaC,this->cadenaC);
    strcat(cadResultado.cadenaC,cadena.cadenaC);


    return cadResultado;
}


int Cadena::cantDigitos(int numero)
{
    int cont=1;

    while((numero/=10)!=0)
    {
        cont++;

    }

    return cont;

}



ostream& operator << (ostream& os, Cadena& cad)
{
    os << cad.cadenaC;

    return os;
}


istream& operator >> (istream& is, Cadena& cad)
{
    queue<char> cola;
    delete [] cad.cadenaC;
    char character = is.get();

    while(character != '\n' && character != EOF )
    {
        cola.push(character);
        character = is.get();
    }

    if(cola.empty())
    {

        cad.cadenaC = new char[6];
        strcpy(cad.cadenaC,"vacio");
        //cad = Cadena("vacio");

    }
    else
    {

        int cantChar = cola.size();
        //char* nuevoChar = new char[ cantChar];
        cad.cadenaC = new char[cantChar];
        cad.cadenaC[cantChar]='\0';


        for(int i=0;i<cantChar;i++)
        {
            cad.cadenaC[i]=cola.front();
            cola.pop();

        }



    }




    return is;
}
