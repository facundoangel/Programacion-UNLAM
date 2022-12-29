#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#define esVocal(c) ((c)==('a') || (c)==('e') || (c)==('i') || (c)==('o') || (c)==('u') || (c)==('á') || (c)==('é') || (c)==('í') || (c)==('ó') || (c)==('ú'))
#define esLetra(c) (((c)>='a' && (c)<='z') || ((c)>='A' && (c)<='Z') || (c)==('á') || (c)==('é') || (c)==('í') || (c)==('ó') || (c)==('ú'))
#define esEspacio(c) ((c)==' ')
#define esDigito(c) ((c)>='0' && (c)<='9')

typedef struct SNodo{

    void* elem;
    size_t tamElem;
    struct SNodo *hIzq, *hDer;

}NodoA;

typedef  NodoA* Arbol;
typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Accion) (const void* elem, const void* elemAux);


//=============================FUNCIONES GENERALES=======================================
int strLong(char* cad);
void contarVocales(const char* cad, int n);
void ingresarCaracterSeparador(char* cad);
void imprimirElem(const void* elem, const void* elemAux);
int cmpInt(const void* e1, const void* e2);
//=============================PRIMITIVAS ARBOL=======================================
NodoA* crearNodoA(void* elem, size_t tamElem);
void crearArbol(Arbol *pa);
bool insertarEnArbol(Arbol *pa, void* elem, size_t tamElem, Cmp cmp);
void graficarArbolRec(Arbol *pa, Accion acc, int nivel);
void graficarArbol(Arbol *pa, Accion acc);
int contarNodosInternos(Arbol *pa);
int borrarNodo(Arbol* pa);
int podarArbolRec(Arbol *pa, int nivelActual, int nivelPoda);
int podarArbol(Arbol *pa, int nivel);



int main()
{
    //Parte 1.1-a.
    contarVocales("A esta hora, es la hora en que todo deberia funcionar sin problemas.O,no-es-asi?",3);


    //printf("\nresltado: %d",result);
    //Parte 1.1-b.
    ingresarCaracterSeparador("ef sefsef    sefse·$%·$% 3·$%$% $%$%fg");

    int num1 = 1;
    int num2 = 2;
    int num4 = 4;
    int num3 = 3;
    int num5 = 5;
    int num9 = 9;
    int num8 = 8;


    Arbol ar;
    crearArbol(&ar);

    insertarEnArbol(&ar,&num4,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num8,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num2,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num1,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num3,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num9,sizeof(int),cmpInt);
    insertarEnArbol(&ar,&num5,sizeof(int),cmpInt);

    printf("\n=================IMPRESION DE ARBOL====================\n");
    graficarArbol(&ar,imprimirElem);
    int CantNodos = contarNodosInternos(&ar);
    //int NodosElim = borrarNodo(&ar);
    int NodosElim = podarArbol(&ar,2);
    printf("\nCantidad de nodos internos: %d",CantNodos);
    printf("\nCantidad de nodos eliminados: %d",NodosElim);
    graficarArbol(&ar,imprimirElem);
    //printf("\nCantidad de nodos eliminados: %d",NodosElim);


    return 0;
}




int strLong(char* cad)
{
    int cont=0;

    while(*cad)
    {
        cont++;

        cad++;
    }

    return cont;
}

void contarVocales(const char* cad, int n)
{
    int contPalabra=0, contVocales=0;


    while(!esLetra(*cad) && !esDigito(*cad))
        cad++;



    while(*cad)
    {
        if(esLetra(*cad) || esDigito(*cad))
        {
            if(esVocal(*cad))
                contVocales++;
        } else if(esEspacio(*cad))
        {
            if(contVocales>=n)
                contPalabra++;
            contVocales=0;
        }

        cad++;
    }

    //return cont;
    printf("\nhay %d palabras con mas de %d vocales",contPalabra,n);

}

void ingresarCaracterSeparador(char* cad)
{

    char cadenaNueva[strLong(cad)+1];
    char* cadAux = cadenaNueva;

    while(!esLetra(*cad) && !esDigito(*cad))
        cad++;


    while(*cad)
    {

        if(!esLetra(*cad) && !esDigito(*cad))
        {
            *cadAux=';';
            cad++;
            cadAux++;


            while(!esLetra(*cad) && !esDigito(*cad))
                cad++;

            continue;
        }
        *cadAux=*cad;

        cad++;
        cadAux++;
    }

    *cadAux='\0';

    printf("\n%s",cadenaNueva);
}

void imprimirElem(const void* elem, const void* elemAux)
{
    int* num = (int*)elem;

    printf("%d\n",*num);
}

int cmpInt(const void* e1, const void* e2)
{
    int* num1 = (int*)e1;
    int* num2 = (int*)e2;

    return *num1-*num2;
}


//=========================================================================================================
//PRIMITIVAS DE ARBOL

NodoA* crearNodoA(void* elem, size_t tamElem)
{
    NodoA* nue = malloc(sizeof(NodoA));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    memcpy(nue->elem,elem,tamElem);
    nue->hDer=nue->hIzq=NULL;

    return nue;

}

void crearArbol(Arbol *pa)
{
    *pa=NULL;
}

bool insertarEnArbol(Arbol *pa, void* elem, size_t tamElem, Cmp cmp)
{
    NodoA* nue = crearNodoA(elem,tamElem);
    if(!nue)
        return false;

    if(!*pa)
    {
        *pa=nue;
        return true;
    }

    int comparacion = cmp(elem,(*pa)->elem);

    if(comparacion==0)
        return true;

    if(comparacion<0)
        return insertarEnArbol(&(*pa)->hIzq,elem,tamElem,cmp);

    return insertarEnArbol(&(*pa)->hDer,elem,tamElem,cmp);

}

void graficarArbolRec(Arbol *pa, Accion acc, int nivel)
{
    if(!*pa)
        return;

    graficarArbolRec(&(*pa)->hIzq,acc,nivel+1);


    for(int i=1;i<=nivel;i++)
    {
        printf("    ");
    }

    acc((*pa)->elem,NULL);
    graficarArbolRec(&(*pa)->hDer,acc,nivel+1);
}

void graficarArbol(Arbol *pa, Accion acc)
{
    if(!*pa)
        return;

    printf("\n");

    graficarArbolRec(pa,acc,0);
}

int contarNodosInternos(Arbol *pa)
{

    if(!(*pa)->hIzq || !(*pa)->hDer)
        return 0;

    return 1+contarNodosInternos(&(*pa)->hIzq)+contarNodosInternos(&(*pa)->hDer);
}


int borrarNodo(Arbol* pa)
{
    if(!*pa)
        return 0;

    NodoA* nae = *pa;

    int nodosElim = 1+borrarNodo(&(*pa)->hIzq)+borrarNodo(&(*pa)->hDer);

    free(nae->elem);
    free(nae);
    *pa=NULL;

    return nodosElim;
}


int podarArbolRec(Arbol *pa, int nivelActual, int nivelPoda)
{
    if(!*pa)
        return 0;

    if(nivelActual==nivelPoda)
        return borrarNodo(pa);

    return podarArbolRec(&(*pa)->hIzq,nivelActual+1,nivelPoda)+podarArbolRec(&(*pa)->hDer,nivelActual+1,nivelPoda);
}

int podarArbol(Arbol *pa, int nivel)
{
    if(!*pa)
        return 0;

    return podarArbolRec(&(*pa)->hIzq,0 ,nivel)+podarArbolRec(&(*pa)->hDer,0 ,nivel);


}
//=========================================================================================================
