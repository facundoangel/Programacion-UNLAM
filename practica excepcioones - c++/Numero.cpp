#include "Numero.h"

Numero Numero::operator-(const Numero& num) const
{
    Numero nue(this->cantidad);

    if(this->cantidad<num.cantidad)
    {
        throw ErrorPersonalizado("no podes restar por un numero mas grande, boludo");
    }

    nue.cantidad-=num.cantidad;

    return nue;
}

Numero Numero::operator/(const Numero& num) const
{
    Numero nue(this->cantidad);

    if(num.cantidad==0)
    {
        throw ErrorPersonalizado("no podes dividir por cero");
    }

    nue.cantidad/=num.cantidad;

    return nue;
}

ostream& operator<<(ostream& os, Numero num)
{
    os << num.cantidad;

    return os;
}

