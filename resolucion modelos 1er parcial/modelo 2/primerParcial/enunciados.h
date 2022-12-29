#ifndef ENUNCIADOS_H_INCLUDED
#define ENUNCIADOS_H_INCLUDED
#include <stdbool.h>

#define esLetra(a) (((a)>='A' && (a)<='Z') || ((a)>='a' && (a)<='z') || (a)=='á' || (a)=='é' || (a)=='í' || (a)=='ó' || (a)=='ú' || (a)=='ñ' || (a)=='Ñ')
#define esCaracterPermitido(a) ((a)==' ' || (a)==',')

typedef struct{

    int codigo;
    char nombre[40];
    int stock;
    float precio;

}Producto;

typedef struct SNodo{
    void* info;
    unsigned tamElemento;
    struct SNodo* sig;

}TNodo;

typedef TNodo* Lista;
typedef int (*Cmp) (int num1,int num2);

void normalizarTexto(char* entrada, char* salida);
void generarArchivosAlmacen();
void mostrarLinea(Producto* linea);
int comparar(int num1, int num2);
bool mergeArchivos();
bool leerListadoFinal(Lista* pl);
void crearLista(Lista* pl);
void actualizarNodo(TNodo* n, Producto* prod);
bool eliminarDuplicados(Lista* pl);
bool mostrarLista(Lista* pl);
void vaciarLista(Lista* pl);
bool InsertarEnListaDesordAlFinal(Lista* pl,void* elem, size_t tamElemento);
bool InsertarEnListaDesordAlIni(Lista* pl,const void* elem, size_t tamElemento);
bool generarArchivoMovimientos();
bool generarListadoAPartirLista(Lista* pl);
bool actualizarArchivoFinal(Cmp cmp);

#endif // ENUNCIADOS_H_INCLUDED
