#include "ordVec.h"

int main()
{
    int vc[] = {12,0,2,3,4,45,15,12};
    int ce= sizeof(vc) / sizeof(vc[0]);
    //mostrarVector(vc,ce);
    printf("\nTEST NRO 1: (algoritmo burbuja)");
    ordenarVectorBurbuja(vc,&ce);
    mostrarVector(vc,ce);

    int vc2[] = {12,0,2,3,4,45,15,12};
    int ce2= sizeof(vc2) / sizeof(vc2[0]);
    //mostrarVector(vc,ce);
    printf("\nTEST NRO 1: (algoritmo insercion)");
    ordenarVectorInser(vc2,&ce2);
    mostrarVector(vc,ce);



//    int vc2[] = {12,0,2,3,4,45,15,12};
//    int ce2= sizeof(vc2) / sizeof(vc2[0]);
//    //int vc[] = {45,56,45};
//    printf("\nTEST NRO 2: (algoritmo burbuja)");
//    ordenarVectorBurbuja(vc2,&ce2);
//    mostrarVector(vc2,ce2);
//
//
//    int vc3[] = {7,6,5,4,3,2,1};
//    int ce3= sizeof(vc3) / sizeof(vc3[0]);
//    printf("\nTEST NRO 3: (algoritmo burbuja)");
//    ordenarVectorBurbuja(vc3,&ce3);
//    mostrarVector(vc3,ce3);


    return 0;
}
