#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilaCircular.h"



void crearPilaDin(PilaDin *TPila)
{

    *TPila = NULL;

}

void vaciarPilaDin(PilaDin *TPila)
{

    *TPila = NULL;

}



bool apilarDin(PilaDin* TPila, const void* elem, size_t tamElem)
{

    Nodo *NodoNuevo;
    NodoNuevo = (Nodo *) malloc(sizeof(Nodo));
    NodoNuevo->info = malloc(sizeof(tamElem));



    if(NodoNuevo==NULL || NodoNuevo->info==NULL)
    {
        printf("\nERROR: No hay suficiente memoria");
        return 0;

    }

    NodoNuevo->tam = tamElem;
    memcpy(NodoNuevo->info,elem,tamElem);


    if(!*TPila)
    {
        NodoNuevo->sig = NodoNuevo;//1
        *TPila = NodoNuevo;//2

    }
    else
    {

        NodoNuevo->sig = (*TPila)->sig;//1
        (*TPila)->sig = NodoNuevo;//3
        //*TPila = NodoNuevo;//2


    }












  return 1;

}


bool desapilarDin(PilaDin *TPila, void* dato, size_t tamElem)
{
    Nodo* nodo=*TPila;
    if(*TPila==NULL)
        return 0;



    Nodo* nodoSig = (*TPila)->sig;
    if(nodo == nodoSig)
    {
        memcpy(dato,nodo->info,sizeof(tamElem));
        *TPila=NULL;
        return 1;

    }

    Nodo *NodoABorrar = nodoSig;
    memcpy(dato,NodoABorrar->info,MIN(NodoABorrar->tam,tamElem));
    (*TPila)->sig = NodoABorrar->sig;



    free(NodoABorrar);


    return 1;

}


bool verTopeDin(const PilaDin *TPila, void* dato, size_t tamElem)
{
    if(*TPila == NULL)
    {
        printf("\nERROR: pila vacia");
        return 0;

    }

    Nodo *NodoAVer = (*TPila)->sig;
    memcpy(dato,NodoAVer->info,MIN(NodoAVer->tam,tamElem));



    return 1;

}

bool pilaVaciaDin(PilaDin* TPila)
{

    return *TPila == NULL;
}
