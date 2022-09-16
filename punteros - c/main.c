#include "library.h"


int main()
{

    //Person personToCreate;
    //Person personToCreate = {"pedro","perez",25};
    int persona[5];
    persona[0]=111;
    printf("Ejecucion del programa principal y declaracion de las variables principales\n");
    //viewPerson(&personToCreate);
    printf("\nedad: %d",persona[0]);
    modificPerson(persona);
    //printf("\n=========name: %s surname: %s age: %d========= (main)",personToCreate.nombre,personToCreate.apellido,personToCreate.edad);
    printf("\nedad: %d",persona[0]);
    return 0;
}
