#ifndef PARCAIL2_H
#define PARCAIL2_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../TDAListaDobleEnlace/TDAListaDobleEnlace/ListaDobleEnlace.h"


#define TAM_LINEA 100


typedef struct{

    int dni;
    char apyn[30];
    float notas[5];


} Alumno;

typedef struct{
    int dni;
    char apyn[30];
    char condicion;
} CondFinal;

void leerLinea(char* linea,Alumno* alu);
int compararAlumno(void* elem1, void* elem2);
void actualizarNodo(void* elem, Nodo* nodo);
bool leerArchivo(char* archAlumnos,Lista* pl);
void imprimirAlumno(Nodo* nodo);
bool ordenarNotas(Lista* plAlu,Lista* plNot);
void escribirArchivo(Lista* pl);

#endif // PARCAIL2_H
