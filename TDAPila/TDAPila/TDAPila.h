#ifndef TDAPILA_H_INCLUDED
#define TDAPILA_H_INCLUDED



#include <stdbool.h>
#include <stdlib.h>
#define TAM_PILA 135
#define PILA_DIN



#define MIN(a,b) ((a) < (b)? (a) : (b))



#ifdef PILA_EST

    #include "TDAPilaImplEstatica.h"
/*
    void crearPila(Pila* pila);
    void vaciarPila(Pila* pp);
    bool apilar(Pila* pp, const void* elem, size_t tamElem);
    bool desapilar(Pila* pp, void* elem, size_t tamElem);
    bool pilaLlena(const Pila* pp, size_t tamElem);
    bool pilaVacia(const Pila* pp);
    void verTope(const Pila* pp, void* elem);*/

#endif

#ifdef PILA_DIN

    #include "TDAPilaImplDinamica.h"


    void crearPilaDin(PilaDin *TPila);
    void vaciarPilaDin(PilaDin *TPila);
    bool apilarDin(PilaDin *TPila, const void* elem, size_t tamElem);
    bool desapilarDin(PilaDin *TPila, void* elem, size_t tamElem);
    bool pilaVaciaDin(PilaDin* TPila);
    bool verTopeDin(const PilaDin *TPila, void* dato, size_t tamElem);


#endif








#endif // TDAPILA_H_INCLUDED
