#include <stdio.h>
#include <stdlib.h>
#include "../enunciados/enunciados.h"

int main()
{
    Cola cola;
    crearCola(&cola);


    crearArchivos();
    cargarPedidos(&cola);

    cargarFaltantes(&cola);

        return 0;
}
