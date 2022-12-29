#ifndef SUMA_H_INCLUDED
#define SUMA_H_INCLUDED

#include "../TDAPila/TDAPila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define ABS(a) ((a)<0 ? -(a) : (a))
#define esNumero(c) ((c)>='0' && (c)<='9')

void IngresarNumeros(char* num1,char* num2);
void inicializarPila(Pila* p1,char* num1);
void igualarLongitud(char* num1,char* num2);
void sumarPilas(Pila* p1, Pila* p2, Pila* resultado);
void mostrarPila(Pila* pp);

#endif // SUMA_H_INCLUDED
