#include "Lista.h"

NodoD *crearNodoD(const void *elem, size_t tamElem)
{
    NodoD *nue = (NodoD *)malloc(sizeof(NodoD));
    if (!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if (!nue->elem)
        return NULL;

    nue->ant = nue->sig = NULL;
    memcpy(nue->elem, elem, tamElem);
    nue->tamElem = tamElem;

    return nue;
}
void crearLista(Lista *pl)
{
    *pl = NULL;
}
bool listaVacia(Lista *pl)
{
    return *pl == NULL;
}
bool insertarEnListaOrdCDup(Lista *pl, const void *elem, size_t tamElem, Cmp cmp)
{
    NodoD *nue = crearNodoD(elem, tamElem);
    if (!nue)
        return false;

    if (!*pl)
    {
        *pl = nue;
        return true;
    }

    NodoD *nodo = *pl;
    int resultado = cmp(elem, nodo->elem);

    if (resultado < 0 || resultado == 0)
    {
        NodoD *nodoAnt = nodo->ant;

        while (nodoAnt && cmp(elem, nodoAnt->elem) < 0)
        {
            nodo = nodoAnt;
            nodoAnt = nodo->ant;
        }

        if (nodoAnt)
            nodoAnt->sig = nue;
        nue->ant = nodoAnt;
        nue->sig = nodo;
        nodo->ant = nue;

        *pl = nue;
        return true;
    }

    NodoD *nodoSig = nodo->sig;

    while (nodoSig && cmp(nodoSig->elem, elem) < 0)
    {
        nodo = nodoSig;
        nodoSig = nodo->sig;
    }

    if (nodoSig)
        nodoSig->ant = nue;
    nue->ant = nodo;
    nue->sig = nodoSig;
    nodo->sig = nue;

    *pl = nue;

    return true;
}
bool eliminarPrimero(Lista *pl, void *elem, size_t tamElem)
{
    if (!*pl)
        return false;

    while ((*pl)->ant)
        pl = &(*pl)->ant;

    NodoD *nae = *pl;

    *pl = nae->sig;
    if (*pl)
        (*pl)->ant = NULL;

    memcpy(elem, nae->elem, MIN(tamElem, nae->tamElem));

    free(nae->elem);
    free(nae);

    return true;
}
