#ifndef CADENA_H
#define CADENA_H

#include <iostream>

using namespace std;


class Cadena
{
private:
    char* cadenaC;

    static int cantDigitos(int numero);
    static bool esFinDeLinea(char c);

public:

    Cadena();
    Cadena(const char* cadEntrada);
    Cadena(char character);
    Cadena(int num);
    Cadena(long int num);
    Cadena(Cadena& cad);
    ~Cadena();
    Cadena& operator =(const Cadena& cadena);
    Cadena operator +(const Cadena& cadena);

    Cadena& operator +=(const Cadena& cadena);
    bool operator ==(const Cadena& cadena) const;
    //bool operator !=(const Cadena& cadena) const;
    //bool operator <(const Cadena& cadena) const;
    //bool operator <=(const Cadena& cadena) const;
    //bool operator >(const Cadena& cadena) const;
    //bool operator >=(const Cadena& cadena) const;
    //char& operator [](int subindice);
    //const char& operator [](int subindice) const;

    //const char* getCadenaC() const;
    //int getLongitud() const;

    friend ostream& operator << (ostream& os, Cadena& cad);
    friend istream& operator >> (istream& is, Cadena& cad);


    //friend Cadena operator +(const Cadena& cadena1, const Cadena& cadena2);

};


#endif // CADENA_H
