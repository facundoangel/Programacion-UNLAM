#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include <iostream>
using namespace std;

class FVector{


private:
    float *vec;
    int cantElementos;

public:
    FVector(float v[], int ce);
    friend ostream &operator<<(ostream &os, FVector &obj);
    int operator==(const FVector &obj);
    FVector operator+=(float valor);
    FVector &operator--(int );
    FVector &operator/(const FVector &obj);

};
class MiException{
private:
    string message;

    public:
        MiException(string mensaje);
        inline string getMensaje(){return this->message;}

};


#endif // CLASS_H_INCLUDED
