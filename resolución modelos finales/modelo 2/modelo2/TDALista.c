#include "TDALista.h"

Nodo *crearNodo(void *elem, size_t tamElem)
{
    Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
    if (!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if (!nue->elem)
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->elem, elem, tamElem);
    nue->sig = nue->ant = NULL;
    nue->tamElem = tamElem;
    return nue;
}

void crearLista(Lista *pl)
{
    *pl = NULL;
}

bool listaVacia(Lista* pl)
{
    return *pl==NULL;
}


bool insertarOrdSDup(Lista *pl, void *elem, size_t tamElem, Cmp cmp, Actualizar act)
{
    Nodo *nue = crearNodo(elem, tamElem);
    if (!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    Nodo* nodo= *pl;

    int resultado = cmp(elem, (*pl)->elem);

    if (resultado == 0)
    {
        act((*pl)->elem, elem);
        return true;
    }

    if (resultado < 0)
    {
        Nodo* nodoAnt = nodo->ant;

        while (nodoAnt && cmp(elem, nodoAnt->elem) < 0)
        {
            nodo = nodoAnt;
            nodoAnt = nodo->ant;
        }

        if (nodoAnt && cmp(elem, nodoAnt->elem) == 0)
        {
            act(nodoAnt->elem, elem);
            return true;
        }

        if (nodoAnt)
            nodoAnt->sig = nue;
        nue->ant = nodoAnt;
        nue->sig = nodo;
        nodo->ant = nue;


        *pl=nue;
        return true;
    }

    Nodo* nodoSig = nodo->sig;

    while (nodoSig && cmp(elem, nodoSig->elem) > 0)
    {
        pl = &nodoSig;
        nodoSig = nodo->sig;
    }

    if (nodoSig && cmp(elem, nodoSig->elem) == 0)
    {
        act(nodoSig->elem, elem);
        return true;
    }

    if (nodoSig)
        nodoSig->ant = nue;
    nue->ant = nodo;
    nue->sig = nodoSig;
    nodo->sig = nue;



    *pl=nue;
    return true;
}



bool eliminarPrimero(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return false;


    while((*pl)->ant)
        pl=&(*pl)->ant;

    Nodo* nae = *pl;

    *pl=nae->sig;
    if(*pl)
        (*pl)->ant=NULL;


    memcpy(elem,nae->elem,MIN(nae->tamElem,tamElem));

    free(nae->elem);
    free(nae);

    return true;

}


int eliminarUltimosNdeLaLista(Lista * pl, int n)
{
    if(!*pl)
        return 0;

    int nodosAnt=0, nodosSig=0;

    Nodo* nodo=*pl;
    Nodo* nae;

    while(nodo->ant)
    {
        nodo=nodo->ant;
        nodosAnt++;
    }

    nodo=*pl;
    while(nodo->sig)
    {
        nodo=nodo->sig;
        nodosSig++;
    }

    if(nodosAnt+nodosSig+1 < n)
        return 0;

    for(int i=0;i<n;i++)
    {
        nae=nodo;
        nodo=nodo->ant;

        free(nae->elem);
        free(nae);
    }

    *pl=nodo;
    if(*pl)
        (*pl)->sig=NULL;

    return 1;
}
