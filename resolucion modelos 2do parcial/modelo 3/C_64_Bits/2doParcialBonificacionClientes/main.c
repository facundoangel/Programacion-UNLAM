#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Solucion2doParcialBonificacionClientes/Utilitarias2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/Solucion2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/TiposArchivos.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define MIN(a,b) ((a)<(b)?(a):(b))


typedef struct{

    char codCliente[16];
    float compraTotal;

}ClienteCompra;

void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);
void listarClientesOrdXBonifDesc_ALU(const char* clientes);
int cmpComp(const void* e1, const void* e2);
int cmpInd (const void* e1, const void* e2);
void actComp (void* actualizado, const void* actualizador);
float calcularBonif(float monto);
void imprimirCliente_ALU(void* elem, void* datosAccion);



int main()
{
	generarArchivoClientes();
	generarIndiceArchivoClientes();
	generarArchivoVentas();

	mostrarArchivoClientes();
	puts("\n");

	mostrarArchivoVentas();
	puts("\n");

	bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
	//bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");

	puts("Clientes Bonificados");
	mostrarArchivoClientes();
	puts("\n");

	listarClientesOrdXBonifDesc_ALU("Clientes.dat");
	//listarClientesOrdXBonifDesc("Clientes.dat");

	return 0;
}

//=========================PRIMITIVAS ARBOL============================================
NodoA* creaNodoA_ALU(void* elem, size_t tamElem)
{
    NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
    if(!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if(!nue->elem)
        return NULL;

    nue->tamElem=tamElem;
    nue->hDer=nue->hIzq=NULL;
    memcpy(nue->elem,elem,tamElem);

    return nue;

}

booleano buscarEnArbol_ALU(const Arbol *pa,void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return falso;

    int resultado = cmp((*pa)->elem,dato);

    if(resultado==0)
    {
        memcpy(dato,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
        return verdadero;
    }

    if(resultado<0)
        buscarEnArbol_ALU(&(*pa)->hDer,dato,tamElem,cmp);


    return buscarEnArbol_ALU(&(*pa)->hIzq,dato,tamElem,cmp);;
}

int cargarArbolDeArchivoOrdenado_REC_ALU(Arbol *pa, size_t tamElem, FILE* pf,int li, int ls)
{
    if(li>ls)
        return TODO_OK;

    int m = (li+ls) / 2;

    void* elem = malloc(tamElem);

    fseek(pf,m*tamElem,SEEK_SET);
    fread(elem,tamElem,1,pf);

    NodoA* nue = creaNodoA_ALU(elem,tamElem);
    if(!nue)
        return SIN_MEM;

    *pa=nue;

    int r=cargarArbolDeArchivoOrdenado_REC_ALU(&(*pa)->hIzq,tamElem,pf,li,m-1);
    if(r!=0)
        return r;

    return cargarArbolDeArchivoOrdenado_REC_ALU(&(*pa)->hDer,tamElem,pf,m+1,ls);

}

int cargarArbolDeArchivoOrdenado_ALU(Arbol* pa,size_t tamElem,const char* nomArch)
{
    FILE* pf = fopen(nomArch,"rb");

    fseek(pf,0L,SEEK_END);

    int cantReg = ftell(pf) / tamElem;


    int r=cargarArbolDeArchivoOrdenado_REC_ALU(pa,tamElem,pf,0,cantReg-1);

    if(r!=0)
        return r;

    fclose(pf);

    return TODO_OK;
}



//=====================================================================================

//=========================PRIMITIVAS LISTA============================================

NodoD* creaNodoD_ALU(const void* elem, size_t tamElem)
{
    NodoD* nue = (NodoD*) malloc(sizeof(NodoD));
    if(!nue)
        return NULL;
    nue->elem = malloc(tamElem);
    if(!nue->elem)
        return NULL;

    memcpy(nue->elem,elem,tamElem);
    nue->sig=nue->ant=NULL;
    nue->tamElem=tamElem;

    return nue;
}

int insertarOActualizarEnListaOrd_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar)
{
    NodoD* nue = creaNodoD_ALU(elem,tamElem);
   if(!nue)
        return SIN_MEM;

   if(!*pl)
   {
       *pl=nue;
       return TODO_OK;
   }

   NodoD* nodo = *pl;

   int resultado = cmp(elem,nodo->elem);

   if(resultado==0)
   {
       actualizar(nodo->elem,elem);
       return TODO_OK;
   }

   if(resultado<0 || resultado==0)
   {
       NodoD* nodoAnt = nodo->ant;

       while(nodoAnt && cmp(elem,nodoAnt->elem)<0)
       {
           nodo=nodoAnt;
           nodoAnt=nodo->ant;
       }

       if(nodoAnt && cmp(elem,nodoAnt->elem)==0)
       {
            actualizar(nodoAnt->elem,elem);
            return TODO_OK;
       }

       if(nodoAnt)
            nodoAnt->sig=nue;
       nue->ant=nodoAnt;
       nue->sig=nodo;
       nodo->ant=nue;


   }
   else if(resultado>0)
   {
       NodoD* nodoSig = nodo->sig;

       while(nodoSig && cmp(elem,nodoSig->elem)>0)
       {
           nodo=nodoSig;
           nodoSig=nodo->sig;
       }

       if(nodoSig && cmp(elem,nodoSig->elem)==0)
       {
            actualizar(nodoSig->elem,elem);
            return TODO_OK;
       }

       if(nodoSig)
            nodoSig->ant=nue;
       nue->ant=nodo;
       nue->sig=nodoSig;
       nodo->sig=nue;

   }

   *pl=nue;

   return TODO_OK;
}


int insertarEnListaOrdCDup_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp)
{

   NodoD* nue = creaNodoD_ALU(elem,tamElem);
   if(!nue)
        return SIN_MEM;

   if(!*pl)
   {
       *pl=nue;
       return TODO_OK;
   }

   NodoD* nodo = *pl;

   int resultado = cmp(elem,nodo->elem);

   if(resultado<0 || resultado==0)
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
   else if(resultado>0)
   {
       NodoD* nodoSig = nodo->sig;

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

   *pl=nue;

   return TODO_OK;

}

booleano eliminarDeListaPrimero_ALU(Lista* pl,void* elem, size_t tamElem)
{
    if(!*pl)
        return falso;

    NodoD* nodo = *pl;

    //RETORNO AL INICIO
    while(nodo->ant)
        nodo=nodo->ant;

    NodoD* nodoSig = nodo->sig;

    if(nodoSig)
        nodoSig->ant=NULL;

    *pl=nodoSig;

    memcpy(elem,nodo->elem,MIN(tamElem,nodo->tamElem));

    free(nodo->elem);
    free(nodo);


    return verdadero;
}

//=====================================================================================

int cmpComp_ALU(const void* e1, const void* e2)
{
    ClienteCompra *cComp1 = (ClienteCompra*)e1;
    ClienteCompra *cComp2 = (ClienteCompra*)e2;

    return strcmp(cComp1->codCliente,cComp2->codCliente);

}

int cmpInd_ALU (const void* e1, const void* e2)
{
    Indice *ind1 = (Indice*)e1;
    Indice *ind2 = (Indice*)e2;

    return strcmp(ind1->codCliente,ind2->codCliente);
}

int cmpCliDesc_ALU(const void* e1, const void* e2)
{
    Cliente* cli1 = (Cliente*)e1;
    Cliente* cli2 = (Cliente*)e2;

    return (int) (cli2->porcBonif-cli1->porcBonif);
}

void actComp_ALU (void* actualizado, const void* actualizador)
{
    ClienteCompra *cComp = (ClienteCompra*)actualizado;
    ClienteCompra *cCopmAct = (ClienteCompra*)actualizador;

    cComp->compraTotal+=cCopmAct->compraTotal;
}


float calcularBonif_ALU(float monto)
{

    if(monto>=300000)
        return 20;

    if(monto>=200000)
        return 10;
    if(monto>=100000)
        return 5;

    return 0;
}

void imprimirCliente_ALU(void* elem, void* datosAccion)
{
    Cliente* cli = (Cliente*)elem;

    printf("\n%-16s  %-25s  %.2f",cli->codigo,cli->nombre,cli->porcBonif);

}

void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.


//CREO ARBOL BINARIO DE BUSQUEDA Y LO CARGO DESDE EL ARCHIVO DE INDICES
Arbol ar;
crearArbol(&ar);
cargarArbolDeArchivoOrdenado_ALU(&ar,sizeof(Indice),clientesInd);


////CONTABILIZO LAS COMPRAS TOTALES HECHAS POR CADA CLIENTE AGREGANDOLAS A UNA LISTA
Lista listComprasXClientes;
crearLista(&listComprasXClientes);
FILE *pfVent= fopen(ventas,"rb");

if(!pfVent)
    return;

Venta ven;
ClienteCompra cComp;

fread(&ven,sizeof(Venta),1,pfVent);

while(!feof(pfVent))
{
    strcpy(cComp.codCliente,ven.codCliente);
    cComp.compraTotal = ven.precioUnit * (float)ven.cantidad;
    insertarOActualizarEnListaOrd_ALU(&listComprasXClientes,&cComp,sizeof(ClienteCompra),cmpComp_ALU,actComp_ALU);
    fread(&ven,sizeof(Venta),1,pfVent);
}

fclose(pfVent);




//CREO LA LISTA CON LAS BONIFICACIONES DE CADA CLIENTE
Lista listClient;
crearLista(&listClient);

FILE *pfCli = fopen(clientes,"r+b");

if(!pfCli)
    return;

Cliente cli;
Indice ind;

while(eliminarDeListaPrimero_ALU(&listComprasXClientes,&cComp,sizeof(ClienteCompra)))
{
    strcpy(ind.codCliente,cComp.codCliente);
    buscarEnArbol_ALU(&ar,&ind,sizeof(Indice),cmpInd_ALU);

    fseek(pfCli,ind.nroReg*sizeof(Cliente),SEEK_SET);
    fread(&cli,sizeof(Cliente),1,pfCli);
    cli.porcBonif=calcularBonif_ALU(cComp.compraTotal);

    if(cli.porcBonif!=0)
    {
        fseek(pfCli,(long int) -sizeof(Cliente),SEEK_CUR);
        fwrite(&cli,sizeof(Cliente),1,pfCli);
        fseek(pfCli,0L,SEEK_CUR);
    }

}

fclose(pfCli);

}


void listarClientesOrdXBonifDesc_ALU(const char* clientes)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.

FILE *pf = fopen(clientes,"rb");

if(!pf)
    return;

Lista listDescCli;
crearLista(&listDescCli);

Cliente cli;

fread(&cli,sizeof(Cliente),1,pf);

while(!feof(pf))
{
    insertarEnListaOrdCDup_ALU(&listDescCli,&cli,sizeof(Cliente),cmpCliDesc_ALU);
    fread(&cli,sizeof(Cliente),1,pf);
}

printf("\n\nClientes Ord. X Bonificacion\n");
recorrerLista(&listDescCli,imprimirCliente_ALU,NULL);



fclose(pf);

}
