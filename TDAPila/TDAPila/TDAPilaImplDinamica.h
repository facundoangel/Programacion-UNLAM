#ifndef TDAPILAIMPLDINAMICA_H_INCLUDED
#define TDAPILAIMPLDINAMICA_H_INCLUDED

typedef struct SNodo{

    void *info;
    unsigned tam;
    struct SNodo *sig;

}Nodo;



typedef Nodo* PilaDin;

#endif // TDAPILAIMPLDINAMICA_H_INCLUDED
