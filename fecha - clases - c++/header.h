#include <iostream>
#include <stdbool.h>
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define ANIO_BASE 1600

using namespace std;

class Fecha{

private:
    static const int diasXMes[13];
    static const int cantDiasXMes[13];
    int diaRel=0;
    int d;
    int m;
    int a;
    static int calcularDiasXmes(int m, int y);
    static inline bool esBiciesto(int a){return ((a%4==0 && a%100!=0) || (a%400==0));};
    static bool fechaValida(int a, int m, int d);
    void ajustarFecha();


public:
    Fecha();
    char prueba;
    Fecha(int d, int m, int y);
    void obtenerDiaRel();
    void obtenerFechaNormal();
    void mostrarDiaRel();
    void sumarFecha(int);
    void mostrarFechaNormal();
    int obtenerDia();
    int obtenerMes();
    int obtenerAnio();
    void establecerDia(int d);
    void establecerMes(int m);
    void establecerAnio(int a);
    bool operator == ( string s);
    void operator +(int dias);
    void operator ++();
    void operator ++(int);
    void operator --();
    void operator --(int);
    void operator -(int dias);


};

ostream& operator << (ostream& o, Fecha& f);
istream& operator >> (istream& i, Fecha& f);


#endif // HEADER_H_INCLUDED
