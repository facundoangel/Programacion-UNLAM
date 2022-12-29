#include "TDAPila.h"
#include "TDAPilaImplDinamica.h"
#include <string.h>
#include <stdio.h>




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

    Nodo *NodoNuevo = (Nodo *) malloc(sizeof(Nodo));
    NodoNuevo->info = malloc(sizeof(tamElem));


    if(NodoNuevo==NULL || NodoNuevo->info==NULL)
    {
        printf("\nERROR: No hay suficiente memoria");
        return 0;

    }

    NodoNuevo->tam = tamElem;
    memcpy(NodoNuevo->info,elem,tamElem);
    NodoNuevo->sig = *TPila;

    *TPila = NodoNuevo;


  return 1;

}


bool desapilarDin(PilaDin *TPila, void* dato, size_t tamElem)
{
    if(*TPila == NULL)
    {
        printf("\nERROR: pila vacia");
        return 0;

    }

    Nodo *NodoABorrar = *TPila;
    memcpy(dato,NodoABorrar->info,MIN(NodoABorrar->tam,tamElem));
    *TPila = NodoABorrar->sig;


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

    Nodo *NodoAVer = *TPila;
    memcpy(dato,NodoAVer->info,MIN(NodoAVer->tam,tamElem));



    return 1;

}

bool pilaVaciaDin(PilaDin* TPila)
{

    return *TPila == NULL;
}
