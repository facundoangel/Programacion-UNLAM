#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "comun.h"
#include <stdio.h>

typedef struct NodoSL{

    void* elem;
    size_t tamElem;
    struct NodoSL *sig,*ant;

}NodoD;

typedef NodoD* Lista;

NodoD* crearNodoD(const void* elem, size_t tamElem);

void crearLista(Lista* pl);
bool listaVacia(Lista* pl);
bool insertarEnListaOrdCDup(Lista* pl, const void* elem,size_t tamElem,Cmp cmp);
bool eliminarPrimero(Lista* pl, void* elem, size_t tamElem);

#endif // LISTA_H_INCLUDED
