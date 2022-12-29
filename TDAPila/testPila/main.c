#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TDAPila/TDAPila.h"


int main()
{
    system("chcp 1252 > nul");

    /*Pila pila;

    crearPila(&pila);
    char palabra[] = "cadena 1";
    char palabra2[] = "cadena 2";
    char palabraDestino[10];
    apilar(&pila,palabra,sizeof(palabra));
    apilar(&pila,palabra2,sizeof(palabra2));



    verTope(&pila,&palabraDestino);
    printf("=============================");
    printf("\n%s",palabraDestino);
    printf("\n=============================");



    desapilar(&pila,&palabraDestino,sizeof(palabra));
    verTope(&pila,&palabraDestino);
    printf("\n=============================");
    printf("\n%s",palabraDestino);
    printf("\n=============================");


    verTope(&pila,&palabraDestino);
    printf("\n=============================");
    printf("\n%s",palabraDestino);
    printf("\n=============================");*/

    PilaDin pila;
    char datoEntrada[20] = "Hola Qué tal?";
    char datoSalida[20];

    crearPilaDin(&pila);
    apilarDin(&pila,&datoEntrada,sizeof(datoEntrada));
    //memcpy(&datoSalida,pila->info,sizeof(datoSalida));
    //desapilarDin(&pila,&datoSalida,sizeof(datoSalida));
    verTopeDin(&pila,&datoSalida,sizeof(datoSalida));

    printf("\n=============================");
    printf("\nDato salida: %s",datoSalida);
    printf("\n%d",pilaVaciaDin(&pila));
    printf("\n=============================");

    return 0;
}
