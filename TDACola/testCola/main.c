#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../TDAcolaDin/TDAcolaDin.h"

int main()
{
    system("chcp 1252 > nul");


    Cola cola;
    char palabra[20]="palabra";
    char palabra2[20]="palabra2";
    char palabra3[20]="palabra3";
    char destino[20];

    crearCola(&cola);
    encolarAlInicio(&cola,palabra,sizeof(palabra));
    encolarAlInicio(&cola,palabra2,sizeof(palabra2));
    encolarAlFin(&cola,palabra3,sizeof(palabra3));
    //desencolarAlInicio(&cola,destino,sizeof(destino));
    desencolarAlFin(&cola,destino,sizeof(destino));
    printf("\nResultado: %s",destino);
    desencolarAlInicio(&cola,destino,sizeof(destino));
    printf("\nResultado: %s",destino);



    return 0;
}
