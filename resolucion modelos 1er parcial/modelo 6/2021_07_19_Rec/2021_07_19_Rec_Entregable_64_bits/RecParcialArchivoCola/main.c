#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
///*************************************************************************************
///********************** DESCOMENTAR EL QUE CORRESPONDA *******************************
//#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
///*************************************************************************************

#include "../TDACola/TDACola.h"
#include "../SolucionParcialArchivoCola/SolucionParcialArchivoCola.h"

#define MIN(X,Y) X<Y? X:Y


#define TDAColaEstatica
//#define TDAColaCircular


typedef struct{

    char COD_ART[7];
    char COD_MAT_PRI[7];
    int CANTIDAD;
    float COSTO_UNIT;

}Articulo;


void cargarColaEnArchivo_ALU(Cola *pc,FILE* pfMayor, FILE* pfMenor, float costoTotal);
int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000);

int main()
{
	generarArchivoProductos();

 	puts("Archivo de Productos");
	mostrarArchivoProd("productos.dat");

    int ret = procesarArchProductos_alu("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");
    //int ret = procesarArchProductos("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");

    if(ret != TODO_OK)
    {
        puts("Hubo un error en el proceso.");
        return ret;
    }

    puts("\nArchivo de productos de costo mayor a $1000");
	mostrarArchivoProd("ProductosMas1000.dat");

    puts("\nArchivo de productos de costo menor a $1000");
    mostrarArchivoProd("ProductosMenos1000.dat");

    return 0;
}


//================================================PRIMITIVAS COLA ESTATICA =============================================


#ifdef TDAColaEstatica
void crearCola_ALU(Cola *pc)
{
    pc->frente=0;
    pc->fondo=0;
    pc->tamDisponible=TAM_COLA;
}


void incorparDato_ALU(Cola* cp,const void* elem, const size_t tamElemento)
{
    size_t cantACopiar = tamElemento;
    size_t cantContigua = (cp->fondo >= cp->frente)? TAM_COLA - cp->fondo : cp->frente - cp->fondo;

    memcpy(cp->vCola+cp->fondo,elem,MIN(cantACopiar,cantContigua));
    cantACopiar-=MIN(cantACopiar,cantContigua);





    if(cantACopiar>0)
        memcpy(cp->vCola,(char *) elem + cantACopiar, cantACopiar);

    cp->tamDisponible-=tamElemento;
    cp->fondo = (cp->fondo + tamElemento > TAM_COLA)? cantACopiar : cp->fondo + tamElemento;
}


bool encolar_ALU(Cola* pc,const void* elem,const size_t tamElemento)
{

    if(sizeof(size_t) + tamElemento >= pc->tamDisponible)
        return false;


    incorparDato_ALU(pc,&tamElemento,sizeof(size_t));
    incorparDato_ALU(pc,elem,tamElemento);


    return true;

}


void retirarDato_ALU(Cola *pc, void* dato, size_t tamElem)
{
    size_t cantACopiar = tamElem;
    size_t cantContigua = (pc->frente > pc->fondo)? TAM_COLA-pc->frente : pc->fondo - pc->frente;

    memcpy(dato,pc->vCola+pc->frente,MIN(tamElem,cantContigua));
    cantACopiar-=MIN(cantContigua,tamElem);

    if(cantACopiar>0)
        memcpy(dato+cantContigua,pc->vCola,cantACopiar);

    pc->frente=(pc->frente+tamElem > TAM_COLA)? pc->frente+tamElem - TAM_COLA : pc->frente+tamElem;
    pc->tamDisponible+=tamElem;

}

void verFrenteDeCola_ALU(Cola *pc,void* dato, size_t tamElem)
{
    size_t tamElementoEncolado;

    if(pc->tamDisponible==TAM_COLA)
        return;

    Cola cola = *pc;

    retirarDato_ALU(&cola,&tamElementoEncolado,sizeof(size_t));
    retirarDato_ALU(&cola,dato,tamElementoEncolado);


}

void desencolar_ALU(Cola *pc,void* dato, size_t tamElem)
{
    size_t tamElementoEncolado;


    retirarDato_ALU(pc,&tamElementoEncolado,sizeof(size_t));
    retirarDato_ALU(pc,dato,tamElementoEncolado);

}

bool colaVacia_ALU(Cola *pc)
{
    return pc->tamDisponible==TAM_COLA;
}

#endif // TDAColaEstatica

//================================================PRIMITIVAS COLA ESTATICA =============================================
//================================================PRIMITIVAS COLA DINAMICA CIRCULAR =============================================

#ifdef TDAColaCircular

void crearCola_ALU(Cola *pc)
{
    *pc=NULL;
}


Nodo* crearNodo(const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*) malloc(sizeof(Nodo));
    if(!nue)
        return NULL;
    nue->dato=malloc(tamElem);
    if(!nue->dato)
        return NULL;

    memcpy(nue->dato,elem,tamElem);

    nue->sig=NULL;
    nue->tamElem=tamElem;

    return nue;
}



bool encolar_ALU(Cola* pc,const void* elem,const size_t tamElemento)
{

    Nodo* nue = crearNodo(elem,tamElemento);
    if(!nue)
        return false;

    if(!*pc)
    {
        *pc=nue;
        (*pc)->sig=nue;
    }

    nue->sig=(*pc)->sig;
    (*pc)->sig=nue;

    *pc=nue;


    return true;

}



bool verFrenteDeCola_ALU(Cola *pc,void* dato, size_t tamElem)
{
    if(!*pc)
        return false;

    Nodo* nodo = (*pc)->sig;

    memcpy(dato,nodo->dato,MIN(tamElem,nodo->tamElem));

    return true;

}

bool desencolar_ALU(Cola *pc,void* dato, size_t tamElem)
{
    if(!*pc)
        return false;

    Nodo* nodo = (*pc)->sig;

    if(*pc == nodo)
    {
        nodo = *pc;
        *pc=NULL;
        memcpy(dato,nodo->dato,MIN(tamElem,nodo->tamElem));

        free(nodo->dato);
        free(nodo);
        return true;
    }

    memcpy(dato,nodo->dato,MIN(tamElem,nodo->tamElem));

    (*pc)->sig=nodo->sig;


    free(nodo->dato);
    free(nodo);

    return true;

}

bool colaVacia_ALU(Cola *pc)
{
    return *pc==NULL;
}


#endif // TDAColaCircular

//================================================PRIMITIVAS COLA DINAMICA CIRCULAR =============================================



int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000)
{

    FILE *pf= fopen(nombreArchProd,"rb");
    FILE *pfMayores= fopen(nombreArchProdMas1000,"wb");
    FILE *pfMenores= fopen(nombreArchProdMenos1000,"wb");

    Cola colaProd;
    crearCola_ALU(&colaProd);

    Articulo art, artAux = {"","",0,0};
    float costoTotal=0;

    fread(&art,sizeof(Articulo),1,pf);


    while(!feof(pf))
    {
        verFrenteDeCola_ALU(&colaProd,&artAux,sizeof(Articulo));
        if(strcmp(artAux.COD_ART,"")==0 || strcmp(art.COD_ART,artAux.COD_ART)==0)
        {
            costoTotal+=(art.COSTO_UNIT*art.CANTIDAD);
        }

        if(strcmp(art.COD_ART,artAux.COD_ART)!=0 && strcmp(artAux.COD_ART,"")!=0)
        {

            cargarColaEnArchivo_ALU(&colaProd,pfMayores, pfMenores, costoTotal);
            costoTotal=(art.COSTO_UNIT*art.CANTIDAD);
        }

        encolar_ALU(&colaProd,&art,sizeof(Articulo));
        fread(&art,sizeof(Articulo),1,pf);
    }

    cargarColaEnArchivo_ALU(&colaProd,pfMayores, pfMenores, costoTotal);


    fclose(pf);
    fclose(pfMayores);
    fclose(pfMenores);


    Cola prueba;
    crearCola_ALU(&prueba);

    int num = 2;
    int dest;



    encolar_ALU(&prueba,&num,sizeof(int));
    desencolar_ALU(&prueba,&dest,sizeof(int));
    bool colaEstado = colaVacia_ALU(&prueba);
    num=200;
    encolar_ALU(&prueba,&num,sizeof(int));
    verFrenteDeCola_ALU(&prueba,&dest,sizeof(int));

    return 0;
}

void cargarColaEnArchivo_ALU(Cola *pc,FILE* pfMayor, FILE* pfMenor, float costoTotal)
{
    Articulo art;

    while(!colaVacia_ALU(pc))
    {
        desencolar_ALU(pc,&art,sizeof(Articulo));
        if(costoTotal<=1000)
        {
            fwrite(&art,sizeof(Articulo),1,pfMenor);
        } else
        {
            fwrite(&art,sizeof(Articulo),1,pfMayor);
        }

    }
}
