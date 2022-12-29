#include "busqBinaria.h"
#include <stdlib.h>
#include <stdio.h>
#define mitad(a) ((a)/2)


int busquedaBinaria(int vc[],int tam){

    int mitad = mitad(tam);

    int buscado = 8,encontrado,inicio=0,fin=tam-1,flag;


    while(flag!=0)
    {

        if(mitad>buscado){
            fin = mitad;
            mitad = mitad / 2;
        } else if(mitad<buscado){
            inicio = mitad;
            mitad = mitad + mitad /2;
        } else if(mitad==buscado){
            return mitad;
        }

        /*if(fin-inicio < 5){
            for(int i=inicio;i<=fin;i++){
            flag=1;
            if(vc[i]==buscado)
                return i;
        }
        }*/
        printf("\n vuelta");
    }

    return -1;
}
