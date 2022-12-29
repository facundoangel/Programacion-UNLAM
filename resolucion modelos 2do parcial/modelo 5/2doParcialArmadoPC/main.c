#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDALista/TDALista.h"


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2
#define LISTA_VACIA 2
#define ELEMENTO_NO_ENCONTRADO 5

int actualizarComponentes_alu(char* pathComponentes, char* pathArmadoYRep);


int cmpArmYRep_ALU(const void* e1, const void* e2);
int cmpInd_ALU(const void* e1, const void* e2);
void accArmYRep_ALU(void* actualizado, const void* actualizador);
void imprimirArm_ALU(void* dato, void* datosAccion);
void eliminarDuplicadosLista_ALU(Lista* pl);



void cargarArbolRec_ALU(Arbol *pa,size_t tamElem,FILE* pf,int li, int ls);
void cargarArbol_ALU(Arbol *pa,size_t tamElem,char* nomArch);


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);
//
	puts("Componentes antes de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");

    ///int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	///******** Descomente esta línea y comente la de arriba para probar su código ********
    int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK)
	{
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}

//============================================PRIMITIVAS LISTA=================================================

NodoD* crearNodoD_ALU(void* elem, size_t tamElem)
{
    NodoD* nue = (NodoD*) malloc(sizeof(NodoD));
    nue->dato = malloc(tamElem);
    if(!nue || !nue->dato)
        return NULL;

    nue->sig=nue->ant=NULL;
    nue->tamElem=tamElem;
    memcpy(nue->dato,elem,tamElem);

    return nue;

}

bool eliminarDeListaPrimero_ALU(Lista* pl,void* dato, size_t tamElem)
{
    if(!*pl)
        return false;

    NodoD* nodo = *pl;




    //RETORNO AL INICIO DE LA LISTA
    while(nodo->ant)
        nodo=nodo->ant;

    NodoD* nodoSig = nodo->sig;
    if(nodoSig)
        nodoSig->ant=NULL;

    *pl=nodoSig;

    memcpy(dato,nodo->dato,min(nodo->tamElem,tamElem));

    free(nodo->dato);
    free(nodo);

    return true;
}


bool insertarOActualizarEnListaOrd_ALU(Lista* pl,void* elem,size_t tamElem,Cmp cmp,Actualizar act)
{

    NodoD* nue = crearNodoD_ALU(elem,tamElem);

    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }


    NodoD* nodo = *pl;
    int resultado = cmp(elem,nodo->dato);

    if(resultado==0)
    {
        act(nodo->dato,elem);
        return true;
    }

    if(resultado<0)
    {
        NodoD* nodoAnt = nodo->ant;

        while(nodoAnt && cmp(nodoAnt->dato,elem)>0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt && cmp(nodoAnt->dato,elem)==0)
        {
            act(nodoAnt->dato,elem);
            return true;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->ant=nodoAnt;
        nue->sig=nodo;
        nodo->ant=nue;

        return true;
    }

    NodoD* nodoSig = nodo->sig;

        while(nodoSig && cmp(nodoSig->dato,elem)<0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }

        if(nodoSig && cmp(nodoSig->dato,elem)==0)
        {
            act(nodoSig->dato,elem);
            return true;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;


    return true;

}

bool insertarEnListaOrd_ALU(Lista* pl,void* elem,size_t tamElem,Cmp cmp)
{

    NodoD* nue = crearNodoD_ALU(elem,tamElem);

    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }


    NodoD* nodo = *pl;
    int resultado = cmp(elem,nodo->dato);


    if(resultado<0 || resultado==0)
    {
        NodoD* nodoAnt = nodo->ant;

        while(nodoAnt && cmp(nodoAnt->dato,elem)>0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }


        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->ant=nodoAnt;
        nue->sig=nodo;
        nodo->ant=nue;

        return true;
    }

    NodoD* nodoSig = nodo->sig;

        while(nodoSig && cmp(nodoSig->dato,elem)<0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }


        if(nodoSig)
            nodoSig->ant=nue;
        nue->sig=nodoSig;
        nue->ant=nodo;
        nodo->sig=nue;


    return true;

}

void insertarEnListaAlInicio_ALU(Lista* pl,void* elem,size_t tamElem)
{
    NodoD *nue = crearNodoD_ALU(elem,tamElem);

    if(!*pl)
    {
        *pl=nue;
        return;
    }

    NodoD* nodo = *pl;

    while(nodo->ant)
        nodo=nodo->ant;

    nodo->ant=nue;
    nue->sig=nodo;
    *pl=nue;
}

//=============================================================================================================


//============================================PRIMITIVAS ARBOL=================================================

NodoA* creaNodoA(void* elem, size_t tamElem)
{
    NodoA* nue = (NodoA*) malloc(sizeof(NodoA));
    if(!nue)
        return NULL;
    nue->dato = malloc(tamElem);
    if(!nue->dato)
        return NULL;

    nue->hDer=nue->hIzq=NULL;
    nue->tamElem=tamElem;

    memcpy(nue->dato,elem,tamElem);

    return nue;

}


int buscarEnArbol_ALU(Arbol* pa,void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return ELEMENTO_NO_ENCONTRADO;

    int resultado = cmp((*pa)->dato,dato);

    if(resultado == 0)
    {
        memcpy(dato,(*pa)->dato,min(tamElem,(*pa)->tamElem));
        return TODO_OK;
    }

    if(resultado>0)
        return buscarEnArbol_ALU(&(*pa)->hIzq,dato,tamElem,cmp);

    return buscarEnArbol_ALU(&(*pa)->hDer,dato,tamElem,cmp);
}

void cargarArbolRec_ALU(Arbol *pa,size_t tamElem,FILE* pf,int li, int ls)
{
    if(li>ls)
    {
        *pa=NULL;
        return;
    }

    void* elem = malloc(tamElem);
    if(!elem)
        return;

    int m = (li+ls) / 2;

    fseek(pf,m*tamElem,SEEK_SET);
    fread(elem,tamElem,1,pf);
//    printf("\n====================================================");
//    IndComponente* ind = (IndComponente*)elem;
//    printf("\ncodigo:%s indice:%d",ind->codigo,ind->nroReg);
    NodoA* nue = creaNodoA(elem,tamElem);
    if(!nue)
        return;
    *pa=nue;




    cargarArbolRec_ALU(&(*pa)->hIzq,tamElem,pf,li,m-1);
    cargarArbolRec_ALU(&(*pa)->hDer,tamElem,pf,m+1,ls);

    free(elem);
}

void cargarArbol_ALU(Arbol *pa,size_t tamElem,char* nomArch)
{
    FILE* pf = fopen(nomArch,"rb");

    fseek(pf,0L,SEEK_END);

    int cantReg = ftell(pf) / tamElem;


    cargarArbolRec_ALU(pa,tamElem,pf,0,cantReg-1);

    fclose(pf);
}

//=============================================================================================================

int cmpArmYRep_ALU(const void* e1, const void* e2)
{
    ArmadoYRep* arm1 = (ArmadoYRep*) e1;
    ArmadoYRep* arm2 = (ArmadoYRep*) e2;

//    int resultado = arm1->nroOp-arm2->nroOp;
//
//    if(resultado!=0)
//        return resultado;

    return strcmp(arm1->codigo,arm2->codigo);

}

int cmpInd_ALU(const void* e1, const void* e2)
{
    IndComponente* ind1 = (IndComponente*) e1;
    IndComponente* ind2 = (IndComponente*) e2;

//    int resultado = arm1->nroOp-arm2->nroOp;
//
//    if(resultado!=0)
//        return resultado;

    return strcmp(ind1->codigo,ind2->codigo);

}

void accArmYRep_ALU(void* actualizado, const void* actualizador)
{
    ArmadoYRep* arm = (ArmadoYRep*) actualizado;
    ArmadoYRep* armActualizador = (ArmadoYRep*) actualizador;

    arm->cantidad+=armActualizador->cantidad;
    arm->precioUnitario=armActualizador->precioUnitario;
}

void imprimirArm_ALU(void* dato, void* datosAccion)
{
    ArmadoYRep* arm = (ArmadoYRep*) dato;

    printf("\n componente:%s  stock:%d  precio:%.2f",arm->codigo,arm->cantidad,arm->precioUnitario);

}

void eliminarDuplicadosLista_ALU(Lista* pl)
{
    Lista listArmSDup;
    crearLista(&listArmSDup);
    ArmadoYRep arm;
    while(eliminarDeListaPrimero(pl,&arm,sizeof(ArmadoYRep)))
    {
        insertarOActualizarEnListaOrd(&listArmSDup,&arm,sizeof(ArmadoYRep),cmpArmYRep_ALU,accArmYRep_ALU);
    }

    *pl=listArmSDup;
}

void cargarArmadosYRepEnLista_ALU(char* nomArch,Lista* pl)
{
    ArmadoYRep arm;

    FILE *pf = fopen(nomArch,"rb");

    if(!pf)
        return;

    fread(&arm,sizeof(ArmadoYRep),1,pf);


    while(!feof(pf))
    {
        insertarOActualizarEnListaOrd_ALU(pl,&arm,sizeof(ArmadoYRep),cmpArmYRep_ALU,accArmYRep_ALU);
        fread(&arm,sizeof(ArmadoYRep),1,pf);
    }

    fclose(pf);

}



int actualizarComponentes_alu(char* pathComponentes, char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.


    //MODIFICO EXTENSIÒN DE ARCHIVO
    char pathIndices[strlen(pathComponentes)+1];
    strcpy(pathIndices,pathComponentes);
    char *c;
    c = strrchr(pathIndices,'.');
    *c='\0';
    strcat(pathIndices,".idx");



    //CREO Y CARGO EL ARBOL CON LOS INDICES
    Arbol ar;
    cargarArbol_ALU(&ar,sizeof(IndComponente),pathIndices);


    //CARGO LOS ARMADOS Y REPARACIONES DE ArmadosYReparaciones.dat en una Lista
    Lista listArm;
    crearLista(&listArm);
    cargarArmadosYRepEnLista_ALU(pathArmadoYRep,&listArm);
    eliminarDuplicadosLista_ALU(&listArm);



    //ACTUALIZO componentes.dat CON LA LISTA DE ARMADOS Y REPARACIONES CARGADA
    FILE *pfComp = fopen(pathComponentes,"r+b");

    Componente comp;
    IndComponente ind;
    ArmadoYRep arm;

    int debug;
    while(eliminarDeListaPrimero_ALU(&listArm,&arm,sizeof(ArmadoYRep)))
    {
        debug = strcmp(arm.codigo,"MOTHASUSXP567");
        strcpy(ind.codigo,arm.codigo);
        buscarEnArbol_ALU(&ar,&ind,sizeof(IndComponente),cmpInd_ALU);

        fseek(pfComp,ind.nroReg * sizeof(Componente),SEEK_SET);
        fread(&comp,sizeof(Componente),1,pfComp);
        comp.stock-=arm.cantidad;
        comp.precioUnitario=arm.precioUnitario;
        fseek(pfComp,(long int)-sizeof(Componente),SEEK_CUR);
        fwrite(&comp,sizeof(Componente),1,pfComp);
        fseek(pfComp,0L,SEEK_CUR);
    }



    fclose(pfComp);




    return 0;

}


