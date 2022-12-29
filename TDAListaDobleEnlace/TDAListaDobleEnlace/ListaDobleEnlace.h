#ifndef LISTADOBLEENLACE_H
#define LISTADOBLEENLACE_H

#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MIN(a,b) ((a)<(b)? (a) : (b))

typedef struct SNodo{

    void* info;
    size_t tamElemento;
    struct SNodo* sig;
    struct SNodo* ant;

}Nodo;

typedef Nodo* Lista;
typedef int (*Cmp) (void* elem1, void* elem2);
typedef void (*Actualizar) (void* elem, Nodo* nodo);
typedef void (*Accion) (Nodo* nodo);

//funciones auxiliares
void mostrarNumero(Nodo* nodo);
void actualizar(void* elem, Nodo* nodo);
void borrarNodo(Nodo* nodo);

//primitivas lista
void crearLista(Lista* pl);
void eliminar(Lista* pl);
Nodo* crearNodo(void* elem, size_t tamElem);
int comparar(void* elem1, void* elem2);
bool enlistarEnOrdCDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp);
bool enlistarEnOrdSDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp, Actualizar act);
bool enlistarDesordSDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp,Actualizar act);
bool desenlistar(Lista* pl, void* elem, size_t tamElemento);
void mostrarLista(Lista* pl,Accion acc);
bool listaVacia(Lista* pl);
bool desenlistarAlInicio(Lista* pl, void* elem, size_t tamElem);

#endif // LISTADOBLEENLACE_H
