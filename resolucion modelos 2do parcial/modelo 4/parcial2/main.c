#include <stdio.h>
#include <stdlib.h>

#include "parcial2.h"

#define TAM_MAX 100

void leerLinea(char* linea,Pedido *ped)
{
    char *c;

    c=strchr(linea,'\n');
    *c='\0';

    c=strrchr(linea,';');
    sscanf(c+1,"%8d",&ped->cantPedida);
    *c='\0';

    c=strrchr(linea,';');
    strcpy(ped->codProd,c+1);
    *c='\0';

    c=strrchr(linea,';');
    sscanf(c+1,"%8d",&ped->codClie);
    *c='\0';

    c=strrchr(linea,'/');
    sscanf(c+1,"%8d",&ped->fecha.a);
    *c='\0';

    c=strrchr(linea,'/');
    sscanf(c+1,"%8d",&ped->fecha.m);
    *c='\0';


    sscanf(linea,"%8d",&ped->fecha.d);

}

int compararIndice(void* elem1, void* elem2)
{
    Indice* ind1=(Indice*)elem1;
    Indice* ind2=(Indice*)elem2;

    return strcmpi(ind1->codProd,ind2->codProd);
}

void actualizarIndice(void* elem1, void* elem2)
{
    Indice* ind1=(Indice*)elem1;
    Indice* ind2=(Indice*)elem2;

    ind1->indice=ind2->indice;
}


int main()
{

    crearArchivos();

    ordenarYSacarDuplicadosProductos();

    mostrarArchProductos();

    Arbol ar;
    crearArbol(&ar);

    FILE *pf;

    cargarArchivoEnArbol(&ar,pf,comparar,leerRegistro,sizeof(Producto),"productos.dat");

    graficarARbol(&ar,imprimirIndice);


    //RECORRO Y ACTUALIZO EN BASE A PEDIDOS LEIDOS

    FILE *pfPed, *pfProd;
    Pedido ped;
    Indice ind;
    Producto prod;

    char linea[TAM_MAX];

    pfPed=fopen("pedidos.txt","r");
    pfProd=fopen("Productos.dat","r+b");


    while(fgets(linea,TAM_MAX,pfPed))
    {
        leerLinea(linea,&ped);
        strcpy(ind.codProd,ped.codProd);
        buscarElemetoEnArbolBusqueda(&ar,&ind, sizeof(Indice), actualizarIndice,compararIndice);

        fseek(pfProd,ind.indice*sizeof(Producto),SEEK_SET);
        fread(&prod,sizeof(Producto),1,pfProd);
        prod.stock-=ped.cantPedida;
        fseek(pfProd,(long int)-sizeof(Producto),SEEK_CUR);
        fwrite(&prod,sizeof(Producto),1,pfProd);
        fseek(pfProd,0L,SEEK_CUR);

    }


    mostrarArchProductos();

    return 0;
}
