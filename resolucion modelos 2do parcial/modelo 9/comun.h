#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Accion) (const void* elem, void* aux);

#endif // COMUN_H_INCLUDED
