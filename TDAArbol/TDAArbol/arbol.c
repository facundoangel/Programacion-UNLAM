#include "arbol.h"

#define TODO_BIEN 0
#define ERRO_PUNTERO_NULO 1
#define MEM_INSUF 2
#define ERROR 3

void crearArbol(Arbol* pa)
{
    *pa = NULL;
}

NodoA* crearNodoA(void* elem, size_t tamElem)
{
    NodoA* nue = (NodoA* ) malloc(sizeof(NodoA));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        return NULL;

    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem=tamElem;
    nue->sig=NULL;
    nue->ante=NULL;

    return nue;
}

int compararElem(void* elem1, void* elem2)
{

    int *num1, *num2;

    num1 = (int*) elem1;
    num2 = (int*) elem2;

    return *num1 - *num2;

}


NodoA* insertarNodoA(Arbol* pa,void* elem, size_t tamElem,Cmp cmp)
{
    //int resultado = -1;
    if(!*pa)
    {
        NodoA* nue = crearNodoA(elem,tamElem);
        if(!nue) return false;
        *pa=nue;
        return *pa;
    }

    int resultado=cmp(elem,(*pa)->elem);



    if(resultado<0)
    {
        insertarNodoA(&(*pa)->ante,elem,tamElem,cmp);

    }
    if(resultado>0)
    {

        insertarNodoA(&(*pa)->sig,elem,tamElem,cmp);

    }


    return *pa;
}

bool insertarNodoAIterativa(Arbol* pa,void* elem, size_t tamElem,Cmp cmp)
{
    //int resultado = -1;
    if(!*pa)
    {
        NodoA* nue = crearNodoA(elem,tamElem);
        if(!nue) return false;
        *pa=nue;
        return true;
    }

    int resultado=cmp(elem,(*pa)->elem);



    while(resultado!=0)
    {
        if(resultado<0)
            pa=&(*pa)->ante;
        else
            pa=&(*pa)->sig;

        if(!*pa) break;

        resultado=cmp(elem,(*pa)->elem);
    }

    if(resultado==0)
        return true;

    NodoA* nue = crearNodoA(elem,tamElem);
    if(!nue) return false;
    *pa=nue;
    return true;
}


Arbol* buscarEnArbol(Arbol* pa,void* elem,size_t tamElem, Cmp cmp)
{

    //CASO DE ARBOL VACIO
    if(!(*pa))
    {
        printf("\nNo encontrado!!!!!");
        return NULL;
    }

    //CASO DE ENCONTRAR EL ELEMENTO BUSCADO
    int resultado=cmp(elem,(*pa)->elem);

    if(resultado==0)
    return pa;


    return buscarEnArbol(resultado<0?(&(*pa)->ante):(&(*pa)->sig),elem,tamElem,cmp);

}

Arbol* buscarMayorHijoIzq(Arbol* pa)
{
    if(!pa)
        return NULL;

    if((*pa)->sig)
        return buscarMayorHijoIzq(&(*pa)->sig);

    return pa;
}

bool eliminarNodoA(Arbol* pa,void* elem,size_t tamElem, Cmp cmp)
{
    Arbol* ar = buscarEnArbol(pa,elem,tamElem,cmp);

    if(!ar) return false;

    if(!(*ar)->sig && !(*ar)->ante)
    {
        NodoA* nae = *ar;
        ar = NULL;
        free(nae->elem);
        free(nae);
        return true;
    }

    if((!(*ar)->sig && (*ar)->ante) || ((*ar)->sig && !(*ar)->ante))
    {
        NodoA* nae = *ar;
        NodoA* hoja = ((*ar)->sig)? (*ar)->sig : (*ar)->ante ;
        *ar = hoja;


        free(nae->elem);
        free(nae);
        return true;
    }

    if((*ar)->sig && (*ar)->ante)
    {
        NodoA* nae = *ar;
        Arbol* nodoARemplazar = buscarMayorHijoIzq(&(*ar)->ante);
        NodoA* nodoABorrar = *nodoARemplazar;
        memcpy(nae->elem,nodoABorrar->elem,tamElem);
        *nodoARemplazar=NULL;




        free(nodoABorrar->elem);
        free(nodoABorrar);
    }

    return true;
}


bool buscarYEliminarRama(Arbol* pa,void* elem,size_t tamElem, Cmp cmp)
{
    pa = buscarEnArbol(pa,elem,tamElem,cmp);

    if(!*pa) return false;

    return vaciarArbol(pa);
}

bool buscarYEliminarNodoA(Arbol* pa,void* elem,size_t tamElem, Cmp cmp)
{
    pa = buscarEnArbol(pa,elem,tamElem,cmp);

    if(!*pa) return false;

    return eliminarNodoA(pa,elem,tamElem,cmp);
}

bool vaciarArbol(Arbol* pa)
{
    if(!*pa)
        return false;

    NodoA* nae = *pa;
    NodoA* hDer = nae->sig;
    NodoA* hIzq = nae->ante;
    *pa=NULL;

    free(nae->elem);
    free(nae);



    vaciarArbol(&hDer);
    vaciarArbol(&hIzq);

    return true;
}



bool recorrerArbolPre(Arbol *pa)
{


    int numSalida;

    if(!*pa)
        return false;

    memcpy(&numSalida,(*pa)->elem,sizeof(int));
    printf(" %d ",numSalida);

    //RETORNO EN CASO DE QUE EL NODO NO TENGA HIJOS
    if(!(*pa)->sig && !(*pa)->ante)
        return true;


    //EN CASO DE QUE EL NODO TENGA HIJOS LOS IMPRIMO EN PANTALLA
    printf("(");
    if((*pa)->sig)
        recorrerArbolPre(&(*pa)->sig);
    else
        printf(" X ");
    printf(",");
    if((*pa)->ante)
        recorrerArbolPre(&(*pa)->ante);
    else
        printf(" X ");
    printf(")");


    return true;

}

bool recorrerArbolOrden(Arbol *pa)
{
    int numSalida;

    if(!*pa)
        return false;


    if((*pa)->ante || (!(*pa)->ante && (*pa)->sig))
    {
        printf("(");
        if((*pa)->ante)
            recorrerArbolOrden(&(*pa)->ante);
        else
            printf(" X ");
        printf(")");

    }


    memcpy(&numSalida,(*pa)->elem,sizeof(int));
    printf(" %d ",numSalida);


    if((*pa)->sig || (!(*pa)->sig && (*pa)->ante))
    {
        printf("(");
        if((*pa)->sig)
            recorrerArbolOrden(&(*pa)->sig);
        else
            printf(" X ");
        printf(")");

    }

    return true;

}

bool recorrerArbolPos(Arbol *pa)
{


    int numSalida;

    if(!*pa)
        return false;



    //IMPRIMO RAMAS DEL NODO
    if((*pa)->sig || (*pa)->ante)
    {
         printf("(");
        if((*pa)->ante)
            recorrerArbolPos(&(*pa)->ante);
        else
            printf(" X ");
        printf(",");
        if((*pa)->sig)
            recorrerArbolPos(&(*pa)->sig);
        else
            printf(" X ");
        printf(")");
    }




    //IMPRIMO VALOR DEL ELEMENTO DEL NODO
    memcpy(&numSalida,(*pa)->elem,sizeof(int));
    printf(" %d ",numSalida);


    return true;

}


int contarNodos(Arbol *pa)
{
    if(!*pa) return 0;

    return 1+contarNodos(&(*pa)->ante)+contarNodos(&(*pa)->sig);

}

int contarNodosXNivelRec(Arbol *pa,int nivel,int nivelStop)
{
    if(!*pa) return 0;

    if(nivel>nivelStop)
        return 0;

    return 1+contarNodosXNivelRec(&(*pa)->ante,nivel+1,nivelStop)+contarNodosXNivelRec(&(*pa)->sig,nivel+1,nivelStop);

}


int contarNodosXNivel(Arbol *pa,int nivel)
{
    if(!*pa) return 0;

    return contarNodosXNivelRec(pa,0,nivel);

}

int contarNiveles(Arbol *pa)
{
    if(!*pa)
        return 0;

    if(!(*pa)->ante && !(*pa)->sig)
        return 1;

    return 1+MAX(contarNiveles(&(*pa)->ante),contarNiveles(&(*pa)->sig));
}

void imprimirNodo(Arbol* pa,int n,ImprimirIndice imp)
{


    NodoA* nodo = *pa;
    printf("\n");

    while(n>0)
    {
        printf("         ");
        n--;
    }


    //printf("%d",*(int*)nodo->elem);
    imp(nodo);
}

void graficarARbolRec(Arbol* pa, int nivel, ImprimirIndice imp)
{
    if(!*pa)
        return;

    graficarARbolRec(&(*pa)->sig,nivel+1,imp);
    imprimirNodo(pa,nivel,imp);
    graficarARbolRec(&(*pa)->ante,nivel+1,imp);
}



void graficarARbol(Arbol* pa, ImprimirIndice imp)
{
    if(!*pa)
        return;
    graficarARbolRec(pa, 0,imp);
}



void graficarARbolIndiceRec(Arbol* pa, int nivel,Imprimir acc)
{
    if(!*pa)
        return;

    graficarARbolIndiceRec(&(*pa)->sig,nivel+1,acc);
    acc(pa,nivel);
    graficarARbolIndiceRec(&(*pa)->ante,nivel+1,acc);
}

void graficarARbolIndice(Arbol* pa,Imprimir acc)
{
    if(!*pa)
        return;
    graficarARbolIndiceRec(pa, 0,acc);
}


bool esArbolCompleto(Arbol *pa)
{
    int cantNodos = contarNodos(pa);
    int cantNiveles = contarNiveles(pa);

    int cantNodosCompletos = pow(2,cantNiveles)-1;

    return cantNodosCompletos == cantNodos;

}

bool esArbolBalanceadoRec(Arbol *pa,int nivel,int ultNivel)
{
    if(!*pa)
        return false;


    if(ultNivel==nivel)
        return true;

    return esArbolBalanceadoRec(&(*pa)->sig,nivel+1,ultNivel) && esArbolBalanceadoRec(&(*pa)->ante,nivel+1,ultNivel);

}

bool esArbolBalanceado(Arbol *pa)
{
    int cantNiveles = contarNiveles(pa);


    return esArbolBalanceadoRec(pa,0,cantNiveles-2);

}


bool esArbolAVL(Arbol *pa)
{
    if(!*pa)
        return true;

    int hHijoDer = contarNiveles(&(*pa)->sig);
    int hHijoIzq = contarNiveles(&(*pa)->ante);

    if(abs(hHijoDer-hHijoIzq)<2)
        return (esArbolAVL(&(*pa)->ante) && esArbolAVL(&(*pa)->sig));
    else
        return false;
}




int cargarArchivoEnArbolRec(Arbol* pa,FILE* pf,Cmp cmp,Accion acc,size_t tamElem,const char* nombreArc,int li,int ls)
{


    if(li>ls)
    {
        *pa=NULL;
        return TODO_BIEN;
    }


    int m = (li+ls) / 2;


    acc(pa,nombreArc,pf,cmp,tamElem,m);


    if(cargarArchivoEnArbolRec(&(*pa)->ante,pf,cmp,acc,tamElem,nombreArc,li,m-1)!=TODO_BIEN)
        return ERROR;


    return cargarArchivoEnArbolRec(&(*pa)->sig,pf,cmp,acc,tamElem,nombreArc,m+1,ls);
}


bool cargarArchivoEnArbol(Arbol* pa,FILE* pf,Cmp cmp,Accion acc,size_t tamElem,const char* nombreArch)
{

    pf = fopen(nombreArch, "rb");
    fseek(pf,0L,SEEK_END);

    int cantRegistro = ftell(pf) / tamElem;



    if(cargarArchivoEnArbolRec(pa,pf,cmp,acc,tamElem,nombreArch,0,cantRegistro-1)!=TODO_BIEN)
        return false;

    fclose(pf);
    return true;
}

bool buscarElemetoEnArbolBusqueda(Arbol* pa,void* elem, size_t tamElem, Actualizar act, Cmp cmp)
{

    if(!*pa)
        return false;


    int resultado = cmp(elem,(*pa)->elem);

    if(resultado==0)
    {
        act(elem,(*pa)->elem);
        return true;
    }

    if(resultado<0)
    {
        return buscarElemetoEnArbolBusqueda(&(*pa)->ante,elem,tamElem,act,cmp);
    }


        return buscarElemetoEnArbolBusqueda(&(*pa)->sig,elem,tamElem,act,cmp);



}
