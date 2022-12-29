#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "library.h"

void crearArchivo()
{
    FILE* pf;

    pf = fopen("empleados.dat","wb");

    if(pf==NULL){
        printf("\nError: No se pudo crear el Archivo");
        exit(1);
    }


    EMPLEADO empleados[] = {

        {"facundo","angel",2},
        {"juan","perez",20},
        {"manolo","gonzalez",6},
    };



    int cantEmpl = sizeof(empleados)/sizeof(EMPLEADO);

    fwrite(empleados,sizeof(EMPLEADO),cantEmpl,pf);
    fclose(pf);

}

void mostrarEmpleados()
{

    FILE* pf;
    EMPLEADO empleadoTmp;
    int i=1;

    pf = fopen("empleados.dat","rb");

    if(pf==NULL){
        printf("\nError: No se pudo leer el Archivo");
        exit(1);
    }

    fread(&empleadoTmp,sizeof(EMPLEADO),1,pf);
    printf("\n\n=========  EMPLEADOS LEIDOS  ================");
    if(feof(pf))
        printf("\nSin datos disponibles");
    while(!feof(pf)){
        printf("\n%-16s%-12s\t%d\t%d",empleadoTmp.nombre,empleadoTmp.apellido,empleadoTmp.antiguedad,i);
        fread(&empleadoTmp,sizeof(EMPLEADO),1,pf);
        i++;
    }
    printf("\n==============================================");

     fclose(pf);
}

bool preguntarEdicionUsuario()
{
    char response;
    do{
        printf("\n\n¿Desea editar algún registro? (s/n): ");
        fflush(stdin);
        response = getchar();
        if(response!='s' && response!='n')
            printf("\nError: Respuesta Erronea");
    } while(response!='s' && response!='n');

    return response=='s';

}

void ingresarNombreApellidoEmpleado(char* dato,EMPLEADO* EmpleadoAEditar)
{
    char datoActualizado[12];
    printf("\n\nIngrese %s del empleado: ",dato);
    fflush(stdin);
    gets(datoActualizado);
    if(strcmp(dato,"nombre")==0)
    {

        strcpy(EmpleadoAEditar->nombre,datoActualizado);
    } else if(strcmp(dato,"apellido")==0)
    {

        strcpy(EmpleadoAEditar->apellido,datoActualizado);
    }

}

void editarDatos(){

    FILE *pf;
    EMPLEADO empleadoTmp;
    void (*pfunc)(EMPLEADO);
    int opcion;

    pf = fopen("empleados.dat","r+");

    if(pf==NULL){
        printf("\nError: No se pudo leer el Archivo");
        exit(1);
    }



    do{
        fflush(stdin);
        printf("\n\nIngrese numero de empleado a editar: ");
        scanf("%d",&opcion);
        if(opcion<0)
            printf("\nError: Respuesta Erronea");
    } while(opcion<0);

    //LEO LOS DATOS DEL EMPLEADO SELECCIONADO
    fseek(pf,(size_t) sizeof(EMPLEADO)*(opcion-1),SEEK_SET);
    fread(&empleadoTmp,sizeof(EMPLEADO),1,pf);
    printf("\n%-16s%-12s\t%d",empleadoTmp.nombre,empleadoTmp.apellido,empleadoTmp.antiguedad);
    fseek(pf,(int) -sizeof(EMPLEADO),SEEK_CUR);


     do{
        fflush(stdin);
        printf("\n\n¿Qué acción se necesita hacer sobre el usuario?: ");
        printf("\n\t1.Cambiar nombre ");
        printf("\n\t2.Cambiar apellido ");
        printf("\n\t3.Cambiar Antiguedad ");
        printf("\nIngrese opción: ");
        scanf("%d",&opcion);
        if(opcion<0)
            printf("\nError: Respuesta Erronea");
    } while(opcion<0);


    //REALIZO ACCION SOBRE EL EMPLEADO
    switch(opcion){
        case 1:
            ingresarNombreApellidoEmpleado("nombre",&empleadoTmp);
            fwrite(&empleadoTmp,sizeof(EMPLEADO),1,pf);

            break;
        case 2:
            ingresarNombreApellidoEmpleado("apellido",&empleadoTmp);
            fwrite(&empleadoTmp,sizeof(EMPLEADO),1,pf);
            break;
        case 3:
            printf("\nOpción 3");
            break;
        default:
            printf("\ndefault");

    }


     fclose(pf);
}
