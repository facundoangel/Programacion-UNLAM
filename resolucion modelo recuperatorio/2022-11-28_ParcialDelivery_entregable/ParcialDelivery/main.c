/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: ANGEL, FACUNDO NICOLAS
*
* DNI: 40640923
*
****************************************************************************************
********** Descomente el parcial que debe rendir. Si es el integrador, es P2: **********
***************************************************************************************/
//#define P1
#define P2
/***************************************************************************************
********************* Descomente la solución que quiere probar: ************************
***************************************************************************************/
//#define SOLUCION_DOC
#define SOLUCION_ALU
/**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef P1
	#define TDA_COLA_IMPL_DINAMICA
	#define TDA_LISTA_IMPL_DINAMICA
#endif

#ifdef P2
	#define TDA_COLA_IMPL_DINAMICA_CIRCULAR
	#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#endif

#include "../TDACola/TDACola.h"
#include "../TDALista/TDALista.h"
#include "../SolucionDelivery/TiposDelivery.h"
#include "../SolucionDelivery/SolucionDelivery.h"
#include "../Utilitarias/Utilitarias.h"


#define TAM_LINEA 100
#define MIN(a,b) ((a)>(b)?(a):(b))


void leerLina(char* linea, Pedido* ped);
int cmpRecInd(const void* e1, const void* e2);
int cmpIngInd(const void* e1, const void* e2);
void cambioExtDeArch_ALU(const char* nomArch,char* nomArchInd);


//=======================================PRIMITIVAS LISTA DOBLE=============================================

NodoD* crearNodoD_ALU(const void* elem, size_t tamElem);
bool buscarEnLista_ALU(Lista* pl,void* elem, size_t tamElem,Cmp cmp);
void cargarIndiceEnLista_ALU(const char* nomArch,size_t tamElem,Lista* pl,Cmp cmp);
int insertarEnListaOrd_ALU(Lista *pl,const void* elem,size_t tamElem,Cmp cmp);
int insertarEnListaAlFinal_ALU(Lista *pl, const void* elem, size_t tamElem);



//=======================================PRIMITIVAS COLA CIRCULAR=============================================
Nodo* crearNodo_ALU(void* elem, size_t tamElem);
bool encolar_ALU(Cola* pc,void* elem, size_t tamElem);
bool desencolar_ALU(Cola* pc,void* elem, size_t tamElem);



int main()
{
	generarArchivoPedidos();
	generarArchivoRecetas();
	generarArchivoIngredientes();

	mostrarArchivoPedidos("Pedidos.txt");
	mostrarArchivoRecetas("Recetas.dat");

	puts("Ingredientes antes de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");

	int resp;

#ifdef SOLUCION_DOC
	resp = satisfacerPedidos("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#else
	resp = satisfacerPedidos_ALU("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#endif

	if(resp != TODO_OK)
	{
		puts("Error actualizando los pedidos.");
		return resp;
	}

	puts("Ingredientes despues de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");

	getchar();

	return resp;
}

void leerLina(char* linea, Pedido* ped)
{
    char* c = strchr(linea,'\n');

    if(!c)
    {
        c = strchr(linea,'\0');
        if(!*c)
            return;
    }
    *c='\0';


    c=strrchr(linea,'\t');
    sscanf(c+1,"%d",&ped->cantidad);
    *c='\0';


    c=strrchr(linea,'\t');
    strcpy(ped->codReceta,c+1);
    *c='\0';

    sscanf(linea,"%d",&ped->nroPedido);

}

int cmpRecInd(const void* e1, const void* e2)
{
    IndReceta* ind1 = (IndReceta*) e1;
    IndReceta* ind2 = (IndReceta*) e2;

    return strcmpi(ind1->codReceta,ind2->codReceta);
}

int cmpIngInd(const void* e1, const void* e2)
{
    IndIngrediente* ind1 = (IndIngrediente*) e1;
    IndIngrediente* ind2 = (IndIngrediente*) e2;

    return strcmpi(ind1->codIngr,ind2->codIngr);
}

void cambioExtDeArch_ALU(const char* nomArch,char* nomArchInd)
{
    strcpy(nomArchInd,nomArch);
    char *c=strrchr(nomArchInd,'.');

    *c='\0';
    strcat(nomArchInd,".idx");

}

//=======================================PRIMITIVAS LISTA DOBLE=============================================

NodoD* crearNodoD_ALU(const void* elem, size_t tamElem)
{
    NodoD* nue = (NodoD*) malloc(sizeof(NodoD));
    if(!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->ant=nue->sig=NULL;
    memcpy(nue->elem,elem,tamElem);

    return nue;

}


int insertarEnListaAlFinal_ALU(Lista *pl, const void* elem, size_t tamElem)
{
    NodoD* nue = crearNodoD_ALU(elem,tamElem);

    if(!nue)
        return SIN_MEM;

    NodoD* nodo = *pl;

    if(!nodo)
    {
        *pl=nue;
        return TODO_OK;
    }

    while(nodo->sig)
        nodo=nodo->sig;

    nodo->sig=nue;
    nue->ant=nodo;


    *pl=nue;

    return TODO_OK;
}

int insertarEnListaOrd_ALU(Lista *pl,const void* elem,size_t tamElem,Cmp cmp)
{
    NodoD* nue = crearNodoD_ALU(elem,tamElem);

    if(!nue)
        return SIN_MEM;

    if(!*pl)
    {
        *pl=nue;
        return TODO_OK;
    }

    NodoD* nodo = *pl;
    NodoD* nodoAnt = nodo->ant;


    while(nodo && cmp(elem,nodo->elem)>0)
    {
        nodoAnt=nodo;
        nodo=nodo->sig;
    }

    if(nodoAnt)
        nodoAnt->sig=nue;
    nue->ant=nodoAnt;
    nue->sig=nodo;
    if(nodo)
        nodo->ant=nue;

    *pl=nue;


    return TODO_OK;
}


void cargarIndiceEnLista_ALU(const char* nomArch,size_t tamElem,Lista* pl,Cmp cmp)
{
    FILE *pf=fopen(nomArch,"rb");

    void* elem = malloc(tamElem);
    if(!pf || !elem)
        return;

    fread(elem,tamElem,1,pf);

    while(!feof(pf))
    {
        insertarEnListaAlFinal_ALU(pl,elem,tamElem);
        fread(elem,tamElem,1,pf);
    }

    free(elem);
    fclose(pf);

}


bool buscarEnLista_ALU(Lista* pl,void* elem, size_t tamElem,Cmp cmp)
{

    if(!*pl)
        return false;
    NodoD* nodo = *pl;

    int resultado = cmp(elem,nodo->elem);

    if(resultado==0)
    {
        memcpy(elem,nodo->elem,MIN(nodo->tamElem,tamElem));
        return true;
    }

    if(resultado<0)
    {
        nodo = nodo->ant;

        while(nodo && cmp(elem,nodo->elem)!=0)
            nodo=nodo->ant;

        if(nodo && cmp(nodo->elem,elem)==0)
        {
            memcpy(elem,nodo->elem,MIN(tamElem,nodo->tamElem));
            return true;
        }


    }

    if(resultado>0)
    {
        nodo = nodo->sig;

        while(nodo && cmp(elem,nodo->elem)!=0)
            nodo=nodo->sig;

        if(cmp(nodo->elem,elem)==0)
        {
            memcpy(elem,nodo->elem,MIN(tamElem,nodo->tamElem));
            return true;
        }
    }


    return false;
}

//==============================================================================================================
//=======================================PRIMITIVAS COLA CIRCULAR=============================================

Nodo* crearNodo_ALU(void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*) malloc(sizeof(Nodo));
    if(!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->sig=NULL;
    memcpy(nue->elem,elem,tamElem);

    return nue;


}



bool encolar_ALU(Cola* pc,void* elem, size_t tamElem)
{
    Nodo* nue = crearNodo_ALU(elem,tamElem);

    if(!*pc)
    {
        nue->sig=nue;
        *pc=nue;
        return true;
    }

    Nodo* nodo = *pc;
    nue->sig=nodo->sig;
    nodo->sig=nue;

    *pc=nue;

    return true;
}


bool desencolar_ALU(Cola* pc,void* elem, size_t tamElem)
{
    if(!*pc)
        return false;


    Nodo* nae = (*pc)->sig;
    memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));

    if(nae->sig == nae)
    {
        *pc=NULL;
        return true;
    }

    (*pc)->sig=nae->sig;


    free(nae->elem);
    free(nae);

    return true;
}

//==============================================================================================================


///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que �ste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_ALU(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{


    char nomArchRecInd[strlen(nombreArchRecetas)+1];
    char nomArchIngInd[strlen(nombreArchIngredientes)+1];

    cambioExtDeArch_ALU(nombreArchRecetas,nomArchRecInd);
    cambioExtDeArch_ALU(nombreArchIngredientes,nomArchIngInd);

    //CARGO ARCHIVOS DE INDICES EN LISTA DE DOBLE ENLACE
    Lista listRec, listIng;
    crearLista(&listRec);
    crearLista(&listIng);

    cargarIndiceEnLista_ALU(nomArchRecInd,sizeof(IndReceta),&listRec,cmpRecInd);
    cargarIndiceEnLista_ALU(nomArchIngInd,sizeof(IndIngrediente),&listIng,cmpIngInd);





    //ABRO ARCHIVO PEDIDOS Y LEO CADA PEDIDO

    FILE* pfPed=fopen(nombreArchPedidos,"r");
    FILE *pfRec = fopen(nombreArchRecetas,"rb");
    FILE *pfIng = fopen(nombreArchIngredientes,"r+b");

    char linea[TAM_LINEA];
    char recetaAnt[20];

    Cola colIngr;
    crearCola(&colIngr);


    Pedido ped;
    Receta rec;
    Ingrediente ing, ingUsado;

    IndIngrediente indIng;
    IndReceta indRec;

    while(fgets(linea,TAM_LINEA,pfPed))
    {
        leerLina(linea,&ped);
        strcpy(indRec.codReceta,ped.codReceta);
        buscarEnLista_ALU(&listRec,&indRec,sizeof(IndReceta),cmpRecInd);

        fseek(pfRec,indRec.nroReg * sizeof(Receta),SEEK_SET);


        fread(&rec,sizeof(Receta),1,pfRec);
        strcpy(recetaAnt,rec.codReceta);
        while(!feof(pfRec) && strcmp(rec.codReceta,recetaAnt)==0)
        {
            strcpy(ingUsado.codIngr,rec.codIngr);
            ingUsado.stock=rec.cantidad*ped.cantidad;
            encolar_ALU(&colIngr,&ingUsado,sizeof(Ingrediente));



            strcpy(recetaAnt,rec.codReceta);
            //printf("\n Receta:%s Ingrediente:%s    unid usadas:%d",rec.codReceta,ingUsado.codIngr,ingUsado.stock);
            fread(&rec,sizeof(Receta),1,pfRec);
        }


        //LEO TODOS LOS INGREDIENTES DE LA RECETA
        while(!colaVacia(&colIngr))
        {
            desencolar_ALU(&colIngr,&ingUsado,sizeof(Ingrediente));
            strcpy(indIng.codIngr,ingUsado.codIngr);
            buscarEnLista_ALU(&listIng,&indIng,sizeof(IndIngrediente),cmpIngInd);

            fseek(pfIng,indIng.nroReg*sizeof(Ingrediente),SEEK_SET);
            fread(&ing,sizeof(Ingrediente),1,pfIng);
            //printf("\nIngre: %s cant:%d - %d = %d",ing.codIngr,ing.stock,ingUsado.stock,ing.stock-ingUsado.stock);
            ing.stock-=ingUsado.stock;
            fseek(pfIng,(long int)-sizeof(Ingrediente),SEEK_CUR);
            fwrite(&ing,sizeof(Ingrediente),1,pfIng);
            fseek(pfIng,0L,SEEK_CUR);
        }

    }


    fclose(pfPed);
    fclose(pfRec);
    fclose(pfIng);

	return TODO_OK;
}
