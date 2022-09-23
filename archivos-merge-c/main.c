#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"

int main()
{
    //genrarArchivos();
    mostrarArchivos();


    mergeAlgoritmo1("productos.dat","movimientos.dat");
    printf("\n\n==================SALIDA=============================================================\n\n");
    //mostrarArchivos();
    mostrarArchivos();


    return 0;
}
