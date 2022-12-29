#ifndef TDALISTA_H
#define TDALISTA_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Actualizar) (void* elem, const void* actualizador);

typedef struct SNodo
{
    void* elem;
    size_t tamElem;
    struct SNodo *sig, *ant;
}Nodo;

typedef Nodo* Lista;


Nodo *crearNodo(void *elem, size_t tamElem);


void crearLista(Lista *pl);
bool listaVacia(Lista* pl);
bool insertarOrdSDup(Lista *pl, void *elem, size_t tamElem, Cmp cmp, Actualizar act);
bool eliminarPrimero(Lista* pl, void* elem, size_t tamElem);
int eliminarUltimosNdeLaLista(Lista * pl, int n);











#endif // TDALISTA_H
