#include "library.h"

void insertPerson(Person* personToCreate)
{

    //int num;
    //Person personToCreate;
    puts("Ingrese apellido de persona");
    fflush(stdin);
    gets(personToCreate->apellido);
    puts("Ingrese nombre de persona");
    fflush(stdin);
    gets(personToCreate->nombre);
    puts("Ingrese edad de persona");
    fflush(stdin);
    scanf("%d",&personToCreate->edad);
    //printf("=========name: %s surname: %s age: %d=========",personToCreate.nombre,personToCreate.apellido,personToCreate.edad);
    //printf("nombre: %s \n",per->nombre);
    //printf("edad: %d",per->edad);

}


void viewPerson(const Person* param){

    printf("=========name: %s surname: %s age: %d=========",param->apellido,param->nombre,param->edad);

}



void modificPerson(int persona[]){

    persona[0]=999;
    printf("\nedad: %d",persona[0]);


}
