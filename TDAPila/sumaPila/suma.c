#include "suma.h"


void IngresarNumeros(char* num1,char* num2)
{


    int i=1;
    printf("\nIngrese el numero %d a sumar:",i);
    gets(num1);
    i++;
    printf("\nIngrese el numero %d a sumar:",i);
    gets(num2);

}



void inicializarPila(Pila* pp,char* num1)
{
    char *i = num1;


    while(*i)
    {
        if(esNumero(*i))
            apilar(pp,i,sizeof(*i));
        ++i;

    }

}



void igualarLongitud(char* num1,char* num2)
{
    char *menorString;
    char cerosAAgregar[20];
    int diferencia = strlen(num1)-strlen(num2);

    if(diferencia==0)
        return;

    if(diferencia<0)
        menorString = num1;
    else
        menorString = num2;


    for(int i = 0; i < ABS(diferencia); i++)
    {
        cerosAAgregar[i] = '0';

    }
    cerosAAgregar[ABS(diferencia)+1] = '\0';

    strcat(cerosAAgregar,menorString);
    strcpy(menorString,cerosAAgregar);


}

int sumarCaracteres(char num1, char num2)
{
    int numEntero1 = num1 - '0';
    int numEntero2 = num2 - '0';


    return numEntero1 + numEntero2;
}

void sumarPilas(Pila* p1, Pila* p2, Pila* resultado)
{
    char dig1, dig2, caracterResultado;
    char *caracterLeido = (char*) malloc(sizeof(char));
    int resultadoSuma;
    int acarreo=0;

    while(!pilaVacia(p1))
    {

        desapilar(p1,caracterLeido,sizeof(caracterLeido));
        dig1 = *caracterLeido;
        desapilar(p2,caracterLeido,sizeof(caracterLeido));
        dig2 = *caracterLeido;
        resultadoSuma = sumarCaracteres(dig1,dig2) + acarreo;
        acarreo = resultadoSuma / 10;
        resultadoSuma %= 10;
        caracterResultado = resultadoSuma + '0';
        apilar(resultado,&caracterResultado,sizeof(caracterResultado));



    }

    if(acarreo==1)
    {
        caracterResultado = '1';
        apilar(resultado,&caracterResultado,sizeof(caracterResultado));
    }

    free(caracterLeido);

}


void mostrarPila(Pila* pp)
{
    char *caracterLeido = (char*) malloc(sizeof(char));
    Pila pMuestra = *pp;
    printf("\n Pila: {");

    while(!pilaVacia(&pMuestra))
    {

        desapilar(&pMuestra,caracterLeido,sizeof(caracterLeido));
        printf(" %c",*caracterLeido);

    }
    printf(" }");
    free(caracterLeido);
}


//C:\Users\facun\OneDrive\Escritorio\Programacion-UNLAM\pila - c\sumaPila\suma.c|65|warning: 'caracterLeido' may be used uninitialized in this function [-Wmaybe-uninitialized]|
