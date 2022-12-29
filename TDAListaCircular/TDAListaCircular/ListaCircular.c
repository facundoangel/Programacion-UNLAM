#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ListaCircular.h"

#define TODO_OK 0
#define ELEMENTO_DUPLICADO 1;
#define MEMORIA_INSUF 2;




void crearLista(Lista *pl)
{

    *pl = NULL;

}

void eliminarLista(Lista *pl)
{

    *pl = NULL;

}

int comparar(const void* num1, Nodo* num2)
{
    int numero1, numero2;

    memcpy(&numero1,num1,sizeof(numero1));
    memcpy(&numero2,num2->info,sizeof(numero2));

    return numero1-numero2;
}

Nodo* crearNodo(const void* elem, size_t tamElem)
{
    Nodo* nue=(Nodo*) malloc(sizeof(Nodo));
    nue->info = malloc(tamElem);

    if(nue==NULL || nue->info==NULL)
    {
        printf("\nError: Memoria insuf");
        return NULL;
    }

    memcpy(nue->info,elem,tamElem);
    nue->tam=tamElem;

    return nue;
}

int encolarOrdSinDuplicados(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{

    Nodo *inicio = *pl;
    int resultado;

    //EVALUO CASO PARTICULAR DONDE HAY UN SOLO NODO EN LA LISTA CIRCULAR
    if(*pl && (inicio==(*pl)->sig))
    {
        Nodo *nodo = crearNodo(elem,tamElem);

        if(!nodo)
            return MEMORIA_INSUF;

        nodo->sig=*pl;
        (*pl)->sig=nodo;


        if(cmp(elem,*pl)>0)
        {
            *pl=nodo;
        }

        return TODO_OK;

    }

    Nodo *nodo = crearNodo(elem,tamElem);

    if(!nodo)
        return MEMORIA_INSUF;

    if(!*pl)
    {
        nodo->sig=nodo;
        *pl=nodo;
        return TODO_OK;
    }
    // 2 ->10
    //  5
    while(*pl && cmp(elem,*pl)>0)
    {
        pl=&(*pl)->sig;

    }

    if(*pl && cmp(elem,*pl)==0)
        return ELEMENTO_DUPLICADO;
    nodo->sig=*pl;
    *pl=nodo;

//    nodo->sig=(*pl)->sig;
//    (*pl)->sig=nodo;
    //(*pl)->sig=nodo;
    //*pl=nodo;

    while(*pl != inicio)
        pl=&(*pl)->sig;


    return TODO_OK;
}

bool encolar(Lista* pl, const void* elem, size_t tamElem)
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


    if(!*pl)
    {
        NodoNuevo->sig = NodoNuevo;//1
        *pl = NodoNuevo;//2

    }
    else
    {

        NodoNuevo->sig = (*pl)->sig;//1
        (*pl)->sig = NodoNuevo;//3
        *pl = NodoNuevo;//2

    }

  return 1;

}


bool desencolar(Lista *pl, void* dato, size_t tamElem)
{
    Nodo* nodo=*pl;
    if(*pl==NULL)
        return 0;



    Nodo* nodoSig = (*pl)->sig;
    if(nodo == nodoSig)
    {
        memcpy(dato,nodo->info,sizeof(tamElem));
        *pl=NULL;
        free(nodo);
        return 1;

    }

    Nodo *NodoABorrar = nodoSig;
    memcpy(dato,NodoABorrar->info,MIN(NodoABorrar->tam,tamElem));
    (*pl)->sig = NodoABorrar->sig;



    free(NodoABorrar);


    return 1;

}


bool verTopeDin(const Lista *pl, void* dato, size_t tamElem)
{
    if(*pl == NULL)
    {
        printf("\nERROR: pila vacia");
        return 0;

    }

    Nodo *NodoAVer = (*pl)->sig;
    memcpy(dato,NodoAVer->info,MIN(NodoAVer->tam,tamElem));



    return true;

}

bool pilaVaciaDin(Lista* pl)
{

    return *pl == NULL;
}
