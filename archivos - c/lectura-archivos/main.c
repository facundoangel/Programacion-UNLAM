#include <stdio.h>
#include <stdlib.h>
#include "txtABin.h"

int main()
{
    crearTxtFij();
    archivoTxtABin("empleados.txt","empleados.dat");
    return 0;
}
