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

/*||=== Build: Debug in archivosPractica (compiler: GNU GCC Compiler) ===|
C:\Users\laboratorios\Desktop\Programacion-UNLAM-main\archivos - c\archivosPractica\archivos.c||In function 'crearArchivo':|
C:\Users\laboratorios\Desktop\Programacion-UNLAM-main\archivos - c\archivosPractica\archivos.c|6|warning: implicit declaration of function 'fopen' [-Wimplicit-function-declaration]|
C:\Users\laboratorios\Desktop\Programacion-UNLAM-main\archivos - c\archivosPractica\archivos.c|6|warning: assignment makes pointer from integer without a cast [-Wint-conversion]|
C:\Users\laboratorios\Desktop\Programacion-UNLAM-main\archivos - c\archivosPractica\main.c||In function 'main':|
C:\Users\laboratorios\Desktop\Programacion-UNLAM-main\archivos - c\archivosPractica\main.c|9|warning: 'p' is used uninitialized in this function [-Wuninitialized]|
||=== Build finished: 0 error(s), 3 warning(s) (0 minute(s), 0 second(s)) ===|
*/
