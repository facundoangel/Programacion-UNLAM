#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TDAColaImplementacion.h"
#include "TDAcola.h"

void crearCola(Cola* cp)
{
    cp->frente = 0;
    cp->fondo = 0;
    cp->espacioDisponible = TAM;

}

void vaciarCola(Cola* cp)
{
    cp->frente = 0;
    cp->fondo = 0;
    cp->espacioDisponible = TAM;

}



void incorparDato(Cola* cp,const void* elem, const size_t tamElemento)
{
    size_t cantACopiar = tamElemento;
    size_t cantContigua = (cp->fondo >= cp->frente)? TAM - cp->fondo : cp->frente - cp->fondo;

    memcpy(cp->vector+cp->fondo,elem,MIN(cantACopiar,cantContigua));
    cantACopiar-=MIN(cantACopiar,cantContigua);

    if(cantACopiar>0)
        memcpy(cp->vector,(char *) elem + cantACopiar, cantACopiar);


}


bool encolar(Cola* cp,const void* elem,const size_t tamElemento)
{

    if(sizeof(size_t) + tamElemento >= cp->espacioDisponible)
        return false;


    incorparDato(cp,&tamElemento,sizeof(size_t));
    cp->fondo = ((cp->fondo + sizeof(size_t)) <= TAM) ? (cp->fondo + sizeof(size_t)) :  (cp->fondo + sizeof(size_t) - TAM);

    incorparDato(cp,elem,tamElemento);
    cp->fondo = ((cp->fondo + tamElemento) <= TAM) ? (cp->fondo + tamElemento) :  (cp->fondo + tamElemento - TAM);

    cp->espacioDisponible-=tamElemento+sizeof(size_t);


    return true;

}

void retirarDato(Cola* cp, void* elem,const size_t tamElemento)
{
    size_t tamPorLeer = tamElemento;
    size_t cantContigua = (cp->frente < cp->fondo)? (cp->fondo - cp->frente)  : (TAM - cp->frente);
    //size_t cantContigua = TAM - cp->frente;

    memcpy(elem,cp->vector+cp->frente,MIN(tamElemento,cantContigua));
    tamPorLeer-=MIN(tamElemento,cantContigua);

    if(tamPorLeer>0)
        memcpy(((char*) elem) + cantContigua ,cp->vector,tamPorLeer);




}


bool desencolar(Cola* cp, void* elem,const size_t tamElemento)
{
    if(cp->espacioDisponible == TAM)
        return false;

    size_t tamElementoLeido;
    size_t num;

    retirarDato(cp,&tamElementoLeido,sizeof(size_t));
    cp->frente= ((cp->frente+sizeof(size_t))<=TAM)?  (cp->frente + sizeof(size_t)) : (cp->frente + sizeof(size_t) - TAM);
    //printf("\n[desencolar] mensaje en vector: %s",cp->vector+cp->frente);
    num = (unsigned)tamElementoLeido;
    tamElementoLeido = num;



    retirarDato(cp,elem,num);
    cp->frente= ((cp->frente+num)<=TAM)?  (cp->frente + num)  : (TAM - cp->frente + num);

    cp->espacioDisponible+=tamElemento + sizeof(size_t);

    return true;
}


bool colaLlena(Cola* cp)
{
    return cp->espacioDisponible == 0;
}

bool colaVacia(Cola* cp)
{
    return cp->espacioDisponible == TAM;
}
