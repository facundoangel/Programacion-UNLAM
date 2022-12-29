#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_LINEA 100
#define MIN(a,b) ((a)<(b)?(a):(b))


typedef int (*Cmp) (const void* e1,const void* e2);
typedef void (*Actualizar) (void* actualizado, const void* actualizador);

typedef struct snodito
{
    void *info;
    unsigned tam;
    struct snodito *sig, *ant;

}tNodo;
typedef tNodo *Lista;


typedef struct {
    int dispositivo;
    int tempCruda;
}t_Mediciones;

typedef struct {
    int dispositivo;
    int tempCruda;
    int cantMediciones;
}t_MedicionesAcum;

typedef struct{
    int disp;
    float ganancia;
    float desplazamiento;

}t_Coeficientes;



int cmpMediciones_ALU(const void* e1, const void* e2);
int cmpCoeficientes_ALU(const void* e1, const void* e2);
int cmpMedicionesAcum(const void* e1, const void* e2);
void actMedAcum(void* actualizado, const void* actualizador);

tNodo* crearNodo(const void* elem, size_t tamElem);
bool leerArchivoCoef(const char* nomArch,Lista* pl);
void leerLinea(char* linea,t_Coeficientes* coef);



//======================================PRIMITIVAS===================================
bool insertarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp);
void crearLista(Lista* pl);
bool buscarEnLista(Lista*pl,void* elem,size_t tamElem, Cmp cmp);
bool insertarAlFinal_ALU(Lista *pl,const void* elem, size_t tamElem);
bool eliminarPrimero(Lista *pl,void* elem, size_t tamElem);
bool insertarOActualizarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar act);

#endif // CABECERA_H_INCLUDED
