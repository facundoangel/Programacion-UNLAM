#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED


typedef struct
{

    char cod[4];
    char descripcion[15];
    float precio;
    int cant;

}PRODUCTO;

typedef struct
{
    char cod[4];
    int cant;
}MOVIMIENTO;

void genrarArchivos();
void mostrarArchivos();
void mostrarArchivoTMP();
void mergeAlgoritmo(char* prod,char* mov);

#endif // ARCHIVOS_H_INCLUDED
