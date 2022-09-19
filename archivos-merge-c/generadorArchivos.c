#include <stdio.h>
#include "archivos.h"
#include <string.h>

void genrarArchivos()
{
    FILE* arcProd;
    FILE* arcMov;

    PRODUCTO productos[] = {
        {"MAN","Manzana",150.90,80},
        {"PER","Pera",150.90,80},
        {"NAR","Naranja",150.90,80},
        {"BAN","Banana",150.90,80},
        {"ZAN","Zandia",150.90,80}

    };

    MOVIMIENTO movimientos[] = {
        {"MAN",20},
        {"PER",-10},
        {"NAR",40},

    };



    //printf("\nCE: %d",sizeof(productos));

    arcProd =fopen("Productos.dat","wb");


    fwrite(productos,sizeof(PRODUCTO),5,arcProd);


    fclose(arcProd);


    arcMov = fopen("Movimientos.dat","wb");


    fwrite(movimientos,sizeof(MOVIMIENTO),3,arcMov);


    fclose(arcMov);
}

void mostrarArchivos()
{
    FILE* arcProd;
    FILE* arcMov;

    PRODUCTO prodLeido;
    MOVIMIENTO movLeido;


    //LEO Y IMPRIMO PRODUCTOS
    arcProd =fopen("Productos.dat","rb");

    if(arcProd==NULL)
    {
        printf("\nNo se pudo leer archivo producto");
        exit(1);
    }

    fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);
    printf("\n=============================");
    printf("\n ARCHIVO PRODUCTOS:");
    while(!feof(arcProd))
    {

        printf("\n%s  -  %s  -  %2.f  -  %d",prodLeido.cod,prodLeido.descripcion,prodLeido.precio,prodLeido.cant);
        fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);



    }
    printf("\n=============================");


    fclose(arcProd);


    //LEO Y IMPRIMO MOVIMIENTOS
    arcMov =fopen("Movimientos.dat","rb");

    if(arcMov==NULL)
    {
        printf("\nNo se pudo leer archivo movimientos");
        exit(1);
    }

    fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);
    printf("\n=============================");
    printf("\n ARCHIVO PRODUCTOS:");
    //printf("\n%s  -   %d",movLeido.cod,movLeido.cant);
    while(!feof(arcMov))
    {

        printf("\n%s  -   %d",movLeido.cod,movLeido.cant);
        fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);

    }
    printf("\n=============================");


    fclose(arcMov);




}


void mostrarArchivoTMP(){


}

void mergeAlgoritmo(char* prod,char* mov)
{
    FILE* arcProd;
    FILE* arcMov;
    FILE* tmpProd;

    PRODUCTO prodLeido, prodNuevo;
    MOVIMIENTO movLeido;

    int comp;


    arcProd =fopen(prod,"rb");
    arcMov =fopen(mov,"rb");
    tmpProd = fopen("temporario.tmp","wb");

    if(arcProd==NULL || arcMov==NULL)
    {
        printf("\nNo Leer alguno de los archivos");
        exit(1);
    }


    //COMIENZO DE LA ITERACIÓN SOBRE LOS ARCHIVOS
    fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);
    fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);



    while(!feof(arcMov) && !feof(arcProd))
    {
        comp = strcmp(prodLeido.cod,movLeido.cod);

        if(comp<0){
            printf("\n AGREGAR PRODUCTO A ARCHIVO TEMPORAL");
            prodNuevo.cod = prodLeido.cod;
            prodNuevo.descripcion = prodLeido.descripcion;
            prodNuevo.cant = prodLeido.cant;
            prodNuevo.precio = prodLeido.precio;
            fwrite(prodNuevo,sizeof(PRODUCTO),1,tmpProd);
        }

        if(comp==0){
            printf("\n COINCIDENCIA DE CODIGOS");
        }

        if(comp>0){
            printf("\n PRODUCTO YA CARGADO");
        }

        break;

    }



    fclose(arcProd);
    fclose(arcMov);
    fclose(tmpProd);


    //remove(arcProd)


}
