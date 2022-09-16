#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"

int main(int argc,char* argv[])
{

    char* name = argv[1];

    crearArchivo(name);
    leerArchivo(name);
    return 0;
}
