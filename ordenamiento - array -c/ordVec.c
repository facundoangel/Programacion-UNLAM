#include "ordVec.h"

void ordenarVectorInser(int* vec, int* ce){
    /*ordenamiento de un vector por el metodo de inserción*/
    int ceOrd=1, j=0,aux, cont=0;

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
        cont++;
        }
        ceOrd++;
        cont++;
    }

    printf("\niteraciones realizadas: %d",cont);

}


void ordenarVectorBurbuja(int* vec, int* ce){
    /*ordenamiento de un vector por el metodo de inserción*/
    int desorden=0, cota=*ce-1;
    int aux, i, cont=0;

    while(desorden!=-1)
    {
        desorden=-1;
        for(i=0;i<cota;i++)
        {
            if(vec[i]>vec[i+1])
            {
                aux=vec[i+1];
                vec[i+1]=vec[i];
                vec[i]=aux;
                desorden=i;
            }

            cont++;
        }

        cota=desorden;


    }

    printf("\niteraciones realizadas: %d",cont);
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
