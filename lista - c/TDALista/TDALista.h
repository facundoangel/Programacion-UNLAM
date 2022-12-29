#ifndef TDALISTA_H
#define TDALISTA_H

#include "TDAListaImpl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (void* elem,TNodo* pl);


void crearLista(Lista *pl);
void vaciarLista(Lista *pl);
int comparar(void* elem, TNodo* nodo);
int InsertarEnListaOrdSinDup(Lista* pl,void* elem, size_t tamElemento, Cmp cmp);
int InsertarEnListaDesordAlFinal(Lista* pl,void* elem, size_t tamElemento);
int InsertarEnListaDesordSinDup(Lista* pl,void* elem, size_t tamElemento);
bool EliminarElementoListaOrd(Lista* pl,void* elem, size_t tamElemento, Cmp cmp);
bool leerPrimerElemento(Lista* pl,void* elem, size_t tamElemento);
bool mostrarLista(Lista* pl);

#endif // TDALISTA_H
