#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b) ((a)>b?(a):(b))

typedef struct SNodo{

    void* elem;
    size_t tamElem;
    struct SNodo* sig;
    struct SNodo* ante;
}NodoA;


typedef NodoA* Arbol;

typedef int (*Cmp) (void* el1, void* el2);
typedef void (*Imprimir) (Arbol* pa,int nivel);
typedef NodoA* (*Leer) (NodoA* nodo,FILE* pf,int pos);
typedef void (*Accion)(Arbol* pa,const char* nombreArch,FILE* pf,Cmp cmp,size_t tamElem,int m);
typedef void (*ImprimirIndice) (void* elem);
typedef void (*Actualizar) (void* elem1, void* elem2);

void crearArbol(Arbol* pa);
NodoA* crearNodoA(void* elem, size_t tamElem);
int compararElem(void* elem1, void* elem2);
NodoA* insertarNodoA(Arbol* pa,void* elem, size_t tamElem,Cmp cmp);
bool insertarNodoAIterativa(Arbol* pa,void* elem, size_t tamElem,Cmp cmp);
Arbol* buscarEnArbol(Arbol* pa,void* elem,size_t tamElem, Cmp cmp);
bool eliminarNodoA(Arbol* pa,void* elem,size_t tamElem, Cmp cmp);
bool vaciarArbol(Arbol* pa);
bool buscarYEliminarRama(Arbol* pa,void* elem,size_t tamElem, Cmp cmp);
bool buscarYEliminarNodoA(Arbol* pa,void* elem,size_t tamElem, Cmp cmp);
bool recorrerArbolPre(Arbol *pa);
bool recorrerArbolOrden(Arbol *pa);
bool recorrerArbolPos(Arbol *pa);
int contarNodos(Arbol *pa);
int contarNodosXNivelRec(Arbol *pa,int nivel,int nivelStop);
int contarNodosXNivel(Arbol *pa,int nivel);
int contarNiveles(Arbol *pa);
void imprimirNodo(Arbol* pa,int n,ImprimirIndice imp);
void graficarARbolRec(Arbol* pa, int nivel, ImprimirIndice imp);
void graficarARbol(Arbol* pa, ImprimirIndice imp);
bool esArbolCompleto(Arbol *pa);
bool esArbolBalanceadoRec(Arbol *pa,int nivel,int ultNivel);
bool esArbolBalanceado(Arbol *pa);
bool esArbolAVL(Arbol *pa);
bool cargarArchivoEnArbol(Arbol* pa,FILE* pf,Cmp cmp,Accion acc,size_t tamElem,const char* nombreArch);
int cargarArchivoEnArbolRec(Arbol* pa,FILE* pf,Cmp cmp,Accion acc,size_t tamElem,const char* nombreArc,int li,int ls);
bool buscarElemetoEnArbolBusqueda(Arbol* pa,void* elem, size_t tamElem, Actualizar act, Cmp cmp);


#endif // ARBOL_H_INCLUDED
