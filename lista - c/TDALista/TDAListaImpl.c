#include "TDALista.h"
#include "TDAListaImpl.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define ERROR_DUPLICADO 1
#define TODO_OK 0


void crearLista(Lista *pl)
{
    *pl=NULL;
}

void vaciarLista(Lista *pl)
{
    *pl=NULL;
}

int comparar(void* elem, TNodo* nodo)
{
    int num1, num2;

    memcpy(&num1,elem,sizeof(num1));
    memcpy(&num2,nodo->info,sizeof(num2));

    return num1 - num2;

}

int InsertarEnListaOrdSinDup(Lista* pl,void* elem, size_t tamElemento, Cmp cmp)
{

//    Lista *inicio = pl;


    while(*pl && cmp(elem, *pl)>0)
        pl =  &((*pl)->sig);


    if(*pl && cmp(elem,*pl)==0)
    {
        return ERROR_DUPLICADO;
    }

    TNodo *nue=(TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(sizeof(tamElemento));
    memcpy(nue->info,elem,tamElemento);

    nue->sig =  *pl;
    *pl = nue;

//    pl = inicio;



    return TODO_OK;
}

int InsertarEnListaDesordSinDup(Lista* pl,void* elem, size_t tamElemento)
{
    TNodo *nodo;
    int numero, numeroNodo;

    memcpy(&numero,elem,sizeof(numero));

    while(*pl)
    {
        nodo = *pl;
        memcpy(&numeroNodo,nodo->info,sizeof(numeroNodo));
        if(numeroNodo == numero)
            return ERROR_DUPLICADO;
        pl =  &((*pl)->sig);

    }





    TNodo *nue=(TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(sizeof(tamElemento));
    memcpy(nue->info,elem,tamElemento);

    nue->sig =  NULL;
    *pl = nue;





    return TODO_OK;
}

int InsertarEnListaDesordAlFinal(Lista* pl,void* elem, size_t tamElemento)
{

    while(*pl)
        pl = &(*pl)->sig;


    TNodo *nue=(TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(sizeof(tamElemento));
    memcpy(nue->info,elem,tamElemento);

    nue->sig =  NULL;
    *pl = nue;





    return TODO_OK;
}

bool EliminarElementoListaOrd(Lista* pl,void* elem, size_t tamElemento, Cmp cmp)
{


    while(*pl && cmp(elem,*pl)!=0)
        pl=&(*pl)->sig;

    if(!*pl)
        return false;

    TNodo *nae = *pl;
    *pl=nae->sig;



    free(nae->info);
    free(nae);

    return true;
}

bool leerPrimerElemento(Lista* pl,void* elem, size_t tamElemento)
{

    if(!*pl)
        return false;

    TNodo *nae=*pl;
    pl=&(*pl)->sig;

    memcpy(elem,nae->info,MIN(tamElemento,nae->tamElemento));


    free(nae->info);
    free(nae);


    return true;

}

bool mostrarLista(Lista* pl)
{
    int resultado;

    if(!*pl)
        return false;


    printf("\n[");
    while(*pl)
    {
        memcpy(&resultado,(*pl)->info,sizeof(resultado));
        printf("%d ",resultado);
        pl = &(*pl)->sig;
    }
    printf("]\n");



    return true;

}


