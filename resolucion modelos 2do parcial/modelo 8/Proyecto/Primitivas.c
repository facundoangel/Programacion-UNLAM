#include "Cabecera.h"
#define DEBUG_MODE_INSERTAR_O_ACTUALIZAR 0
#define DEBUG_BUSCAR_EN_LISTA 0
#define DEBUG_ELIMINAR_PRIMERO 0

#define METODO_RECURSIVO


//=======================================PRIMITIVAS LISTA==================================================
#ifndef METODO_RECURSIVO


void crearLista(Lista* pl)
{
    *pl = NULL;
}

bool insertarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp)
{
    tNodo* nue = crearNodo(elem,tamElem);
    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    tNodo* nodo = *pl;

    int resultado = cmp(elem,nodo->info);

    if(resultado<0 || resultado == 0)
    {
        tNodo* nodoAnt = nodo->ant;

        while(nodoAnt && cmp(elem,nodoAnt->info)<0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->sig=nodo;
        nue->ant=nodoAnt;
        nodo->ant=nue;

        *pl=nue;
        return true;

    } else
    {
        tNodo* nodoSig = nodo->sig;

        while(nodoSig && cmp(nodoSig->info,elem)<0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;
    }

    *pl=nue;
    return true;
}

bool insertarOActualizarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar act)
{
    tNodo* nue = crearNodo(elem,tamElem);
    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }

    tNodo* nodo = *pl;

    int resultado = cmp(elem,nodo->info);

    if(resultado==0)
    {
        act(nodo->info,elem);
        return true;
    }

    if(resultado<0)
    {
        tNodo* nodoAnt = nodo->ant;

        while(nodoAnt && cmp(elem,nodoAnt->info)<0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt && cmp(elem,nodoAnt->info)==0)
        {
            act(nodoAnt->info,elem);
            return true;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->sig=nodo;
        nue->ant=nodoAnt;
        nodo->ant=nue;

        *pl=nue;
        return true;

    } else
    {
        tNodo* nodoSig = nodo->sig;

        while(nodoSig && cmp(nodoSig->info,elem)<0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }

        if(nodoSig && cmp(nodoSig->info,elem)==0)
        {
            act(nodoSig->info,elem);
            return true;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;
    }

    *pl=nue;
    return true;
}

bool insertarAlFinal_ALU(Lista *pl,const void* elem, size_t tamElem)
{
    tNodo* nue = crearNodo(elem,tamElem);

    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;

        return true;
    }

    tNodo* nodo = *pl;

    while(nodo->sig)
        nodo=nodo->sig;

    nodo->sig=nue;
     nue->ant=nodo;


     *pl=nue;


     return true;

}


bool buscarEnLista(Lista*pl,void* elem,size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return false;

    tNodo* nodo = *pl;

    int resultado = cmp(elem,nodo->info);

    if(resultado == 0)
    {
        memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
        return true;
    }

    if(resultado<0)
    {
        nodo=nodo->ant;

        while(nodo && cmp(elem,nodo->info)<0)
            nodo=nodo->ant;


        if(nodo && cmp(nodo->info,elem)==0)
        {
            memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
            return true;
        }


    }

    if(resultado>0)
    {

        nodo=nodo->sig;
        while(nodo && cmp(elem,nodo->info)>0)
            nodo=nodo->sig;


        if(nodo && cmp(nodo->info,elem)==0)
        {
            memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
            return true;
        }


    }



    return false;
}

bool eliminarPrimero(Lista *pl,void* elem, size_t tamElem)
{
    if(!*pl)
        return false;

    tNodo* nodo = *pl;

    while(nodo->ant)
        nodo=nodo->ant;

    tNodo* nae = nodo;

    nodo = nae->sig;
    if(nodo)
        nodo->ant=NULL;
    *pl=nodo;

    memcpy(elem,nae->info,MIN(tamElem,nae->tam));
    free(nae->info);
    free(nae);

    return true;
}
#endif // METODO_RECURSIVO


#ifdef METODO_RECURSIVO


void crearLista(Lista* pl)
{
    *pl = NULL;
}

bool insertarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp)
{
    tNodo* nue = crearNodo(elem,tamElem);
    if(!nue)
        return false;

    tNodo* nodo = *pl;
    if(!nodo)
    {
        *pl=nue;
        return true;
    }


    int resultado = cmp(elem,nodo->info);

    if(resultado<0 || resultado == 0)
    {
        tNodo* nodoAnt = nodo->ant;

        if(nodoAnt && cmp(elem,nodoAnt->info)<0)
            return insertarEnOrden(&nodoAnt,elem,tamElem,cmp);

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->sig=nodo;
        nue->ant=nodoAnt;
        nodo->ant=nue;

        *pl=nue;
        return true;

    } else
    {
        tNodo* nodoSig = nodo->sig;

        if(nodoSig && cmp(nodoSig->info,elem)<0)
            return insertarEnOrden(&nodoSig,elem,tamElem,cmp);

        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;
    }

    *pl=nue;
    return true;
}

bool insertarOActualizarEnOrden(Lista *pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar act)
{


    tNodo* nue = crearNodo(elem,tamElem);
    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
        {
            printf("\n*SE INSERTA PRIMER ELEMENTO*");
            getchar();
        }
        return true;
    }


    tNodo* nodo = *pl;
    if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
    {
        t_MedicionesAcum* med1 = (t_MedicionesAcum*)elem;
        t_MedicionesAcum* med2 = (t_MedicionesAcum*)nodo->info;
        printf("\n*COMPARACION* disp Nº%d y disp Nº%d",med1->dispositivo,med2->dispositivo);
        getchar();
    }
    int resultado = cmp(elem,nodo->info);

    if(resultado==0)
    {
        act(nodo->info,elem);
        printf("\n*ACTUALIZACIÓN*");
        getchar();
        return true;
    }

    if(resultado<0)
    {
        tNodo* nodoAnt = nodo->ant;

        if(nodoAnt && cmp(elem,nodoAnt->info)<0)
            return insertarOActualizarEnOrden(&nodoAnt,elem,tamElem,cmp,act);

        if(nodoAnt && cmp(elem,nodoAnt->info)==0)
        {
            act(nodoAnt->info,elem);
            if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
            {
                printf("\n*ACTUALIZACIÓN NUMERO ANTERIOR*");
                getchar();
            }
            return true;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->sig=nodo;
        nue->ant=nodoAnt;
        nodo->ant=nue;

        *pl=nue;
        if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
        {
            printf("\n*SE INSERTA ELEMENTO POR IZQUIERDA*");
            getchar();
        }
        return true;

    } else
    {
        tNodo* nodoSig = nodo->sig;

        if(nodoSig && cmp(nodoSig->info,elem)<0)
            return insertarOActualizarEnOrden(&nodoSig,elem,tamElem,cmp,act);

        if(nodoSig && cmp(nodoSig->info,elem)==0)
        {
            act(nodoSig->info,elem);
            if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
            {
                printf("\n*ACTUALIZACIÓN NUMERO SIGUIENTE*");
                getchar();
            }
            return true;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;
    }

    *pl=nue;
    if(DEBUG_MODE_INSERTAR_O_ACTUALIZAR)
    {
        printf("\n*SE INSERTA ELEMENTO POR DERECHA*");
        getchar();
    }
    return true;
}

bool insertarAlFinal_ALU(Lista *pl,const void* elem, size_t tamElem)
{
    tNodo* nue = crearNodo(elem,tamElem);

    if(!nue)
        return false;
    tNodo* nodo = *pl;
    //tNodo* nodoAnt = (nodo)?nodo->ant:nodo;

    if(!nodo)
    {
        *pl=nue;
        return true;
    }


    if(nodo->sig)
        return insertarAlFinal_ALU(&nodo->sig,elem,tamElem);

    nodo->sig=nue;
    nue->ant=nodo;

     return true;

}


bool buscarEnLista(Lista*pl,void* elem,size_t tamElem, Cmp cmp)
{

    if(!*pl)
    {
        if(DEBUG_BUSCAR_EN_LISTA)
        {
            printf("\nERROR: LISTA VACIA");
            getchar();
        }
        return false;
    }

    tNodo* nodo = *pl;
    if(DEBUG_BUSCAR_EN_LISTA)
        {
            t_Coeficientes* buscado = (t_Coeficientes*) elem;
            t_Coeficientes* obtenido = (t_Coeficientes*) nodo->info;
            printf("\n*SE COMPARA* NODO BUSCADO:%d - NODO OBTENIDO DE LISTA: %d",buscado->disp,obtenido->disp);
            getchar();
        }


    int resultado = cmp(elem,nodo->info);

    if(resultado == 0)
    {
        memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
        if(DEBUG_BUSCAR_EN_LISTA)
        {
            printf("\n*SE ENCONTRO EL ELEMENTO*");
            getchar();
        }
        return true;
    }

    if(resultado<0)
    {
        nodo=nodo->ant;




        if(nodo && cmp(nodo->info,elem)==0)
        {
            memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
            if(DEBUG_BUSCAR_EN_LISTA)
            {
                printf("\n*SE ACTUALIZO ELEMENTO ANTERIOR*");
                getchar();
            }
            return true;
        }

        if(nodo && cmp(elem,nodo->info)<0)
        {
            if(DEBUG_BUSCAR_EN_LISTA)
            {
                printf("\n*SE RETROCEDIO HACIA ATRAS EN LA LISTA*");
                getchar();
            }
            return buscarEnLista(&nodo,elem,tamElem,cmp);
        }


    }

    if(resultado>0)
    {

        nodo=nodo->sig;



        if(nodo && cmp(nodo->info,elem)==0)
        {
            memcpy(elem,nodo->info,MIN(tamElem,nodo->tam));
            if(DEBUG_BUSCAR_EN_LISTA)
            {
                printf("\n*SE ACTUALIZO ELEMENTO SIGUIENTE*");
                getchar();
            }
            return true;
        }

        if(nodo && cmp(elem,nodo->info)>0)
        {
            if(DEBUG_BUSCAR_EN_LISTA)
            {
                printf("\n*SE AVANZO HACIA ADELANTE EN LA LISTA*");
                getchar();
            }
            return buscarEnLista(&nodo,elem,tamElem,cmp);
        }


    }



    return false;
}

bool eliminarPrimero(Lista *pl,void* elem, size_t tamElem)
{
    if(!*pl)
    {
        if(DEBUG_ELIMINAR_PRIMERO)
        {
            printf("\n*LISTA VACIA SE CANCELA ELIMINACIÓN*");
            getchar();
        }
        return false;
    }

    tNodo* nae = *pl;

    if(DEBUG_ELIMINAR_PRIMERO)
    {

        t_MedicionesAcum* medAcum = (t_MedicionesAcum*) nae->info;
        printf("\nMedicion Acumulada: disp:%d medicion:%d cantMediciones:%d",medAcum->dispositivo,medAcum->tempCruda,medAcum->cantMediciones);
        getchar();
    }

    if(nae->ant)
    {
        if(DEBUG_ELIMINAR_PRIMERO)
        {
            printf("\n*SE RETROCEDE HACIA ATRAS EN LA LISTA*");
            getchar();
        }
        return eliminarPrimero(&nae->ant,elem, tamElem);
    }



    tNodo* nodo = nae->sig;
    *pl=nodo;
    if(nodo)
        (*pl)->ant=NULL;

    memcpy(elem,nae->info,MIN(tamElem,nae->tam));
    free(nae->info);
    free(nae);

    if(DEBUG_ELIMINAR_PRIMERO)
    {
        t_MedicionesAcum* medAcum = (t_MedicionesAcum*) nae->info;
        printf("\n*SE LIMINA PRIMER ELEMENTO*->MedAcum: disp:%d medicion:%d cantMediciones:%d",medAcum->dispositivo,medAcum->tempCruda,medAcum->cantMediciones);
        getchar();
    }

    return true;
}



#endif // METODO_RECURSIVO




