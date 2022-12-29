#include "TDAPila.h"
#include "TDAPilaImplEstatica.h"
#include <string.h>
#include <stdio.h>

void crearPila(Pila* pila)
{

    pila->tope=0;

}




void vaciarPila(Pila* pila)
{

    pila->tope=0;

}


bool apilar(Pila* pp, const void* elem, size_t tamElem)
{

    if(tamElem + sizeof(size_t) > TAM_PILA - pp->tope)
            return false;

    memcpy(pp->VPila+pp->tope,elem,tamElem);
    pp->tope+=tamElem;

    *(size_t*) (pp->VPila+pp->tope) = tamElem;
    pp->tope+=sizeof(size_t);

    return true;
}




bool desapilar(Pila* pp,void* elemt, size_t tamElem)
{

    if(pp->tope==0)
        return false;


    unsigned tope = pp->tope;
    tope-=sizeof(size_t);
    size_t tamElemApilado = *((size_t*)(pp->VPila+tope));
    tope-=tamElemApilado;

    memcpy(elemt,pp->VPila+tope,tamElem+1);
    pp->tope=tope;


    return true;
}


bool pilaVacia(const Pila* pp)
{
        return pp->tope == 0;
}

bool pilaLlena(const Pila* pp, size_t tamElem)
{
    return pp->tope == tamElem;
}


void verTope(const Pila* pp,void* elemDestino)
{
    size_t tamElement;
    unsigned tope = pp->tope;
    tope -= sizeof(size_t);
    memcpy(&tamElement,pp->VPila+tope,sizeof(size_t));
    tope -= tamElement;
    memcpy(elemDestino,pp->VPila+tope,tamElement);
}
