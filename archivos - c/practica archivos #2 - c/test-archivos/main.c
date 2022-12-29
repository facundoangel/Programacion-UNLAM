#include <stdio.h>
#include <stdlib.h>
#include "../library-archivos/library.h"
#include <stdbool.h>

int main()
{
    system("chcp 1252 > nul");

    //crearArchivo();
    mostrarEmpleados();
    if(preguntarEdicionUsuario())
    {
        editarDatos();
    }
    return 0;
}
