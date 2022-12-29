/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
** DNI:                                                       													**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**                      																					   	**
******************************************************************************************************************
** Nota:																									   	**
*****************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include "../Comun/Comun.h"
#include "../Cadena/Cadena.h"
#include "../Archivo/Archivo.h"
#include "../Solucion1erParcialFabricasComputadoras/Solucion1erParcialFabricasComputadoras.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"
#define TAM_LINEA 100
#define MAX(a,b) ((a)>(b)? (a) : (b))

//#define SOLUCION_DOC
//#define SOLUCION_ALU

int procesarArchivos_ALU(const char* arcProdCord, const char* arcProdChub, const char* arcClieCord, const char* arcClieChub, const char* arcProdFus, const char* arcClieFus);

int main()
{
    int resp = generarArchivos();

    if(resp != TODO_OK)
    {
        printf("Error al generar los archivos");
        return resp;
    }

    puts("Archivos Pre Fusion:\n");

    puts(PROD_COR);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_COR);

    puts("\n");

    puts(PROD_CHU_TXT);
    puts("=========================================");
    mostrarArchivoProductosTxt(PROD_CHU_TXT);

    puts("\n");

    puts(CLI_COR);
    puts("=========================================");
    mostrarArchivoClientes(CLI_COR);

    puts("\n");

    puts(CLI_CHU);
    puts("=========================================");
    mostrarArchivoClientes(CLI_CHU);


    #ifdef SOLUCION_DOC
        resp = procesarArchivos(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #else
        resp = procesarArchivos_ALU(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #endif

    if(resp != TODO_OK)
    {
        printf("Error al procesar los archivos");
        return resp;
    }

    puts("\n\nArchivos Post Fusion:\n");

    puts(PROD_FUS);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_FUS);

    puts("\n");

    puts(CLI_FUS);
    puts("=========================================");
    mostrarArchivoClientes(CLI_FUS);

    return 0;
}


int compararProd_ALU(const void* e1, const void* e2)
{
    Producto* prod1 = (Producto*) e1;
    Producto* prod2 = (Producto*) e2;

    return strcmp(prod1->codigo,prod2->codigo);

}

int compararClie_ALU(const void* e1, const void* e2)
{
    Cliente* cli1 = (Cliente*) e1;
    Cliente* cli2 = (Cliente*) e2;

    return cli1->codigo-cli2->codigo;

}

void actualizarProd_ALU(void* actualizado, const void* actualizador)
{
    Producto* prod = (Producto*) actualizado;
    Producto* prodActualizador = (Producto*) actualizador;

    prod->precio = MAX(prod->precio,prodActualizador->precio);
    prod->stock += prodActualizador->stock;
}

void actualizarClie_ALU(void* actualizado, const void* actualizador)
{

}

bool leerLinea_ALU(char* linea,Producto* prod)
{
    char *c;

    c = strchr(linea,'\n');
    if(!c)
        return false;
    *c='\0';

    c = strrchr(linea,'|');
    sscanf(c+1,"%d",&prod->stock);
    *c='\0';

    c = strrchr(linea,'|');
    sscanf(c+1,"%f",&prod->precio);
    *c='\0';

    c = strrchr(linea,'|');
    strcpy(prod->descripcion,c+1);
    *c='\0';

    strcpy(prod->codigo,linea);

    return true;

}

void pasarNomTxtABin_ALU(char* nombre)
{


    char* c = strrchr(nombre,'.');

    //SI LA EXTENSIÒN NO ES .txt RETORNO LA FUNCION SIN HACER NADA
    if(*(c+1)!='t')
        return;

    *c='\0';
    strcat(nombre,".dat");



}

bool pasarArcABin_ALU(const char* nombreArchivo,char* nuevoNombre)
{

    //MODIFICO LA EXTENSIÓN DEL NOMBRE
    strcpy(nuevoNombre,nombreArchivo);
    pasarNomTxtABin_ALU(nuevoNombre);



    FILE *pf = fopen(nombreArchivo,"r");
    FILE *pfBin = fopen(nuevoNombre,"wb");
    Producto prod;
    char linea[TAM_LINEA];

    while(fgets(linea,TAM_LINEA,pf))
    {
        leerLinea_ALU(linea,&prod);
        fwrite(&prod,sizeof(Producto),1,pfBin);
    }

    fclose(pf);
    fclose(pfBin);



    return true;
}

////////////////////////////////////////////////////////////////PRIMITIVAS LISTAS ////////////////////////////////////////////////////////////

Nodo* crearNodo(const void* elem, size_t tamElem)
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

bool insertarEnListaOrdCDup_ALU(Lista* pl,const void* elem,size_t tamElem, Cmp cmp)
{
    Nodo* nue = crearNodo(elem,tamElem);
    if(!nue)
        return false;



    while(*pl && cmp((*pl)->elem,elem)<0)
        pl=&(*pl)->sig;

    nue->sig = *pl;
    *pl = nue;


    return true;
}


bool eliminarDeListaPrimero_ALU(Lista* pl,void* elem,size_t tamElem)
{
    if(!*pl)
        return false;


    Nodo* nae = *pl;
    *pl = nae->sig;

    memcpy(elem,nae->elem,tamElem);


    free(nae->elem);
    free(nae);


    return true;
}



void eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar act)
{
    if(!*pl)
        return;

    Nodo *nodoSig;


    while(*pl && (*pl)->sig)
    {
        nodoSig = (*pl)->sig;


        while(cmp((*pl)->elem,nodoSig->elem)==0)
        {
            act((*pl)->elem,nodoSig->elem);
            (*pl)->sig = nodoSig->sig;
            free(nodoSig->elem);
            free(nodoSig);

            pl = &(*pl)->sig;
            nodoSig = (*pl)->sig;
        }

        pl = &(*pl)->sig;
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ordenarArchivo_ALU(const char* nombreArchivo, size_t tamElem, Cmp cmp)
{
    char nombreArchivoBin[strlen(nombreArchivo)+1];
    strcpy(nombreArchivoBin,nombreArchivo);
    if(strstr(nombreArchivo,".txt"))
        pasarArcABin_ALU(nombreArchivo,nombreArchivoBin);

     //LEO EN LISTA
    FILE *pf = fopen(nombreArchivoBin,"rb");
    if(!pf)
        return false;


    Lista listOrd;
    crearLista(&listOrd);
    void* elem = malloc(tamElem);

    fread(elem,tamElem,1,pf);


    while(!feof(pf))
    {
        insertarEnListaOrdCDup_ALU(&listOrd,elem,tamElem,cmp);
        fread(elem,tamElem,1,pf);

    }

    fclose(pf);
    //REESCRIBO EL ARCHIVO
    FILE *pfFinal = fopen(nombreArchivoBin,"wb");

    while(eliminarDeListaPrimero_ALU(&listOrd,elem,tamElem))
    {

        fwrite(elem,tamElem,1,pfFinal);
    }


    fclose(pfFinal);
    free(elem);

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool fusionarArchivos_ALU(const char* nombreArchivo1,const char* nombreArchivo2, const char* nombreDestino, size_t tamElem, Cmp cmp, Actualizar actu)
{
    FILE *pf1 = fopen(nombreArchivo1,"rb");
    FILE *pf2 = fopen(nombreArchivo2,"rb");
    FILE *pfFus = fopen(nombreDestino,"wb");

    void* elem1 = malloc(tamElem);
    void* elem2 = malloc(tamElem);

    Lista lista;
    crearLista(&lista);

    fread(elem1,tamElem,1,pf1);
    fread(elem2,tamElem,1,pf2);

    while(!feof(pf1) && !feof(pf2))
    {
        int compar=cmp(elem1,elem2);

        if(compar<0)
        {
            insertarEnListaOrdCDup_ALU(&lista,elem1,tamElem,cmp);
            fread(elem1,tamElem,1,pf1);
        }
        else if(compar==0)
        {
            insertarEnListaOrdCDup_ALU(&lista,elem1,tamElem,cmp);
            fread(elem1,tamElem,1,pf1);
        }
        else if(compar>0)
        {
            insertarEnListaOrdCDup_ALU(&lista,elem2,tamElem,cmp);
            fread(elem2,tamElem,1,pf2);
        }

    }



    while(!feof(pf1))
    {
        insertarEnListaOrdCDup_ALU(&lista,elem1,tamElem,cmp);
        fread(elem1,tamElem,1,pf1);
    }

    while(!feof(pf2))
    {
        insertarEnListaOrdCDup_ALU(&lista,elem2,tamElem,cmp);
        fread(elem2,tamElem,1,pf2);
    }

    eliminarDeListaOrdDuplicados_ALU(&lista,cmp,actu);

    while(eliminarDeListaPrimero_ALU(&lista,elem1,tamElem))
    {
        fwrite(elem1,tamElem,1,pfFus);
    }

    fclose(pf1);
    fclose(pf2);
    fclose(pfFus);

    free(elem1);
    free(elem2);

    return true;
}


int procesarArchivos_ALU( const char* arcProdCord, const char* arcProdChub, const char* arcClieCord, const char* arcClieChub, const char* arcProdFus, const char* arcClieFus)
{

    //ORDENO LOS ARCHIVOSs
    ordenarArchivo_ALU(arcProdCord,sizeof(Producto),compararProd_ALU);
    ordenarArchivo_ALU(arcProdChub,sizeof(Producto),compararProd_ALU);
    ordenarArchivo_ALU(arcClieCord,sizeof(Cliente),compararClie_ALU);
    ordenarArchivo_ALU(arcClieChub,sizeof(Cliente),compararClie_ALU);


    //EVALUO SI ALGUNO DE LOS NOMBRES DE ARCHIVOS ES .txt Y SI ES ASÌ LOS CAMBIO A .dat
    char nomArcProdCord[strlen(arcProdCord)+1];
    char nomArcProdChub[strlen(arcProdChub)+1];
    char nomArcClieCord[strlen(arcClieCord)+1];
    char nomArcClieChub[strlen(arcClieChub)+1];

    strcpy(nomArcProdCord,arcProdChub);
    strcpy(nomArcProdChub,arcProdCord);
    strcpy(nomArcClieCord,arcClieCord);
    strcpy(nomArcClieChub,arcClieChub);

    pasarNomTxtABin_ALU(nomArcProdCord);
    pasarNomTxtABin_ALU(nomArcProdChub);
    pasarNomTxtABin_ALU(nomArcClieCord);
    pasarNomTxtABin_ALU(nomArcClieChub);


    //FUSIONO EN ARCHIVOS
    fusionarArchivos_ALU(nomArcProdChub,nomArcProdCord,arcProdFus,sizeof(Producto),compararProd_ALU,actualizarProd_ALU);
    fusionarArchivos_ALU(nomArcClieCord,nomArcClieChub,arcClieFus,sizeof(Cliente),compararClie_ALU,actualizarClie_ALU);

    printf("\n=========================\n");
    mostrarArchivoProductosBin("Productos-chu.dat");
    printf("\n===========================\n");
    mostrarArchivoProductosBin(arcProdCord);
    printf("\n========================\n");
    mostrarArchivoClientes(arcClieCord);
    printf("\n=======================\n");
    mostrarArchivoClientes(arcClieChub);


    return 0;
}
