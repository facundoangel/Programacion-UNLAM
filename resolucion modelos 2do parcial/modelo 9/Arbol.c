#include "Arbol.h"

NodoA* crearNodoA(const void* elem, size_t tamElem)
{
    NodoA* nue = malloc(sizeof(NodoA));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->hDer=nue->hIzq=NULL;
    nue->tamElem=tamElem;
    memcpy(nue->elem,elem,tamElem);

    return nue;
}

void crearArbol(Arbol *pa)
{
    *pa=NULL;
}
bool agregarEnArbol(Arbol *pa, const void* elem, size_t tamElem, Cmp cmp)
{
    NodoA* nue = crearNodoA(elem,tamElem);
    if(!nue)
        return false;

    if(!*pa)
    {
        *pa=nue;
        return true;
    }

    int resultado = cmp(elem,(*pa)->elem);

    if(resultado==0)
    {
        memcpy((*pa)->elem,elem,tamElem);
        return true;
    }

    if(resultado<0)
        return agregarEnArbol(&(*pa)->hIzq,elem,tamElem,cmp);

    return agregarEnArbol(&(*pa)->hDer,elem,tamElem,cmp);

}
bool buscarEnArbol(Arbol *pa, void* elem, size_t tamElem, Cmp cmp)
{

    if(!*pa)
        return false;

    int resultado = cmp(elem,(*pa)->elem);

    if(resultado==0)
    {
        memcpy(elem,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
        return true;
    }

    if(resultado<0)
        return buscarEnArbol(&(*pa)->hIzq,elem,tamElem,cmp);

    return buscarEnArbol(&(*pa)->hDer,elem,tamElem,cmp);
}

void graficarArbolRec(Arbol *pa,Accion acc,int nivel)
{
    if(!*pa)
        return;

    graficarArbolRec(&(*pa)->hIzq,acc,nivel+1);
    for(int i=1;i<=nivel;i++)
    {
        printf("   ");
    }
    acc((*pa)->elem,NULL);
    graficarArbolRec(&(*pa)->hDer,acc,nivel+1);
}

void graficarArbol(Arbol *pa,Accion acc)
{
    if(!*pa)
        return;

    graficarArbolRec(pa,acc,0);
}


bool buscarEnArbolRec(Arbol *pa, void *elem, size_t tamElem, Cmp cmp)
{
    if (!*pa)
        return false;

    int resultado = cmp(elem, (*pa)->elem);

    if (resultado == 0)
    {
        memcpy(elem, (*pa)->elem, MIN(tamElem, (*pa)->tamElem));
        return true;
    }

    if (resultado < 0)
        return buscarEnArbolRec(&(*pa)->hIzq, elem, tamElem, cmp);

    return buscarEnArbolRec(&(*pa)->hDer, elem, tamElem, cmp);
}



