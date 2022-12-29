#ifndef TDACOLADINIMPL_H_INCLUDED
#define TDACOLADINIMPL_H_INCLUDED
#define TAM 42

typedef struct SNodo {

    void *info;
    unsigned tamElemento;
    struct SNodo *sig;

}TNodo;

typedef struct{

    TNodo* ini;
    TNodo* fin;

}Cola;


#endif // TDACOLADINIMPL_H_INCLUDED
