#ifndef FECHA_H
#define FECHA_H

#include <iostream>

 using namespace std;

class Fecha
{
    private:
        int d;
        int m;
        int a;

    public:


        Fecha();
        Fecha(int dia, int mes, int anio);

        void operator = (Fecha fecha);
        friend ostream& operator << (ostream& os, Fecha& fe);

        //write getter and setter of the atributes
        int getDia() { return d; }
        int getMes() { return m; }
        int getAnio() { return a; }

};

#endif // FECHA_H
