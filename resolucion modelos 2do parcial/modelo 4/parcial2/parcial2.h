#ifndef PARCIAL2_H_INCLUDED
#define PARCIAL2_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../TDAArbol/TDAArbol/arbol.h"
#include "../../../TDACola/TDACola/TDACola.h"
#include "..\..\..\TDACola\TDAColaDin/TDAColaDin.h"
//#include "../../../TDAListaDobleEnlace/TDAListaDobleEnlace/ListaDobleEnlace.h"

//typedef struct SNodo{
//
//    void* info;
//    size_t tamElemento;
//    struct SNodo* sig;
//    struct SNodo* ant;
//
//}Nodo;

typedef struct
{

    char codProd[10];
    int indice;

} Indice;

typedef struct
{

    int d;
    int m;
    int a;

} Fecha;

typedef struct
{

    Fecha fecha;
    int codClie;
    char codProd[10];
    int cantPedida;

} Pedido;

typedef struct
{

    char codProd[10];
    char descripcion[25];
    float pu;
    int stock;

} Producto;

void crearArchivos();
int comparar(void *a, void *b);
void leerRegistro(Arbol *pa, char *nombreArch, FILE *pf, Cmp cmp, size_t tamElem, int m);
void imprimirIndice(void *elem);

#endif // PARCIAL2_H_INCLUDED
