#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED

#include <iostream>


using namespace std;


class Cadena{

    private:
        char* palabra;



    public:
        Cadena();
        Cadena(const char *cad);
        Cadena(char *cad);
        Cadena(const Cadena& cad);
        ~Cadena();


        Cadena& operator =(const Cadena& cad);
        int longitud();



        friend Cadena operator +( const Cadena& cad1, const Cadena& cad2);
        friend istream& operator >>(istream& is, Cadena& cad);
        friend ostream& operator << (ostream& os, Cadena& cad);
};

#endif // CADENA_H_INCLUDED
