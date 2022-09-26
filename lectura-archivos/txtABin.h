#include <stdbool.h>
#ifndef TXTABIN_H_INCLUDED
#define TXTABIN_H_INCLUDED



#define TODO_OK 0
#define ERROR_FATAL 1
#define TAM_LINEA 100
#define ERROR_LINEA_LARGA 2
#define TAM_NOM_APE 30



typedef struct{
        int d;
        int m;
        int a;
    }FechaNac;

typedef struct{

    int dni;
    char nomYApe[25];
    FechaNac fNac;
    int sueldo;

} Empleado;



void crearTxtVar();
bool errorFatal(int cod);
int txtABinFijo(char* linea,Empleado *emp);
int archivoTxtABin(const char* nombreTxt, const char* nombreBin);



#endif // TXTABIN_H_INCLUDED
