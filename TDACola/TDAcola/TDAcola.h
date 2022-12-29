#ifndef TDACOLA_H_INCLUDED
#define TDACOLA_H_INCLUDED

#include "TDAColaImplementacion.h"
#include <stdbool.h>

#define MIN(a,b) ((a)<(b)? (a) : (b))

void crearCola(Cola* cp);
void vaciarCola(Cola* cp);
bool encolar(Cola* cp,const void* elem,const size_t tamElemento);
void incorparDato(Cola* cp,const void* elem ,const size_t tamElemento);
bool desencolar(Cola* cp, void* elem,const size_t tamElemento);
void retirarDato(Cola* cp, void* elem,const size_t tamElemento);
bool colaLlena(Cola* cp);
bool colaVacia(Cola* cp);

#endif // TDACOLA_H_INCLUDED
