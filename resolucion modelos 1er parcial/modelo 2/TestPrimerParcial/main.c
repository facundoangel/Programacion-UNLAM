#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../primerParcial/enunciados.h"

int main()
{
    system("chcp 1252 >nul");

    //EJERCICIO 1=============================================
    printf("\n===========================EJERCICIO 1========================");
    char entrada[50] = "3414134124124*&¡ho44l[]¨¨#";
    char salida[50];

    normalizarTexto(entrada,salida);


    printf("\nTexto Normalizado: %s",salida);
    //=========================================================


    //EJERCICIO 2==============================================
    printf("\n===========================EJERCICIO 2========================");
    generarArchivosAlmacen();
    mergeArchivos();
    //=========================================================



    //Ejercicio 3=============================================
    printf("\n===========================EJERCICIO 3========================");
    Lista lista;
    crearLista(&lista);
    leerListadoFinal(&lista);
    mostrarLista(&lista);
    //=========================================================



    //Ejercicio 4=============================================
    printf("\n===========================EJERCICIO 4========================");
    eliminarDuplicados(&lista);
    printf("\nLista resultante despues de la eliminación de archivos duplicados:");
    mostrarLista(&lista);
    //=========================================================




    //Ejercicio 5=============================================
    printf("\n===========================EJERCICIO 5========================");
    generarListadoAPartirLista(&lista);
    generarArchivoMovimientos();
    actualizarArchivoFinal(comparar);
    //eliminarDuplicadosEnArchivo();
    //crearArchivoMovimientos();
    //ActualizarArchivo(&lista);
    //=========================================================



    return 0;
}
