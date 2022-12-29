/*****************************************************************************************************************
** Apellido/s, Nombre/s:  My Tomás                                    											**
*
** DNI:  43.669.624                                           													**
**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**
******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

/*****************************************************************************************************************
** Descomente SOLUCION_ALU y comente SOLUCION_DOC, para probar su código: 										**
**																												*/
//	#define SOLUCION_DOC
	#define SOLUCION_ALU
/*
*****************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Cadena/Cadena.h"
#include "../Fecha/Fecha.h"
#include "../Solucion2doParcialCentroTele/Solucion2doParcialCentroTele.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define PATH_CLI 1
#define PATH_PAGOS 2
#define PATH_LISTADO 3

#define MIN(X,Y) X<Y? X:Y

void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado);
bool esPagoMoroso_ALU(Pago* pag);
void actFactImp_ALU (void* actualizado, const void* actualizador);
void actFactImpNull_ALU (void* actualizado, const void* actualizador);
int cmpFacturasImp_ALU(const void* e1, const void* e2);
bool mostrarClientesMorosos(Lista *pl,Arbol *pa,char* nomArchClie, char* nomArchListado);
int cmpClieIndices_ALU(const void* e1, const void* e2);
bool insertarEnListaOrd_ALU(Lista* pl,void* elem,size_t tamElem,Cmp cmp,Actualizar act);
int cmpFacturasImpMorosoasDesc_ALU(const void* e1, const void* e2);
bool mostrarClientesMorosos_ALU(Lista *pl,Arbol *pa,const char* nomArchClie, const char* nomArchListado);
void ordenarLista_ALU(Lista *pl,Cmp cmp,size_t tamElem);


//===================================PRIMITIVAS ARBOL========================================================
bool cargarArbolDeArchivoOrdenado_ALU(Arbol *pa,size_t tamElem,char* nomArch);
NodoA* crearNodoA_ALU(void* elem,size_t tamElem);
bool cargarArbolDeArchivoOrdenadoRec_ALU(Arbol *pa,size_t tamElem,FILE*  pf,int li, int ls);
bool buscarEnArbol_ALU(Arbol *pa,void* elem,size_t tamElem,Cmp cmp);




int main(int argc, char* argv[])
{
	generarArchivoClientes(argv[PATH_CLI]);
	generarArchivoPagos(argv[PATH_PAGOS]);

	mostrarArchivoClientes(argv[PATH_CLI]);

	char nombreIdx[201];
	reemplazarSubcad(argv[PATH_CLI], ".dat", ".idx", nombreIdx, 201);
	mostrarArchivoClientesIdx(nombreIdx);

	mostrarArchivoPagos(argv[PATH_PAGOS]);

	#ifdef SOLUCION_DOC
		procesarPagos(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
	#else
		procesarPagos_ALU(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
	#endif

	getchar();

	return 0;
}


void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado)
{


    //CARGAR ARBOL DE BUSQUEDA CON INDICES
    Arbol arClientes;
    crearArbol(&arClientes);
    cargarArbolDeArchivoOrdenado_ALU(&arClientes,sizeof(IndCli),"Clientes.idx");


    //CREO LA LISTA DE FACTURAS IMPAGAS O PAGADAS TARDE
    Lista listFactTarde, listFactTardeOrd;
    crearLista(&listFactTarde);
    crearLista(&listFactTardeOrd);


    //LEO ARCHIVOS DE PAGOS
    FILE * pfPagos = fopen(pathPagos,"rb");


    Pago pag;
    FacturasImpagasFueraTerm fact;

    fread(&pag,sizeof(Pago),1,pfPagos);

    while(!feof(pfPagos))
    {
        if(esPagoMoroso_ALU(&pag))
        {
            //printf("\nPAGO: cliente:%d  factura:%s  fecha Venc:%d/%d/%d   fecha Pago:%d/%d/%d",pag.nroCliente,pag.nroFactura,pag.fechaVencimiento.dia,pag.fechaVencimiento.mes,pag.fechaVencimiento.anio,pag.fechaPago.dia,pag.fechaPago.mes,pag.fechaPago.anio);
            fact.nroCliente=pag.nroCliente;
            fact.cantFactImpagasFueraTerm=1;
            insertarEnListaOrd_ALU(&listFactTarde,&fact,sizeof(FacturasImpagasFueraTerm),cmpFacturasImp_ALU,actFactImp_ALU);
        }

        fread(&pag,sizeof(Pago),1,pfPagos);
    }

    fclose(pfPagos);

    ordenarLista_ALU(&listFactTarde,cmpFacturasImpMorosoasDesc_ALU,sizeof(FacturasImpagasFueraTerm));

    mostrarClientesMorosos_ALU(&listFactTarde,&arClientes,pathCli,pathListado);

}

//========================================PRIMITIVAS ARBOL====================================================

NodoA* crearNodoA_ALU(void* elem,size_t tamElem)
{
    NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->hDer=nue->hIzq=NULL;
    memcpy(nue->elem,elem,tamElem);


    return nue;
}

bool buscarEnArbol_ALU(Arbol *pa,void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pa)
        return false;

    int resultado = cmp(elem,(*pa)->elem);

    if(resultado==0)
    {
        memcpy(elem,(*pa)->elem,tamElem);
        return true;
    }
    if(resultado<0)
    {
        return buscarEnArbol_ALU(&(*pa)->hIzq,elem,tamElem,cmp);
    }

    return buscarEnArbol_ALU(&(*pa)->hDer,elem,tamElem,cmp);
}

bool cargarArbolDeArchivoOrdenadoRec_ALU(Arbol *pa,size_t tamElem,FILE*  pf,int li, int ls)
{
    if(li>ls)
        return true;

    int m = (li+ls) / 2;

    fseek(pf,m*tamElem,SEEK_SET);

    void* elem = malloc(tamElem);

    fread(elem,tamElem,1,pf);
    NodoA* nue = crearNodoA_ALU(elem,tamElem);
    if(!nue)
        return false;

    *pa=nue;

    free(elem);
    if(!cargarArbolDeArchivoOrdenadoRec_ALU(&(*pa)->hIzq,tamElem,pf,li,m-1))
        return false;



    return cargarArbolDeArchivoOrdenadoRec_ALU(&(*pa)->hDer,tamElem,pf,m+1,ls);

}

bool cargarArbolDeArchivoOrdenado_ALU(Arbol *pa,size_t tamElem,char* nomArch)
{
    FILE *pf= fopen(nomArch,"rb");

    fseek(pf,0L,SEEK_END);

    int cantReg = ftell(pf) / tamElem;


    if(!cargarArbolDeArchivoOrdenadoRec_ALU(pa,tamElem,pf,0,cantReg-1))
        return false;


    fclose(pf);

    return true;
}


//================================PRIMITIVAS LISTA===========================================================000

void ordenarLista_ALU(Lista *pl,Cmp cmp,size_t tamElem)
{
    Lista listAux;
    crearLista(&listAux);

    void* elem = malloc(tamElem);

    while(eliminarDeListaPrimero(pl,elem,tamElem))
    {
        insertarEnListaOrdCDup(&listAux,elem,tamElem,cmp);
    }

    free(elem);

    *pl=listAux;
}

NodoD* crearNodo_ALU(void* elem,size_t tamElem)
{
    NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
    if(!nue)
        return NULL;
    nue->elem=malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->sig=nue->ant=NULL;
    memcpy(nue->elem,elem,tamElem);


    return nue;
}

bool insertarEnListaOrd_ALU(Lista* pl,void* elem,size_t tamElem,Cmp cmp,Actualizar act)
{
    NodoD* nue = crearNodo_ALU(elem,tamElem);
    if(!nue)
        return false;

    if(!*pl)
    {
        *pl=nue;
        return true;
    }


    NodoD* nodo = *pl;

    int resultado = cmp(elem,nodo->elem);

    if(resultado==0)
    {
        act(nodo->elem,elem);
        return true;
    }

    if(resultado < 0)
    {
        NodoD* nodoAnt = nodo->ant;

        while(nodoAnt && cmp(elem,nodoAnt->elem)<0)
        {
            nodo=nodoAnt;
            nodoAnt=nodo->ant;
        }

        if(nodoAnt && cmp(elem,nodoAnt->elem)==0)
        {
            act(nodoAnt->elem,elem);
            return true;
        }

        if(nodoAnt)
            nodoAnt->sig=nue;
        nue->ant=nodoAnt;
        nue->sig=nodo;
        nodo->ant=nue;
        *pl=nue;
        return true;
    }


        NodoD* nodoSig = nodo->sig;

        while(nodoSig && cmp(elem,nodoSig->elem)>0)
        {
            nodo=nodoSig;
            nodoSig=nodo->sig;
        }

        if(nodoSig && cmp(elem,nodoSig->elem)==0)
        {
            act(nodoSig->elem,elem);
            return true;
        }

        if(nodoSig)
            nodoSig->ant=nue;
        nue->ant=nodo;
        nue->sig=nodoSig;
        nodo->sig=nue;
        *pl=nue;


    return true;
}

//================================FUNCIONES VARIAS===========================================================000

bool mostrarClientesMorosos_ALU(Lista *pl,Arbol *pa,const char* nomArchClie, const char* nomArchListado)
{
    if(!*pl || !*pa)
        return false;

    FILE* pf = fopen(nomArchClie,"rb");

    if(!pf)
        return false;


    IndCli cliInd;
    Cliente clie;
    FacturasImpagasFueraTerm fact;

    printf("\nNro Cliente     Nombre            Facturas en mora");
    while(eliminarDeListaPrimero(pl,&fact,sizeof(FacturasImpagasFueraTerm)))
    {
        cliInd.nroCliente=fact.nroCliente;
        if(!buscarEnArbol_ALU(pa,&cliInd,sizeof(IndCli),cmpClieIndices_ALU))
            printf("\nNO ENCONTRADO!!!!!");

        fseek(pf,cliInd.nroReg*sizeof(Cliente),SEEK_SET);
        fread(&clie,sizeof(Cliente),1,pf);
        printf("\n%8d	%-30s%d",clie.nroCliente,clie.nombre,fact.cantFactImpagasFueraTerm);
    }



    fclose(pf);

    return true;
}

void actFactImp_ALU (void* actualizado, const void* actualizador)
{
    FacturasImpagasFueraTerm* fact1 = (FacturasImpagasFueraTerm*) actualizado;

    fact1->cantFactImpagasFueraTerm++;
}

void actFactImpNull_ALU (void* actualizado, const void* actualizador)
{



}

int cmpFacturasImpMorosoasDesc_ALU(const void* e1, const void* e2)
{
    FacturasImpagasFueraTerm* fact1 = (FacturasImpagasFueraTerm*) e1;
    FacturasImpagasFueraTerm* fact2 = (FacturasImpagasFueraTerm*) e2;

    return fact2->cantFactImpagasFueraTerm-fact1->cantFactImpagasFueraTerm;

}

int cmpFacturasImp_ALU(const void* e1, const void* e2)
{
    FacturasImpagasFueraTerm* fact1 = (FacturasImpagasFueraTerm*) e1;
    FacturasImpagasFueraTerm* fact2 = (FacturasImpagasFueraTerm*) e2;

    return fact1->nroCliente-fact2->nroCliente;

}

int cmpClieIndices_ALU(const void* e1, const void* e2)
{
    IndCli* indCli1 = (IndCli*) e1;
    IndCli* indCli2 = (IndCli*) e2;

    return indCli1->nroCliente-indCli2->nroCliente;
}

bool esPagoMoroso_ALU(Pago* pag)
{


    if(pag->fechaPago.dia==1 && pag->fechaPago.mes==1 &&pag->fechaPago.anio==1900)
        return true;

    if(difEnDiasEntreFechas(&pag->fechaVencimiento,&pag->fechaPago)>0)
        return true;

    return false;
}
