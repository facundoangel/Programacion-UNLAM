#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nombre[20];
    char apellido[20];
    int edad;
    }Person;

void insertPerson(Person*);
void viewPerson(const Person*);
void modificPerson(int persona[]);
//void modificPerson();
//void modificPerson(int[]);


#endif // LIBRARY_H_INCLUDED
