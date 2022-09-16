#include <stdlib.h>
#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

typedef struct{
    int codigo;
    char nombre[30];
    float price;
}PRODUCTOS;


void crearArchivo(char* nombreArchivo);
void leerArchivo(char* nombreArchivo);

#endif // ARCHIVOS_H_INCLUDED
