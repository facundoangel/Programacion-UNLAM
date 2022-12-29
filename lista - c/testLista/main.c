#include <stdio.h>
#include <stdlib.h>
#include "../TDALista/TDALista.h"
#include "../TDALista/TDAListaImpl.h"

int main()
{
    Lista lista;

    int num = 123;




   crearLista(&lista);
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=2;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=3;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=7;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=5;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=10;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=20;
    InsertarEnListaOrdSinDup(&lista,&num,sizeof(num),comparar);
    num=0;
    InsertarEnListaDesordAlFinal(&lista,&num,sizeof(num));
    num=-2;
    InsertarEnListaDesordAlFinal(&lista,&num,sizeof(num));
    num=30;
    InsertarEnListaDesordSinDup(&lista,&num,sizeof(num));
    num=2;
    InsertarEnListaDesordSinDup(&lista,&num,sizeof(num));
    num=0;
    InsertarEnListaDesordSinDup(&lista,&num,sizeof(num));
    mostrarLista(&lista);
    num=0;
    EliminarElementoListaOrd(&lista,&num,sizeof(num), comparar);
    num=10;
    EliminarElementoListaOrd(&lista,&num,sizeof(num), comparar);
    num=-2;
    EliminarElementoListaOrd(&lista,&num,sizeof(num), comparar);
    mostrarLista(&lista);


    return 0;
}
