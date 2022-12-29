#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include <stdbool.h>

typedef struct {

    char nombre[16];
    char apellido[12];
    int antiguedad;

} EMPLEADO;

void crearArchivo();
void mostrarEmpleados();
bool preguntarEdicionUsuario();
void editarDatos();

#endif // LIBRARY_H_INCLUDED
