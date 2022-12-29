#include <stdio.h>
#include <stdlib.h>
#include "../TDAListaCircular/ListaCircular.h"

int main()
{
    Lista lista;
    crearLista(&lista);


    int num1 = 1;
    int num2 = 2;
    int num3 = 10;
    int num4 = 5;

    int destino;

    encolarOrdSinDuplicados(&lista,&num3,sizeof(int),comparar);//10
    encolarOrdSinDuplicados(&lista,&num2,sizeof(int),comparar);//2
    encolarOrdSinDuplicados(&lista,&num4,sizeof(int),comparar);//5


    desencolar(&lista,&destino,sizeof(int));
    printf("\nResultado: %d",destino);

    desencolar(&lista,&destino,sizeof(int));
    printf("\nResultado: %d",destino);
//
//    desencolar(&lista,&destino,sizeof(int));
//    printf("\nResultado: %d",destino);

    return 0;
}
