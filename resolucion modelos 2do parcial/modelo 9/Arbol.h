#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "comun.h"
#include <stdio.h>

typedef struct Nodo
{

    void *elem;
    size_t tamElem;
    struct Nodo *hIzq, *hDer;

} NodoA;

typedef NodoA *Arbol;

NodoA *crearNodoA(const void *elem, size_t tamElem);

void crearArbol(Arbol *pa);
bool agregarEnArbol(Arbol *pa, const void *elem, size_t tamElem, Cmp cmp);
bool buscarEnArbol(Arbol *pa, void *elem, size_t tamElem, Cmp cmp);
bool buscarEnArbolRec(Arbol *pa, void *elem, size_t tamElem, Cmp cmp);
void graficarArbolRec(Arbol *pa, Accion acc, int nivel);
void graficarArbol(Arbol *pa, Accion acc);

#endif // ARBOL_H_INCLUDED
