#ifndef ENUNCIADOS_H
#define ENUNCIADOS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct SNodo
{

    void *info;
    size_t tamElem;
    struct SNodo *sig;
} Nodo;

typedef struct
{
    Nodo *pri;
    Nodo *ult;
} Cola;

typedef struct
{

    char codProd[11];
    char descripcion[26];
    float pu;
    int stock;

} Producto;

typedef struct
{

    char fecha[11];
    int codCliente;
    char codProd[11];
    int cantPedida;

} Pedidos;


void crearArchivos();
void crearCola(Cola *pl);
bool encolar(Cola *pl, Pedidos pedFaltante, size_t tamElem);
bool colaVacia(Cola *pl);
bool desencolar(Cola *pl, Pedidos *pedFaltante);
void leerLinea(char* linea,Pedidos* ped);
bool cargarPedidos(Cola *pend);
bool generarArchivoFaltantes(Cola *pend);

#endif // ENUNCIADOS_H
