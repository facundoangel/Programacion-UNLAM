#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Matematica/Matematica.h"

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
#define TDA_LISTA_SIMPLE
//#define TDA_LISTA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include "../SolucionAlumnos/Nota.h"
#include "../SolucionAlumnos/EstadoAlumnoMateria.h"
#include <string.h>
#include <math.h>
#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

#define MIN(a,b) ((a)<(b)? (a) : (b))

void procesarLista_ALU(Lista* plAM);
int cmpAlumno_alu(const void* e1, const void* e2);
void actNota_alu(void* actualizado, const void* actualizador);
void notaFinal(void* elem, void* datosAccion);
int cmpNota_alu(const void* e1, const void* e2);


void recorrerLista_ALU(Lista* pl,Accion acc,void* elemAccion);

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
	recorrerLista_ALU(&listaAM, mostrarEstadoAM, NULL);

	return 0;
}

#ifdef TDA_LISTA_SIMPLE
bool eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return false;

    Nodo* nodo = *pl;

    *pl=nodo->sig;

    memcpy(elem,nodo->elem,MIN(tamElem,nodo->tamElem));

    free(nodo->elem);
    free(nodo);


    return true;
}


Nodo* crearNodoD(const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*) malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->sig=NULL;
    memcpy(nue->elem,elem,tamElem);

    return nue;
}

bool insertarEnListaOrdCDup_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{

    Nodo *nue = crearNodoD(elem,tamElem);
    if(!nue)
        return false;

    while(*pl && cmp((*pl)->elem,elem)<0)
        pl=&(*pl)->sig;

    nue->sig=*pl;
    *pl=nue;


    return true;
}

void crearLista_ALU(Lista *pl)
{
    *pl = NULL;
}

void recorrerLista_ALU(Lista* pl,Accion acc,void* elemAccion)
{
    if(!*pl)
        return;

    Nodo* nodo = *pl;

    while(nodo)
    {
        acc(nodo->elem,elemAccion);
        nodo=nodo->sig;
    }

}

#endif // TDA_LISTA_SIMPLE

#ifdef TDA_LISTA_DOBLE
    bool eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem)
    {
        if(!*pl)
            return false;

        NodoD* nodo = *pl;

        //  RETROCESO AL INICIO
        while(nodo->ant)
            nodo=nodo->ant;


        NodoD *nodoSig = nodo->sig;

        *pl=nodoSig;
        if(nodoSig)
            nodoSig->ant=NULL;


        memcpy(elem,nodo->elem,min(tamElem,nodo->tamElem));

        free(nodo->elem);
        free(nodo);

        return true;


    }


    NodoD* crearNodoD(const void* elem, size_t tamElem)
    {
        NodoD* nue = (NodoD*) malloc(sizeof(NodoD));
        nue->elem = malloc(tamElem);

        if(!nue || !nue->elem)
            return NULL;

        nue->tamElem=tamElem;
        nue->sig=nue->ant=NULL;
        memcpy(nue->elem,elem,tamElem);

        return nue;
    }

    bool insertarEnListaOrdCDup_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
    {

        //CASO LISTA VACIA
        if(!*pl)
        {
            NodoD* nue = crearNodoD(elem,tamElem);
            if(!nue)
                return false;
            *pl=nue;
            return true;
        }

        //CASO LISTA CON ELEMENTOS
        NodoD* nodo= *pl;

        int comparacion = cmp(elem,nodo->elem);

        //CREO NODO
        NodoD* nue = crearNodoD(elem,tamElem);
        if(!nue)
            return false;




        //DATO MENOR
        if(comparacion<0 || comparacion==0)
        {
            NodoD* nodoAnt = nodo->ant;

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
        //DATO MAYOR
        else if (comparacion>0)
        {
            NodoD* nodoSig = nodo->sig;

            while(nodoSig && cmp(nodoSig->elem,elem)<0)
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


        return true;
    }

#endif // TDA_LISTA_IMPL_DINAMICA


int compararEstadosXDNI(const void* elem1,const void* elem2)
{
    EstadoAlumnoMateria *est1 = (EstadoAlumnoMateria*) elem1;
    EstadoAlumnoMateria *est2 = (EstadoAlumnoMateria*) elem2;

    if((est1->dni-est2->dni)!=0)
        return est1->dni-est2->dni;

    return strcmpi(est1->materia,est2->materia);
}

int compararEstadosXNota(const void* elem1,const void* elem2)
{
    EstadoAlumnoMateria *est1 = (EstadoAlumnoMateria*) elem1;
    EstadoAlumnoMateria *est2 = (EstadoAlumnoMateria*) elem2;

    return est2->notaFinal-est1->notaFinal;

}

void calcularNota(EstadoAlumnoMateria *est)
{

    int nota1 = max(est->notaP1,est->notaR1);
    int nota2 = max(est->notaP2,est->notaR2);

    //LOGICA DE CALIFICACION

    if(nota1>=7 && nota2>=7)
    {
        est->condicion=PR;
        est->notaFinal=(nota1+nota2)/2;
        est->notaFinal+=(nota1+nota2)%2;
        return;
    }

    if(nota1>=4 && nota2>=4)
    {
        est->condicion=CU;
        est->notaFinal=(nota1+nota2)/2;
        est->notaFinal+=(nota1+nota2)%2;
        return;
    }

    if((nota1>=4 && nota2<4) || (nota1<4 && nota2>=4))
    {
        est->condicion=RE;
        est->notaFinal=2;
        return;
    }

    est->condicion=AU;

}

void procesarLista_ALU(Lista* plAM)
{

    //UNIFICO LOS REGISTROS Y ELIMINO LOS DUPLICADOS
    Lista listOrdNotas, listFinal;
    crearLista_ALU(&listOrdNotas);
    crearLista_ALU(&listFinal);
    EstadoAlumnoMateria est, estAnt;

    //CONFIGURO CASO INICIAL
    estAnt.dni=-1;
    strcpy(estAnt.materia,"");

    while(!listaVacia(plAM))
    {
        eliminarDeListaPrimero_ALU(plAM,&est,sizeof(EstadoAlumnoMateria));
        insertarEnListaOrdCDup_ALU(&listOrdNotas,&est,sizeof(EstadoAlumnoMateria),compararEstadosXDNI);
    }
    //printf("\n");
    //recorrerLista(&listOrdNotas, mostrarEstadoAM, NULL);
    eliminarDeListaPrimero_ALU(&listOrdNotas,&estAnt,sizeof(EstadoAlumnoMateria));
    eliminarDeListaPrimero_ALU(&listOrdNotas,&est,sizeof(EstadoAlumnoMateria));
    while(!listaVacia(&listOrdNotas))
    {

        if(estAnt.dni==est.dni && strcmpi(estAnt.materia,est.materia)==0)
        {
            est.notaP1+=estAnt.notaP1;
            est.notaP2+=estAnt.notaP2;
            est.notaR1+=estAnt.notaR1;
            est.notaR2+=estAnt.notaR2;
        } else{
            calcularNota(&estAnt);
            insertarEnListaOrdCDup_ALU(&listFinal,&estAnt,sizeof(EstadoAlumnoMateria),compararEstadosXNota);
        }


        estAnt=est;
        eliminarDeListaPrimero_ALU(&listOrdNotas,&est,sizeof(EstadoAlumnoMateria));
    }



    //TRATO AL ELEMENTO FALTANTE
     if(estAnt.dni==est.dni && strcmpi(estAnt.materia,est.materia)==0)
    {
        est.notaP1+=estAnt.notaP1;
        est.notaP2+=estAnt.notaP2;
        est.notaR1+=estAnt.notaR1;
        est.notaR2+=estAnt.notaR2;
    }
    calcularNota(&est);
    insertarEnListaOrdCDup_ALU(&listFinal,&est,sizeof(EstadoAlumnoMateria),compararEstadosXNota);


    *plAM=listFinal;

}
