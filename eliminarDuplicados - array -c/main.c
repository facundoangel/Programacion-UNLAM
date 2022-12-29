#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define TAM 10

int main()
{

    int vc[TAM]={1,2,2,4,3,6,7,2,9,10}, cantElem= sizeof(vc)/4;

    printf("\nVector de entrada: {");
        for(int i = 0; i < cantElem; i++){printf("%d ", vc[i]);};
        printf("}.\n ");


    eliminarOcurrencias(vc,&cantElem,2);

    printf("\nVector de salida: {");
        for(int i = 0; i < cantElem; i++){printf("%d ", vc[i]);};
        printf("}.\n ");

    return 0;
}
