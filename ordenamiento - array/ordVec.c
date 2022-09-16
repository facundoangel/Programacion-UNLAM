#include "ordVec.h"

void ordenarVectorInser(int* vec, int* ce){
    /*ordenamiento de un vector por el metodo de inserción*/
    int ceOrd=1, j=0,aux;

    for(int i=1;i<(*ce);i++){
        //printf("\nbucle for(1): %d",i);
        //mostrarVector(vec,*ce);
        for(j=0;j<ceOrd;j++){
            //printf("\nbucle for(2): %d",j);
            if(vec[j]>vec[i]){
                aux=vec[j];
                vec[j]=vec[i];
                vec[i]=aux;
            }
        }
        ceOrd++;
    }

}


void mostrarVector(int* vc,int ce){
    printf("\n============Vector resultado==============\n\n");
    printf("{ ");
    for(int i=0;i<ce;i++){
        printf("%d ",vc[i]);
    }
    printf("}");
    printf("\n\n========================================");

}
