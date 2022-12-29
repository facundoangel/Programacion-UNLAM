#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
//#define TDA_LISTA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include "../SolucionAlumnos/Nota.h"
#include "../SolucionAlumnos/EstadoAlumnoMateria.h"
#include <string.h>
#include <math.h>
#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MEM_INSUF 1
#define TODO_OK 0



int cmpNotasXAlumno_alu(const void* e1, const void* e2);
void actAlumno_ALU(void* actualizado, const void* actualizador);
int cmpNotasXNota_alu(const void* e1, const void* e2);
void imprimirNota_ALU(void* elem, void* datosAccion);
void procesarNota_ALU(void* elem, void* datosAccion);
void procesarLista_ALU(Lista* plAM);

void crearLista_ALU(Lista* pl);
int insertarEnListaOrdCDup_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp);
int insertarOActualizarEnListaOrd_ALU(Lista *pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar);
bool eliminarDeListaPrimero_ALU(Lista* pl,void* elem,size_t tamElem);
void recorrerLista_ALU(Lista* pl,Accion accion, void* elemAccion);


int main()
{
	generarArchivo(NOMBRE_ARCHIVO_NOTAS);

	Lista listaAM;
	crearLista(&listaAM);

	cargarLista(&listaAM, NOMBRE_ARCHIVO_NOTAS);

	puts("Lista antes de procesar:");
	recorrerLista(&listaAM, mostrarEstadoAM, NULL);

	procesarLista_ALU(&listaAM);
 	//procesarLista(&listaAM);

	puts("\nLista despues de procesar:");
	recorrerLista(&listaAM, mostrarEstadoAM, NULL);

	return 0;
}

int cmpNotasXAlumno_alu(const void* e1, const void* e2)
{
    EstadoAlumnoMateria* est1 = (EstadoAlumnoMateria*) e1;
    EstadoAlumnoMateria* est2 = (EstadoAlumnoMateria*) e2;

    int resultado = strcmp(est1->apyn,est2->apyn);

    if(resultado!=0)
        return resultado;

    return strcmp(est1->materia,est2->materia);

}

void actAlumno_ALU(void* actualizado, const void* actualizador)
{
    EstadoAlumnoMateria* estActualizado = (EstadoAlumnoMateria*) actualizado;
    EstadoAlumnoMateria* estActualizador = (EstadoAlumnoMateria*) actualizador;

    estActualizado->notaP1+=estActualizador->notaP1;
    estActualizado->notaP2+=estActualizador->notaP2;
    estActualizado->notaR1+=estActualizador->notaR1;
    estActualizado->notaR2+=estActualizador->notaR2;

}

int cmpNotasXNota_alu(const void* e1, const void* e2)
{
    EstadoAlumnoMateria* est1 = (EstadoAlumnoMateria*) e1;
    EstadoAlumnoMateria* est2 = (EstadoAlumnoMateria*) e2;

    return  est2->notaFinal-est1->notaFinal;

}


void imprimirNota_ALU(void* elem, void* datosAccion)
{
    EstadoAlumnoMateria *est = (EstadoAlumnoMateria*) elem;

    printf("\n%s %s %d %d %d %d %d",est->apyn,est->materia,est->notaP1,est->notaP2,est->notaR1,est->notaR2,est->notaFinal);
}

void procesarNota_ALU(void* elem, void* datosAccion)
{
    EstadoAlumnoMateria* est = (EstadoAlumnoMateria*) elem;
    Lista *lista = (Lista*) datosAccion;

    float nota;

    int notaMayor1 = MAX(est->notaP1,est->notaR1);
    int notaMayor2 = MAX(est->notaP2,est->notaR2);

    if(notaMayor1>=7 && notaMayor2>=7)
    {
        est->condicion=PR;
        nota = (float)(notaMayor1 + notaMayor2) / 2;
        est->notaFinal=nota;
        if(nota > (float) est->notaFinal)
            est->notaFinal++;
    }

    else if(notaMayor1>=4 && notaMayor2>=4)
    {
        est->condicion=CU;
        nota = (float)(notaMayor1 + notaMayor2) / 2;
        est->notaFinal=nota;
        if(nota > (float) est->notaFinal)
            est->notaFinal++;
    }

    else if(notaMayor1>0 && notaMayor2>0)
    {
        est->condicion=RE;
        est->notaFinal= 2;
    }


    insertarEnListaOrdCDup_ALU(lista,est,sizeof(EstadoAlumnoMateria),cmpNotasXNota_alu);


}


//=========================================PRIMITIVAS LISTA SIMPLE==============================================

#ifdef TDA_LISTA_IMPL_DINAMICA

Nodo* crearNodo(const void* elem,size_t tamElem)
{
    Nodo* nue = (Nodo*) malloc(sizeof(Nodo));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    memcpy(nue->elem,elem,tamElem);
    nue->sig=NULL;
    nue->tamElem=tamElem;

    return nue;
}

void recorrerLista_ALU(Lista* pl,Accion accion, void* elemAccion)
{
    Nodo* nodo = *pl;

    while(nodo)
    {
        accion(nodo->elem,elemAccion);
        nodo=nodo->sig;
    }
}

bool eliminarDeListaPrimero_ALU(Lista* pl,void* elem,size_t tamElem)
{
    if(!*pl)
        return false;
    Nodo *nae = *pl;

    *pl=nae->sig;

    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));

    free(nae->elem);
    free(nae);

    return true;

}

int insertarOActualizarEnListaOrd_ALU(Lista *pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar)
{
    Nodo *nue = crearNodo(elem,tamElem);

    if(!nue)
        return 1;

    while(*pl && cmp((*pl)->elem,elem)<0)
        pl=&(*pl)->sig;

    if(*pl && cmp((*pl)->elem,elem)==0)
    {
        actualizar((*pl)->elem,elem);
        return 0;
    }

    nue->sig=*pl;
    *pl=nue;


    return 0;
}

int insertarEnListaOrdCDup_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp)
{
    Nodo* nue = crearNodo(elem,tamElem);

    if(!nue)
        return MEM_INSUF;

    while(*pl && cmp((*pl)->elem,elem)<0)
        pl=&(*pl)->sig;

    nue->sig=(*pl);
        *pl=nue;



    return 0;
}



#endif // TDA_LISTA_IMPL_DINAMICA
//==============================================================================================================
//=========================================PRIMITIVAS LISTA DOBLE==============================================
#ifdef TDA_LISTA_IMPL_DINAMICA_DOBLE

void crearLista_ALU(Lista* pl)
{
    (*pl)->sig=NULL;
    (*pl)->ant=NULL;
}

NodoD* crearNodo(const void* elem,size_t tamElem)
{
    NodoD* nue = (NodoD*) malloc(sizeof(NodoD));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    memcpy(nue->elem,elem,tamElem);
    nue->sig=NULL;
    nue->ant=NULL;
    nue->tamElem=tamElem;

    return nue;
}

bool eliminarDeListaPrimero_ALU(Lista* pl,void* elem,size_t tamElem)
{
    if(!*pl)
        return false;



    NodoD* nae = *pl;

    //RETORNO AL INICIO
    while(nae->ant)
        nae=nae->ant;

    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));

    *pl=nae->sig;
    if(*pl)
        (*pl)->ant=NULL;

    free(nae->elem);
    free(nae);

    return true;
}

int insertarEnListaOrdCDup_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp)
{
    NodoD *nue= crearNodo(elem,tamElem);
    if(!nue)
        return MEM_INSUF;
    NodoD* nodo = *pl;

    if(!*pl)
    {
        *pl=nue;
        return TODO_OK;
    }


    int comparacion = cmp(elem,nodo->elem);

    if(comparacion<0)
    {
        NodoD* nodoAnt=nodo->ant;

        while(nodoAnt && cmp(elem,nodoAnt->elem)<0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->ant=nodoAnt;
        nue->sig=nodo;
        nodo->ant=nue;
    }

    if(comparacion>0 ||comparacion==0)
    {
        NodoD* nodoSig=nodo->sig;

        while(nodoSig && cmp(elem,nodoSig->elem)>0)
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
    return TODO_OK;
}

int insertarOActualizarEnListaOrd_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar acc)
{

    NodoD *nue= crearNodo(elem,tamElem);
    if(!nue)
        return MEM_INSUF;
    NodoD* nodo = *pl;

    if(!*pl)
    {
        *pl=nue;
        return TODO_OK;
    }


    int comparacion = cmp(elem,nodo->elem);

    if(comparacion==0)
        acc((*pl)->elem,elem);

    if(comparacion<0)
    {
        NodoD* nodoAnt=nodo->ant;

        while(nodoAnt && cmp(elem,nodoAnt->elem)<0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt && cmp(elem,nodoAnt->elem)==0)
        {
            acc(nodoAnt->elem,elem);
            return TODO_OK;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->ant=nodoAnt;
        nue->sig=nodo;
        nodo->ant=nue;
    }

    if(comparacion>0)
    {
        NodoD* nodoSig=nodo->sig;

        while(nodoSig && cmp(elem,nodoSig->elem)>0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }

        if(nodoSig && cmp(elem,nodoSig->elem)==0)
        {
            acc(nodoSig->elem,elem);
            return TODO_OK;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->ant=nodo;
        nue->sig=nodoSig;
        nodo->sig=nue;
    }
    return TODO_OK;
}

void recorrerLista_ALU(Lista* pl,Accion accion, void* elemAccion)
{
    NodoD* nodo = *pl;

    while(nodo->ant)
        nodo=nodo->ant;

    while(nodo)
    {
        accion(nodo->elem,elemAccion);
        nodo=nodo->sig;
    }
}
#endif // TDA_LISTA_IMPL_DINAMICA_DOBLE


//==============================================================================================================


void procesarLista_ALU(Lista* plAM)
{
    Lista listOrd;
    crearLista(&listOrd);
    Lista listprueba;
    crearLista(&listprueba);


    EstadoAlumnoMateria est;

    while(eliminarDeListaPrimero_ALU(plAM,&est,sizeof(EstadoAlumnoMateria)))
    {
        insertarOActualizarEnListaOrd_ALU(&listOrd,&est,sizeof(EstadoAlumnoMateria),cmpNotasXAlumno_alu,actAlumno_ALU);
    }


    recorrerLista_ALU(&listOrd,procesarNota_ALU,plAM);



}

