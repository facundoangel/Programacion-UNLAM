
/* -------------------------------------------------------------------------- */
/*                                 INCLUSIONES                                */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>





/* -------------------------------------------------------------------------- */
/*                                DEFINICIONES                                */
/* -------------------------------------------------------------------------- */

#define DEBUG 1
#define TAM 12

#ifndef VECTORES_H_INCLUDED
    #define VECTORES_H_INCLUDED

    int ordenarVector(int* vec,int ce);
    void eliminarElementoVector(int* vec, int* ce, int dato);
    void eliminarElementosDuplicadosVector(int* vec, int* ce, int dato);
    int agregarElementoVector(int* vec, int* ce, int dato);
#endif // VECTORES_H_INCLUDED
