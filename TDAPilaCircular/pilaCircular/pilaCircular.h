#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED

typedef struct SNodo{

    void *info;
    unsigned tam;
    struct SNodo *sig;

}Nodo;


typedef Nodo* PilaDin;



#include <stdbool.h>
#include <stdlib.h>
#define TAM_PILA 135
#define PILA_DIN



#define MIN(a,b) ((a) < (b)? (a) : (b))

void crearPilaDin(PilaDin *TPila);
void vaciarPilaDin(PilaDin *TPila);
bool apilarDin(PilaDin *TPila, const void* elem, size_t tamElem);
bool desapilarDin(PilaDin *TPila, void* elem, size_t tamElem);
bool pilaVaciaDin(PilaDin* TPila);
bool verTopeDin(const PilaDin *TPila, void* dato, size_t tamElem);
bool desapilarNodoPilaCircular(PilaDin *TPila, void *Dato);

#endif // PILACIRCULAR_H_INCLUDED
