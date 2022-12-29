#include "archivos.h"
#include <stdio.h>


void crearArchivo(char* nombreArchivo){

     PRODUCTOS prod[] = {
        {1,"TOMATES",400.10},
        {2,"HUEVOS",260.10},
        {3,"ESPINACA",160.00},
        {4,"ZANAHORIA",360.00},
        {5,"SODA",270.90}
    };


    FILE *pf;

    pf = fopen(nombreArchivo,"wb");

    if(pf==NULL){
        printf("\nError: No se pudo crear archivo");
        return;
    }

    fwrite(prod,sizeof(PRODUCTOS),(sizeof(prod)/sizeof(prod[0])),pf);

    fclose(pf);

}

void leerArchivo(char* nombreArchivo){

    FILE *pf;
    PRODUCTOS pro;

    pf = fopen(nombreArchivo,"rb");
    if(pf==NULL){
        printf("\n=======================================");
        printf("\nError: No se pudo leer archivo");
        printf("\n=======================================");
        exit(1);
    }


    fread(&pro,sizeof(PRODUCTOS),1,pf);



    while(!feof(pf)){
        printf("\n(%d - %s - %2.f)",pro.codigo,pro.nombre,pro.price);
        fread(&pro,sizeof(PRODUCTOS),1,pf);


    }

    fclose(pf);
}


void actualizarArchivo(char* nombreArchivo)
{
    FILE *pf= fopen(nombreArchivo,"r+b");

    PRODUCTOS prod;

    fread(&prod,sizeof(PRODUCTOS),1,pf);

    while(!feof(pf))
    {
        prod.price*=2;
        printf("\nprecio: %2.f",prod.price);

        fseek(pf,(int)-sizeof(PRODUCTOS),SEEK_CUR);
        fwrite(&prod,sizeof(PRODUCTOS),1,pf);
        fseek(pf,0,SEEK_CUR);
        fread(&prod,sizeof(PRODUCTOS),1,pf);

    }


    fclose(pf);

}
