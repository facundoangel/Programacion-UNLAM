#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TDAColaDinImpl.h"
#include "TDAcolaDin.h"

void crearCola(Cola* cp)
{
    cp->fin=NULL;
    cp->ini=NULL;
}

void vaciarCola(Cola* cp)
{
    cp->fin=NULL;
    cp->ini=NULL;

}


bool colaLlena(const Cola* cp, const size_t tamElemento)
{
    TNodo *n= (TNodo*)malloc(sizeof(TNodo));
    n->info = malloc(sizeof(tamElemento));

    return n==NULL || n->info==NULL;

}

bool colaVacia(const Cola* cp)
{
    return cp->ini==NULL || cp->fin==NULL;
}



bool encolarAlInicio(Cola* cp,const void* elem,const size_t tamElemento)
{

    TNodo *nue = (TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(sizeof(tamElemento));

    if(nue==NULL || nue->info==NULL)
    {
        printf("\nError: Memoria insuficiente para crear nodo");
        return false;
    }

    nue->tamElemento = tamElemento;
    memcpy(nue->info,elem,tamElemento);
    nue->sig=cp->ini;

    cp->ini=nue;
    if(!cp->fin)
        cp->fin=nue;



    return true;

}


bool encolarAlFin(Cola* cp,const void* elem,const size_t tamElemento)
{

    TNodo *nue = (TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(sizeof(tamElemento));

    if(nue==NULL || nue->info==NULL)
    {
        printf("\nError: Memoria insuficiente para crear nodo");
        return false;
    }

    nue->tamElemento = tamElemento;
    memcpy(nue->info,elem,tamElemento);
    nue->sig=NULL;

    cp->fin->sig=nue;
    cp->fin=nue;
    if(!cp->ini)
        cp->ini=nue;



    return true;

}

bool desencolarAlInicio(Cola* cp, void* elem,const size_t tamElemento)
{

    if(cp->ini==NULL || cp->fin==NULL)
    {
        printf("\nError: Cola Vacia");
        return false;
    }



    TNodo *nae = (TNodo*) malloc(sizeof(TNodo));
    nae->info = malloc(sizeof(tamElemento));

    if(nae==NULL || nae->info==NULL)
    {
        printf("\nError: Memoria insuficiente para crear nodo");
        return false;
    }
    nae=cp->ini;
    nae->info=cp->ini->info;
    cp->ini=nae->sig;


    memcpy(elem,nae->info,MIN(tamElemento,nae->tamElemento));


    free(nae->info);
    free(nae);

    return true;
}

TNodo* buscarNodoAnteUltimo(Cola* cp)
{
    TNodo *nodoActual = cp->ini;
    TNodo *nodoSiguiente = nodoActual->sig;

    while(nodoSiguiente->sig != NULL)
    {
        nodoActual = nodoSiguiente;
        nodoSiguiente = nodoActual->sig;

    }

    return nodoActual;

}

bool desencolarAlFin(Cola* cp, void* elem,const size_t tamElemento)
{

    if(cp->ini==NULL || cp->fin==NULL)
    {
        printf("\nError: Cola Vacia");
        return false;
    }



    TNodo *nae = (TNodo*) malloc(sizeof(TNodo));
    nae->info = malloc(sizeof(tamElemento));

    if(nae==NULL || nae->info==NULL)
    {
        printf("\nError: Memoria insuficiente para crear nodo");
        return false;
    }
    nae=cp->fin;
    nae->info=cp->fin->info;


    TNodo *anteUltimoNodo = buscarNodoAnteUltimo(cp);
    anteUltimoNodo->sig=NULL;
    cp->fin = anteUltimoNodo;

    memcpy(elem,nae->info,MIN(tamElemento,nae->tamElemento));


    free(nae->info);
    free(nae);

    return true;
}

