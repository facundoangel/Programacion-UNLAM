#ifndef NUMERO_H_INCLUDED
#define NUMERO_H_INCLUDED

#include <iostream>
#include "customException.h"

using namespace std;

class Numero
{
private:
    int cantidad;

public:
    Numero(int cant) : cantidad(cant){}
    Numero(const Numero& num):cantidad(num.cantidad){}
    Numero operator -(const Numero& num)const;
    Numero operator /(const Numero& num)const;

    friend ostream& operator<<(ostream& os, Numero num);
};

#endif // NUMERO_H_INCLUDED
