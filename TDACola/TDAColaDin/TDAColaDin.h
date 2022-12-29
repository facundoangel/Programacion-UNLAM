#ifndef TDACOLADIN_H_INCLUDED
#define TDACOLADIN_H_INCLUDED

#include "TDAColaDinImpl.h"
#include <stdbool.h>

#define MIN(a,b) ((a)<(b)? (a) : (b))

void crearCola(Cola* cp);
void vaciarCola(Cola* cp);
bool encolarAlInicio(Cola* cp,const void* elem,const size_t tamElemento);
bool encolarAlFin(Cola* cp,const void* elem,const size_t tamElemento);
bool desencolarAlInicio(Cola* cp, void* elem,const size_t tamElemento);
bool desencolarAlFin(Cola* cp, void* elem,const size_t tamElemento);
bool colaLlena(const Cola* cp, const size_t tamElemento);
bool colaVacia(const Cola* cp);


#endif // TDACOLADIN_H_INCLUDED
