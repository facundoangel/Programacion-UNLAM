#include "header.h"

int main()
{
    int vect[10];
    int cont = 0;

    printf("Ingresar numeros random (0 para terminar)\n");

    do{
        printf("Ingresar numero %d:\n",cont+1);
        fflush(stdin);
        scanf("%d",&vect[cont]);
        cont++;

    }while(cont < 5);

    puts("ciclo terminado");
    viewArray(vect);


    printf("primer elemento (main) %d \n",vect[0]);

    return 0;
}
