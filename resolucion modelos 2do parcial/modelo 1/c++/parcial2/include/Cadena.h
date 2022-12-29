#ifndef CADENA_H
#define CADENA_H

#include <string.h>
#include <iostream>

using namespace std;


class Cadena
{
    private:
        char* cad;
    public:
        Cadena();
        Cadena(const char* param);
        ~Cadena();

    friend ostream& operator <<(ostream& os, Cadena ca);

};

#endif // CADENA_H
