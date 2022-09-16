#include <stdbool.h>

#ifndef CADENAS_H_INCLUDED
#define CADENAS_H_INCLUDED
#define esLetra(c) (((c)>='a' && (c)<='z') || ((c)>='A' && (c)<='Z') || (c)=='�' || (c)=='�' || (c)=='�' || (c)=='�' || (c)=='�' || (c)=='�' || (c)=='�')


typedef struct{
    char* cursor;
    bool fin;
}Secuencia;

typedef struct{
    char* ini;
    char* fin;
}Palabra;


bool LeerPalabra(char* stringALeer,Palabra* pal,Secuencia* sec);


#endif // CADENAS_H_INCLUDED
