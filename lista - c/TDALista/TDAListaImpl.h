#ifndef TDALISTAIMPL_H
#define TDALISTAIMPL_H

typedef struct SNodo{

    void *info;
    unsigned tamElemento;
    struct SNodo *sig;
}TNodo;

typedef TNodo *Lista;


#endif // TDALISTAIMPL_H
