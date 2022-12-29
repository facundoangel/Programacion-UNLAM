#include <stdio.h>
#include <stdlib.h>
#include "../TDAListaDobleEnlace/ListaDobleEnlace.h"


int main()
{
    Lista lista;

    int numero1 = 1;
    int numero2 = 4;
    int numero3 = 2;
    int numero4 = 10;
    int numero5 = 3;
    int numero6 = 20;
    int numero7 = 0;
    int numero8 = 35;

    int numeroDest;

    crearLista(&lista);
    enlistarEnOrdCDup(&lista,&numero1,sizeof(int),comparar);// ->1
    enlistarEnOrdCDup(&lista,&numero1,sizeof(int),comparar);// ->1
    enlistarEnOrdSDup(&lista,&numero3,sizeof(int),comparar,actualizar);// ->1
    enlistarEnOrdSDup(&lista,&numero4,sizeof(int),comparar,actualizar);// ->1
    enlistarEnOrdSDup(&lista,&numero5,sizeof(int),comparar,actualizar);// ->1
    enlistarEnOrdSDup(&lista,&numero6,sizeof(int),comparar,actualizar);// ->1
    enlistarEnOrdSDup(&lista,&numero6,sizeof(int),comparar,actualizar);// ->1
    enlistarEnOrdSDup(&lista,&numero8,sizeof(int),comparar,actualizar);// ->1


    mostrarLista(&lista,mostrarNumero);

//    desenlistar(&lista,&numeroDest,sizeof(int));// 1 2 ->4 10
//    printf("\nDesencolado: %d",numeroDest);
//
//    desenlistar(&lista,&numeroDest,sizeof(int));// 1 2 ->10
//    printf("\nDesencolado: %d",numeroDest);
//
//    desenlistar(&lista,&numeroDest,sizeof(int));// 1 ->2
//    printf("\nDesencolado: %d",numeroDest);
//
//    desenlistar(&lista,&numeroDest,sizeof(int));//->1
//    printf("\nDesencolado: %d",numeroDest);



    return 0;
}
