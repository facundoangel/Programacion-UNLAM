#include <iostream>
#include "../ClassCadena/Cadena.h"

using namespace std;

void funcionPrueba(Cadena cad)
{
    cout << "ejecucion de funcion prueba" << endl;

}


int main()
{
    //char* prueba = "prueba";
    Cadena c1("hola");
    Cadena c2("chau");

    Cadena c3;
    c3 = c1 + " prueba" + " prueba2";
    cout << c3 << endl;

    return 0;
}
