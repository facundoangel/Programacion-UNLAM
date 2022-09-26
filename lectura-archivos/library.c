#include "txtABin.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>




void crearTxtVar()
{

    FILE *pf;
    pf=fopen("empleados.txt","wb");

    Empleado empleados[] ={
        {40640924, "facundo angel", {11,10,1997}, 40000},
        {40640924, "pedro angel", {11,9,1997}, 40000},
        {15467934, "juan sanchez", {11,9,1997}, 40000},
        {29746832, "martin alvarez", {11,9,1997}, 40000},
        {10234567, "joaquin gutierrez", {01,9,1997}, 40000}

    };
    int cantEmpleados = sizeof(empleados)/sizeof(Empleado);


    for(int i=0;i<cantEmpleados;i++)
        fprintf(pf,"%8d|%-30s|%02d/%02d/%02d|%09d\n",empleados[i].dni,empleados[i].nomYApe,empleados[i].fNac.d,empleados[i].fNac.m,empleados[i].fNac.a,empleados[i].sueldo);



    fclose(pf);


}

bool errorFatal(int cod)
{
    return (cod==TODO_OK)? false : true;

}


int txtABinFijo(char* linea,Empleado *emp)
{

    char *act = strrchr(linea,'\n');
    if(!act)
        return ERROR_LINEA_LARGA;

    *act='\0';
    act-=9;
    sscanf(act,"%9d",&emp->sueldo);
    act--;


    *act='\0';
    act-=10;
    sscanf(act,"%2d/%2d/%4d",&emp->fNac.d,&emp->fNac.m,&emp->fNac.a);
    act--;

    *act='\0';
    act-=30;
    strncpy(emp->nomYApe,act,TAM_NOM_APE);
    act--;


    *act='\0';
    act-=8;
    sscanf(act,"%d",&emp->dni);
    //act--;

    //printf("\nsueldo: %09d",emp->sueldo);


    return TODO_OK;

}



int archivoTxtABin(const char* nombreTxt, const char* nombreBin)
{
    int codRet = TODO_OK;
    bool errF = false;
    Empleado empleadoTmp;


    FILE *arcTxt = fopen(nombreTxt,"rt");
    FILE *arcBin = fopen(nombreBin,"wb");


    if(arcTxt==NULL || arcBin==NULL)
    {
        printf("\nError: No se pudieron crear o leer los archivos");
        exit(1);

    }


    char linea[TAM_LINEA];

    while(!errF && fgets(linea,TAM_LINEA,arcTxt))
    {

        codRet = txtABinFijo(linea,&empleadoTmp);
        printf("%8d|%-30s|%02d/%02d/%02d|%09d\n",empleadoTmp.dni,empleadoTmp.nomYApe,empleadoTmp.fNac.d,empleadoTmp.fNac.m,empleadoTmp.fNac.a,empleadoTmp.sueldo);
        errF = errorFatal(codRet);
        if(codRet==TODO_OK)
            fwrite(&empleadoTmp,sizeof(Empleado),1,arcBin);

    }


    fclose(arcTxt);
    fclose(arcBin);

    return (errF)? ERROR_FATAL : TODO_OK;
}
