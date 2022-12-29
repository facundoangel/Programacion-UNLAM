#include "Fecha.h"

//Fecha::Fecha()
//{
//    this->d=0;
//    this->m=0;
//    this->a=0;
//}

Fecha::Fecha() : d(0),m(0),a(0) {}


Fecha::Fecha(int dia, int mes, int anio)
{
    this->d=dia;
    this->m=mes;
    this->a=anio;
}

void Fecha::operator = (Fecha fecha)
{
    this->d=fecha.d;
    this->m=fecha.m;
    this->a=fecha.a;
}



ostream& operator << (ostream& os, Fecha& fe)
{
    os << fe.d << "/" << fe.m << "/" << fe.a;

    return os;
}
