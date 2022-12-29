#include <stdio.h>
#include <stdlib.h>
#include "busqBinaria.h"

int main()
{

    int vec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    int tam = sizeof(vec) / sizeof(vec[0]), indice;

    indice = busquedaBinaria(vec,tam);
    printf("\n============================================");
    printf("\nIndice: %d",indice);
    return 0;
}
