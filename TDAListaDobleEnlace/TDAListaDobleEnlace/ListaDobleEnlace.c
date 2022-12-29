#include "ListaDobleEnlace.h"



void crearLista(Lista* pl)
{
    *pl=NULL;
}


void eliminar(Lista* pl)
{
    pl=NULL;
}

Nodo* crearNodo(void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*) malloc(sizeof(Nodo));
    nue->info = malloc(tamElem);

    if(nue == NULL || nue->info == NULL)
    {
        printf("\nError: Memoria insuficiente");
        return NULL;
    }

    memcpy(nue->info,elem,tamElem);
    nue->tamElemento=tamElem;
    nue->ant=NULL;
    nue->sig=NULL;

    return nue;

}

int comparar(void* elem1, void* elem2)
{
    int numero1, numero2;
    Nodo* nodo = (Nodo*) elem2;

    memcpy(&numero1,elem1,sizeof(numero1));
    memcpy(&numero2,nodo->info,sizeof(numero2));

    return numero1-numero2;

}

bool enlistarEnOrdCDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp)
{

    Nodo* nue = crearNodo(elem,tamElem);
    Nodo* nodo = *pl;

    //CASO DE LISTA VACIA
    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    if(*pl)
    {
        if(cmp(elem,*pl)<0 || cmp(elem,*pl)==0)
        {


            Nodo* nodoAnt = nodo->ant;

            while(nodoAnt && cmp(elem,nodoAnt)<0)
            {
                nodo = nodoAnt;
                nodoAnt=nodo->ant;
            }


            if(nodoAnt)
                nodoAnt->sig=nue;
            nue->ant=nodoAnt;
            nue->sig=nodo;
            nodo->ant=nue;




        }
        else{

            Nodo* nodoSig = nodo->sig;

            while(nodoSig && cmp(elem,nodoSig)>0)
            {
                nodo=nodoSig;
                nodoSig=nodo->sig;
            }

            if(nodoSig)
                nodoSig->ant=nue;
            nue->ant=nodo;
            nue->sig=nodoSig;
            nodo->sig=nue;

        }

        *pl=nue;
    }


    return true;
}

bool enlistarDesordSDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp,Actualizar act)
{

    Nodo* nue = crearNodo(elem,tamElem);
    Nodo* nodo = *pl;
    Nodo* ultNodo;

    //CASO DE LISTA VACIA
    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    //BUSCO DUPLICADO Y ACTUALIZO
    while(nodo)
    {
        if(cmp(elem,nodo)==0)
        {
            act(elem,nodo);
            return true;
        }
        if(!nodo->sig)
            ultNodo=nodo;
        nodo=nodo->sig;
    }

    //INSERTO ELEMENTO DESDE EL FINAL
    ultNodo->sig=nue;
    nue->ant=ultNodo;
    nue->sig=NULL;


    return true;
}

void actualizar(void* elem, Nodo* nodo)
{
    return;
}

bool enlistarEnOrdSDup(Lista* pl,void* elem, size_t tamElem,Cmp cmp, Actualizar act)
{

    Nodo* nue = crearNodo(elem,tamElem);
    Nodo* nodo = *pl;

    //CASO DE LISTA VACIA
    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    if(*pl)
    {
        if(cmp(elem,*pl)==0)
        {
            act(elem,*pl);
            return true;
        }

        if(cmp(elem,*pl)<0)
        {


            Nodo* nodoAnt = nodo->ant;

            while(nodoAnt && cmp(elem,nodoAnt)<0)
            {

                nodo = nodoAnt;
                nodoAnt=nodo->ant;
            }


            if( nodoAnt && cmp(elem,nodoAnt)==0)
            {
                act(elem,nodoAnt);
                return true;
            }


            if(nodoAnt)
                nodoAnt->sig=nue;
            nue->ant=nodoAnt;
            nue->sig=nodo;
            nodo->ant=nue;




        }
        else{

            Nodo* nodoSig = nodo->sig;

            while(nodoSig && cmp(elem,nodoSig)>0)
            {

                nodo=nodoSig;
                nodoSig=nodo->sig;
            }

            if( nodoSig && cmp(elem,nodoSig)==0)
            {
                act(elem,nodoSig);
                return true;
            }


            if(nodoSig)
                nodoSig->ant=nue;
            nue->ant=nodo;
            nue->sig=nodoSig;
            nodo->sig=nue;

        }

        *pl=nue;
    }


    return true;
}


bool desenlistar(Lista* pl, void* elem, size_t tamElemento)
{

    if(!*pl)
        return false;

    Nodo* nodoSig = (*pl)->sig;
    Nodo* nodoAnt = (*pl)->ant;
    Nodo* nae = *pl;

    if(nodoSig)
        nodoSig->ant=nodoAnt;
    if(nodoAnt)
        nodoAnt->sig=nodoSig;

    memcpy(elem,nae->info,MIN(tamElemento,nae->tamElemento));

    free(nae->info);
    free(nae);

    if(nodoSig)
        *pl=nodoSig;
    else
        *pl=nodoAnt;


    return true;


}


void borrarNodo(Nodo* nodo)
{
    free(nodo->info);
    free(nodo);
}


bool desenlistarAlInicio(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return false;

    Nodo* nodo = *pl;

    if(!(nodo->ant) && !(nodo->sig))
    {
        *pl=NULL;
        memcpy(elem,nodo->info,tamElem);
        borrarNodo(nodo);
        return true;
    }

    Nodo* nae = nodo;
    nodo=nae->sig;
    nodo->ant=NULL;
    *pl=nodo;

    memcpy(elem,nae->info,tamElem);

    borrarNodo(nae);


    return true;

}

void mostrarNumero(Nodo* nodo)
{
    int numSalida;

    memcpy(&numSalida,nodo->info,sizeof(int));
    printf(" %d ",numSalida);

}

void mostrarLista(Lista* pl, Accion acc)
{
    Nodo* nodo = *pl;

    while(nodo->ant)
    {

        nodo=nodo->ant;
    }



    printf("\n[ ");
    while(nodo)
    {
        acc(nodo);
        nodo = nodo->sig;
    }

    printf("]");

}

bool listaVacia(Lista* pl)
{
    return *pl == NULL;
}
