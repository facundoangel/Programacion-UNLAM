#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "enunciados.h"

#define TODO_OK 0
#define ERROR_LEER_ARCHIVOS 1
#define MEMORIA_INSUF 2



void normalizarTexto(char* entrada, char* salida)
{
    while(!esLetra(*entrada) && *entrada)
          entrada++;

    while(*entrada)
    {
        if(esLetra(*entrada) || esCaracterPermitido(*entrada))
        {
            *salida=*entrada;
            salida++;
        }
        entrada++;
    }

}

void generarArchivosAlmacen()
{

    FILE *pf1,*pf2;

    pf1 = fopen("Archivo 1.dat","wb");
    pf2 = fopen("Archivo 2.dat","wb");

    Producto listado1[] = {{1,"chocolate",200,24.3},{2,"Lacteo",560,70.9},{3,"Manzanas",900,20.0},{5,"Zanahoria",900,20.0}};
    Producto listado2[] = {{1,"chocolate",-100,24.3},{2,"Lacteo",20,70.9},{2,"Lacteo",-500,70.9},{2,"Lacteo",-5,70.9},{4,"Mandarina",230,70.9}};

    printf("\nTamaño archivo 1: %d, tamaño archivo 2: %d",(int) (sizeof(listado1)/sizeof(Producto)),(int) (sizeof(listado2)/sizeof(Producto)));
    fwrite(listado1,sizeof(Producto),sizeof(listado1)/sizeof(Producto),pf1);
    fwrite(listado2,sizeof(Producto),sizeof(listado2)/sizeof(Producto),pf2);


    fclose(pf1);
    fclose(pf2);
}

void mostrarLinea(Producto* linea)
{
    char lineaCadena[100];

    sprintf(lineaCadena,"\n%d - %s - %d - %.2f",linea->codigo,linea->nombre,linea->stock,linea->precio);
    puts(lineaCadena);
}

int comparar(int num1, int num2)
{
    return num1 - num2;

}

bool mergeArchivos()
{
    FILE *pf1,*pf2,*pfFinal;
    Producto LeidoArchivo1, LeidoArchivo2;


    pf1 = fopen("Archivo 1.dat","rb");
    pf2 = fopen("Archivo 2.dat","rb");
    pfFinal = fopen("listadoFinal.dat","wb");

    if(pf1 == NULL || pf2 == NULL)
        return ERROR_LEER_ARCHIVOS;


    fread(&LeidoArchivo1,sizeof(Producto),1,pf1);
    fread(&LeidoArchivo2,sizeof(Producto),1,pf2);



    while(!feof(pf1)&&!feof(pf2))
   {
        if(comparar(LeidoArchivo1.codigo,LeidoArchivo2.codigo)<0)
        {
            fwrite(&LeidoArchivo1,sizeof(Producto),1,pfFinal);
            mostrarLinea(&LeidoArchivo1);
            fread(&LeidoArchivo1,sizeof(Producto),1,pf1);
        }

        if(comparar(LeidoArchivo1.codigo,LeidoArchivo2.codigo)==0)
        {
            fwrite(&LeidoArchivo1,sizeof(Producto),1,pfFinal);
            mostrarLinea(&LeidoArchivo1);
            fread(&LeidoArchivo1,sizeof(Producto),1,pf1);
        }
        if(comparar(LeidoArchivo1.codigo,LeidoArchivo2.codigo)>0)
        {

            fwrite(&LeidoArchivo2,sizeof(Producto),1,pfFinal);
            mostrarLinea(&LeidoArchivo2);
            fread(&LeidoArchivo2,sizeof(Producto),1,pf2);

        }

    }



    while(!feof(pf1))
    {
        fwrite(&LeidoArchivo1,sizeof(Producto),1,pfFinal);
        mostrarLinea(&LeidoArchivo1);
        fread(&LeidoArchivo1,sizeof(Producto),1,pf1);

    }

    while(!feof(pf2))
    {
        fwrite(&LeidoArchivo2,sizeof(Producto),1,pfFinal);
        mostrarLinea(&LeidoArchivo2);
        fread(&LeidoArchivo2,sizeof(Producto),1,pf2);

    }


    fclose(pf1);
    fclose(pf2);
    fclose(pfFinal);
    return TODO_OK;
}

bool leerListadoFinal(Lista* pl)
{
    Producto prodLeido;

    if(*pl)
        vaciarLista(pl);

    FILE *pf = fopen("listadoFinal.dat","rb");

    if(!pf)
        return false;

    fread(&prodLeido,sizeof(Producto),1,pf);

    while(!feof(pf))
    {
        InsertarEnListaDesordAlFinal(pl,&prodLeido,sizeof(Producto));
        fread(&prodLeido,sizeof(Producto),1,pf);

    }

    fclose(pf);

    return true;
}

void crearLista(Lista* pl)
{
    *pl=NULL;

}

void actualizarNodo(TNodo* n, Producto* prod)
{

    memcpy(n->info,prod,sizeof(Producto));
    n->tamElemento=sizeof(prod);

}

bool eliminarDuplicados(Lista* pl)
{

    Producto prod, prodProx, prodAux={0,"",0,0};
    TNodo *nodo, *nodoProx;

    FILE *fp=fopen("temporal.tmp","wb");


    if(!*pl)
        return false;


    printf("\n[");

    while(*pl)
    {
        nodo = *pl;
        nodoProx =  nodo->sig;

        memcpy(&prod,nodo->info,sizeof(Producto));



        if(nodoProx!=NULL)
        {
            memcpy(&prodProx,nodoProx->info,sizeof(Producto));

            if(nodoProx && (prod.codigo==prodProx.codigo))
            {
                prodAux.codigo=prod.codigo;
                strcpy(prodAux.nombre,prod.nombre);
                prodAux.precio=prod.precio;
                prodAux.stock+=prod.stock;



                TNodo* nae = *pl;
                *pl=(*pl)->sig;
                free(nae->info);
                free(nae);
                continue;
            }

            if(nodoProx && (prod.codigo!=prodProx.codigo))
            {
                if(prodAux.codigo!=0)
                {
                    prodAux.stock+=prod.stock;
                    printf("%s|%d ",prodAux.nombre,prodAux.stock);
                    actualizarNodo(*pl,&prodAux);
                    fwrite(&prodAux,sizeof(Producto),1,fp);
                }


                if(prodAux.codigo==0)
                {
                    printf("%s|%d ",prod.nombre,prod.stock);
                    actualizarNodo(*pl,&prod);
                    fwrite(&prod,sizeof(Producto),1,fp);
                }

                prodAux.codigo=0;
                prodAux.stock=0;
            }
        }

        if(!nodoProx)
        {

            if(prodAux.codigo!=0)
            {
                prodAux.stock+=prod.stock;
                printf("%s|%d ",prodAux.nombre,prodAux.stock);
                actualizarNodo(*pl,&prodAux);
                fwrite(&prodAux,sizeof(Producto),1,fp);
            }

            if(prodAux.codigo==0)
            {
                printf("%s|%d ",prod.nombre,prod.stock);
                actualizarNodo(*pl,&prod);
                fwrite(&prod,sizeof(Producto),1,fp);
            }
        }

        pl = &(*pl)->sig;



    }
    printf("]\n");

    fclose(fp);
    remove("listadoFinal.dat");
    rename("temporal.tmp","listadoFinal.dat");

    return true;

}

bool mostrarLista(Lista* pl)
{

    Producto prod;
    TNodo *nodo;

    if(!(*pl))
        return false;


    printf("\n[");
    while(*pl)
    {
        nodo = (*pl);
        memcpy(&prod,nodo->info,sizeof(Producto));
        printf("%s ",prod.nombre);
        pl = &(*pl)->sig;

    }
    printf("]\n");



    return true;

}

void vaciarLista(Lista* pl)
{

    TNodo *nodo;

    if(!*pl)
        return;



    while(*pl)
    {
        nodo = *pl;
        pl = &(*pl)->sig;
        free(nodo);


    }



}

bool InsertarEnListaDesordAlFinal(Lista* pl,void* elem, size_t tamElemento)
{



    while(*pl)
        pl = &(*pl)->sig;


    TNodo *nue=(TNodo*) malloc(sizeof(TNodo));
    nue->info = malloc(tamElemento);
    memcpy(nue->info,elem,tamElemento);

    if(nue==NULL || nue->info == NULL)
        return false;



    nue->sig=NULL;
    *pl=nue;


    return true;
}

bool InsertarEnListaDesordAlIni(Lista* pl,const void* elem, size_t tamElemento)
{


    TNodo *nue2=(TNodo*) malloc(sizeof(TNodo));
    nue2->info = malloc(sizeof(Producto));
    nue2->tamElemento = sizeof(Producto);
    memcpy(nue2->info,elem,sizeof(Producto));

    nue2->sig = *pl;
    *pl = nue2;


    return true;
}

bool generarArchivoMovimientos()
{
    FILE *pf;

    pf = fopen("movimientos.dat","wb");


    Producto movimientos[] = {{1,"chocolate",50,24.3},{3,"Manzanas",-400,20.0}};

    fwrite(movimientos,sizeof(Producto),sizeof(movimientos)/sizeof(movimientos[0]),pf);


    fclose(pf);
    return true;

}

bool generarListadoAPartirLista(Lista *pl)
{
    FILE *pf = fopen("listadoFinal.dat","wb");

    TNodo *nodo;



    if(!pl && !pf)
    {
        printf("\nError: no se pudo hacer el listado final por segunda vez");
        return false;
    }

    while(*pl)
    {
        nodo = *pl;
        fwrite(nodo->info,sizeof(Producto),1,pf);
        pl=&(*pl)->sig;

    }

    fclose(pf);

    return true;

}


bool actualizarArchivoFinal(Cmp cmp){

    FILE *listFinal, *mov, *tmp;
    Producto prod, prodMov;
    int diff;

    listFinal = fopen("listadoFinal.dat","rb");
    mov = fopen("movimientos.dat","rb");
    tmp = fopen("temporal.tmp","wb");

    if(listFinal==NULL || mov==NULL)
        return false;

    fread(&prod,sizeof(Producto),1,listFinal);
    fread(&prodMov,sizeof(Producto),1,mov);

    while(!feof(listFinal) && !feof(mov))
    {
        diff = cmp(prod.codigo,prodMov.codigo);

        if(diff<0)
        {
            fwrite(&prod,sizeof(Producto),1,tmp);
            printf("\n%s|%d ",prod.nombre,prod.stock);
            fread(&prod,sizeof(Producto),1,listFinal);

        }else if(diff==0)
        {
            prod.stock+=prodMov.stock;
            strcpy(prod.nombre,prodMov.nombre);
            prod.precio=prodMov.precio;
            fread(&prodMov,sizeof(Producto),1,mov);

        }else
        {
            fread(&prodMov,sizeof(Producto),1,mov);
        }

    }


    while(!feof(listFinal))
    {
        fwrite(&prod,sizeof(Producto),1,tmp);
        printf("\n%s|%d ",prod.nombre,prod.stock);
        fread(&prod,sizeof(Producto),1,listFinal);
    }

    while(!feof(mov))
    {

        fwrite(&prodMov,sizeof(Producto),1,tmp);
        printf("\n%s|%d ",prodMov.nombre,prodMov.stock);
        fread(&prodMov,sizeof(Producto),1,mov);


    }

    fclose(listFinal);
    fclose(tmp);
    fclose(mov);

    remove("listadoFinal.dat");
    rename("temporal.tmp","listadoFinal.dat");

    return true;

}
