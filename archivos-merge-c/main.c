#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"

int main()
{
    //genrarArchivos();
    mostrarArchivos();


    mergeAlgoritmo("productos.dat","movimientos.dat");

    mostrarArchivos();
    mostrarArchivoTMP();


    return 0;
}
