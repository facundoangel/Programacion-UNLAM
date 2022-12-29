#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED

typedef struct SNodo{

    void* info;
    unsigned tam;
    struct SNodo *sig;

}Nodo;


typedef Nodo* Lista;



#include <stdbool.h>
#include <stdlib.h>
#define TAM_PILA 135
#define PILA_DIN



#define MIN(a,b) ((a) < (b)? (a) : (b))

typedef int (*Cmp) (const void* num1, Nodo* num2);


void crearLista(Lista *pl);
void eliminarLista(Lista *pl);
bool encolar(Lista* pl, const void* elem, size_t tamElem);
bool desencolar(Lista *pl, void* dato, size_t tamElem);
bool verTopeDin(const Lista *pl, void* dato, size_t tamElem);
bool pilaVaciaDin(Lista* pl);
int comparar(const void* num1,Nodo* num2);
int encolarOrdSinDuplicados(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);

#endif // PILACIRCULAR_H_INCLUDED
