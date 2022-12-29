#include <stdio.h>
#include <stdlib.h>
#include "parcail2.h"
#include "../../../TDAListaDobleEnlace/TDAListaDobleEnlace/ListaDobleEnlace.h"

int main()
{
    Lista listAlumnos, listNotas;
    crearLista(&listNotas);
    crearLista(&listAlumnos);

    leerArchivo("notas.csv",&listAlumnos);

    ordenarNotas(&listAlumnos,&listNotas);

    escribirArchivo(&listNotas);



    return 0;
}
