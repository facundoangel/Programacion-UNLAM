#include "vectores.h"

#define VECTOR_LLENO 1
#define ELEMENTO_REPETIDO 2
#define AGREGADO_EXITOSO 0


/* -------------------------------------------------------------------------- */
/*                           FUNCIONES DESARROLLADAS                          */
/* -------------------------------------------------------------------------- */

int ordenarVector(int* vec, int ce){ //Ordenar vector.
    int aux;

    if (DEBUG) {
        printf("\nVector de entrada (desordenado): {");
        for(int i = 0; i < ce; i++){printf("%d ", vec[i]);};
        printf("}.\n ");
    };

    /*for(int i=0;i<ce;i++){
        for(int j=i+1;j<ce;j++){

            if(vec[i] > vec[j]){
                aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }

        }
    }*/

    int i=0,j,desorden=0,cota=ce-1;

    while(desorden!=-1){

        desorden = -1;

        for(j=0;j<cota;j++){

            if(vec[j]>vec[j+1])
            {
                aux = vec[j+1];
                vec[j+1] = vec[j];
                vec[j] = aux;
                desorden = j;
            }
        }

        cota = desorden;




    }


    printf("\nVector de salida (ordenado): { ");
    for(int i=0; i<ce;i++){
        printf("%d ",vec[i]);
    }
    printf("}\n ");
    return 0;
}

int agregarElementoVector(int* vec, int* ce, int dato){//agrega elemento a un vector odenado


     if (DEBUG) {
        printf("\nVector de entrada (funcion agregar): {");
        for(int i = 0; i < (*ce); i++){printf("%d ", vec[i]);};
        printf("} => ");
    };

    if(*ce >= TAM)
        return VECTOR_LLENO;


    //SE BUSCA EL LUGAR DONDE ENCAJE EL NUMERO DENTRO DEL VECTOR ORDENADO
    int i=0;
    while(dato >= vec[i] && i<*ce)
        i++;

    if(dato == vec[i-1])
        return ELEMENTO_REPETIDO;

    //SE DESPLAZAN TODOS LOS DEMAS ELEMENTOS PARA QUE ENTRE EL NUEVO ELEMENTO
    for(int j=*ce;j>i;j--)
        vec[j] = vec[j-1];

    //SE INSERTA EL ELEMENTO NUEVO DENTRO DEL VECTOR
    vec[i]=dato;
    (*ce)++;

    if (DEBUG) {
        printf("{");
        for(int i = 0; i < *ce; i++){printf("%d ", vec[i]);};
        printf("}.\n ");
    };

    return AGREGADO_EXITOSO;

}

void eliminarElementoVector(int* vec, int* ce, int dato) { //Eliminar elemento del vector.

    //Obtiene posición del dato.
    int i = 0;
    while (dato < vec[i]) {i++;};

    //Remplaza con el valor del elemento a la derecha, cada elemento.
    for (int j = i; j <= (*ce) - 2; j++) {
        vec[j] = vec[j+1];
    }

    (*ce)--; //Modifica el tamaño del vector.

    if (DEBUG) {
        printf("\nVector de entrada (elemento eliminado): {");
        for(int i = 0; i < (*ce); i++){printf("%d ", vec[i]);};
        printf("}.\n ");
    };
}


void eliminarElementosDuplicadosVector(int* vec, int* ce, int dato) { //Eliminar elemento duplicado del vector.

    ordenarVector(vec, *ce);

    int i,contRepeticion=0,indiceRepeticion;
    bool banderaHayRepetidos=false;

    if (DEBUG) {
        printf("\nVector de entrada (con duplicados): {");
        for(int i = 0; i < *ce; i++){printf("%d ", vec[i]);};
        printf("}.\n ");
    };

    //Recorro el vector buscando repetidos
    for(i=1;i<*ce;i++){
        //si encuentro repetidos guardo cuento la cantidad de repeticiones
        //del elemento
         if(vec[i]==vec[i-1])
        {

            if(!banderaHayRepetidos)
                indiceRepeticion=i;

            banderaHayRepetidos=true;
            contRepeticion++;

            //evaluo si ya no hay mas repetidos posteriores al elemento
            if(vec[i]!=vec[i+1])
            {

                //piso los elementos repetidos desplazando a la izquierda los demas elementos
                for(int j=indiceRepeticion;j<((*ce));j++)
                {
                    //desplazo los elementos la misma cantidad de repetidos haya
                    vec[j] = vec[j+contRepeticion];
                    banderaHayRepetidos=false;
                }
                (*ce)-=contRepeticion;
                contRepeticion=0;
                i=indiceRepeticion;

            }

        }


    }




    if (DEBUG) {
        printf("\nVector de salida (sin duplicados): {");
        for(int i = 0; i < *ce; i++){printf("%d ", vec[i]);};
        printf("}.\n ");
    };
}
