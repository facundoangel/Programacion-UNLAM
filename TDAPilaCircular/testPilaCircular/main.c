#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../pilaCircular/pilaCircular.h"





void mostrarPila(PilaDin* pp)
{
    int DatoSalida;
    int ultimoNumeroApuntado=0;
    Nodo* ultNodo;
    int i = 0;

    printf("\n[ ");
    while(!pilaVaciaDin(pp))
    {
        ultNodo = (*pp)->sig;
        memcpy(&ultimoNumeroApuntado,ultNodo->info,sizeof(ultimoNumeroApuntado));
        desapilarDin(pp,&DatoSalida,sizeof(DatoSalida));
        printf("%d -> %d ",DatoSalida,ultimoNumeroApuntado);

        if(i<3)
            i++;
        else
            break;


    }
    //memcpy(&ultimoNumeroApuntado,ultNodo->info,sizeof(ultimoNumeroApuntado));
    //ultimoNumeroApuntado = (int) ultimoNumeroApuntado;
    //memcpy(&ultimoNumeroApuntado,ultNodo->info,sizeof(ultimoNumeroApuntado));

    printf("]");

}

int main()
{
    PilaDin pila;

    int datoEntrada = 123;
    int datoSalida;
    crearPilaDin(&pila);
    apilarDin(&pila,&datoEntrada,sizeof(datoEntrada));
    datoEntrada = 432;
    apilarDin(&pila,&datoEntrada,sizeof(datoEntrada));
    datoEntrada = 200;
    apilarDin(&pila,&datoEntrada,sizeof(datoEntrada));
 // mostrarPila(&pila);
    if(desapilarDin(&pila,&datoSalida,sizeof(datoSalida)))
        printf("\nResultado %d",datoSalida);
    if(verTopeDin(&pila,&datoSalida,sizeof(datoSalida)))
        printf("\nResultado %d",datoSalida);
    if(desapilarDin(&pila,&datoSalida,sizeof(datoSalida)))
        printf("\nResultado %d",datoSalida);
    if(desapilarDin(&pila,&datoSalida,sizeof(datoSalida)))
        printf("\nResultado %d",datoSalida);




    return 0;
}
