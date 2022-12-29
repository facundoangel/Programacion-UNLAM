#include <iostream>
#include "Class.h"
using namespace std;

FVector::FVector(float v[], int ce)
{
    this->vec = v;
    this->cantElementos = ce;

}
ostream &operator<<(ostream &os, FVector &obj)
{
    int i;
    os<<"{";
    for (i= 0; i< obj.cantElementos ; i++)
        os<<obj.vec[i]<<",";
    os<<"}";

    return os;
}
int FVector::operator==(const FVector &obj)
{
    if(this->cantElementos!= obj.cantElementos)
        return 0;

    int i=0;
    for(i = 0; i < obj.cantElementos; i++)
    {
        if(obj.vec[i] != this->vec [i])
            return 0;
    }
    return 1;
}
FVector FVector::operator+=(float valor)
{
    int i ;
    for (i = 0; i < this->cantElementos; i++)
        this->vec[i] = vec[i] + valor;
    return *this;
}
FVector& FVector::operator--(int )
{
    int i ;
    for (i = 0; i < this->cantElementos; i++)
        this->vec[i] --;
    return *this;
}
FVector& FVector::operator/(const FVector &obj)
{
    if(obj.cantElementos != this->cantElementos)
        throw MiException("Este operator no aplica a vectores de diferente tamanio");
    float result;
    int i;
    for (i = 0; i < obj.cantElementos ; i++)
            {
            this->vec[i] = this->vec[i] / obj.vec[i];
            }

        return *this;
}
MiException::MiException(string mensaje)
{
    this->message = mensaje;
}






