#include "header.h"

void eliminarOcurrencias(int* vec, int* cantElem,int elem){

    /*Se aplica algoritmo para eliminar las ocurrencias de un numero en un vector desordenado de enteros, con
    la optimización de que para los casos donde haya dos numeros enteros iguales y seguidos dentro de un vector, la funcion
    eliminara los dos elementos o mas de una sola iteracion*/



    //CALCULA LA DIRECCION DE MEMORIA DEL ULTIMO ELEMENTO DEL VECTOR
    int* fin = (vec+1*(*cantElem))-1;
    int contDuplicados=0;

    //ITERO SOBRE EL VECTOR BUSCANDO COINCIDENCIAS Y EN CASO DE ENCONTRAR, LAS ELIMINO
    for(int* i=vec;i<=fin;i++){
        if(*i==elem){


            //SI EL ELEMENTO ES DISTINTO AL ELEMENTO QUE LE SIGUE, SE LO ELIMINA
            if(*i != *(i+1)){

                desplazarVector(fin,i,contDuplicados);
                (*cantElem)--;
                contDuplicados=0;

            //SI EL ELEMENTO QUE LE SIGUE ES IGUAL, SE INCREMENTA EL CONTADOR DE  DUPLICADOS CON EL
            //OBJETIVO DE REDUCIR EL NUMERO DE ITERACIONES EN LOS CASOS DONDE HAYA DOS NUMEROS IGUALES Y CONTIGUOS
            }else{

                contDuplicados=contDuplicados+1;

            }

        }


    }



}



void desplazarVector(int* fin,int* i,int contDuplicados){

    //REDUZCO EN UNA UNIDAD LA CANTIDAD DE ELMENTOS
    fin = fin - 1 - 1 * contDuplicados;
    //REDUZCO LA VARIABLE "i" PARA RESTROCEDER HASTA LA PRIMERA APARICION DEL NUMERO REPETIDO (EN CASO DE QUE APAREZCA MAS DE UNA VEZ
    //DE MANERA SEGUIDA)
    i-=contDuplicados;
    //DEFINO CUANTOS VAN A SER LOS NUMEROS QUE SE VAN A ELIMINAR
    int incremento = 1+1*contDuplicados;

    //ELIMINO Y DESPLAZO LOS ELEMENTOS RESTANTES DEL VECTOR PARA TAPAR EL ESPACIO VACIO RESULTANTE EN EL VECTOR
   for(int* j=i;j<=fin;j++)
        *j=*(j+incremento);
}
