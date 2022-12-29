#include <stdio.h>
#include <stdlib.h>
#include "suma.h"
//#include "../TDAPila/TDAPilaImplEstatica.h"


int main()
{
    Pila p1, p2, resultado;
    char num1[15];
    char num2[15];


    IngresarNumeros(num1,num2);

    igualarLongitud(num1,num2);
    printf("\n Numeros de entrada:");
    printf("\n num1: %s",num1);
    printf("\n num2: %s\n",num2);
    crearPila(&p1);
    crearPila(&p2);
    crearPila(&resultado);
    inicializarPila(&p2,num2);
    inicializarPila(&p1,num1);
    printf("\n==========Pilas de entrada:==========");
    mostrarPila(&p2);
    mostrarPila(&p1);

    sumarPilas(&p1,&p2,&resultado);


    printf("\n==========Pila de salida:==========");
    mostrarPila(&resultado);


    return 0;
}
