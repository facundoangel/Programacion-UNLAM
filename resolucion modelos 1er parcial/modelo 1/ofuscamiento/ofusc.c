#include <string.h>
#include "ofusc.h"
#include <stdbool.h>
#include <stdio.h>


#define esLetra(a) (((a) >= 65 && (a) <= 90) || ((a) >= 97 && (a) <= 122) || (a)==164 || (a)==165)
#define esVocal(a) ((a)==65 || (a)==97 || (a)==69 || (a)==101 || (a)==73 || (a)==105 || (a)==79 || (a)==111 || (a)==85 || (a)==117)

int vocalANumero(int caracter)
{
    int numeroSalida;

    switch(caracter){

    case 65:
    case 97:
        numeroSalida=5;
        break;
    case 69:
    case 101:
        numeroSalida=4;
        break;
    case 73:
    case 105:
        numeroSalida=3;
        break;
    case 79:
    case 111:
        numeroSalida=2;
        break;
    case 85:
    case 117:
        numeroSalida=1;
        break;


    }

    return numeroSalida;
}


void desplazarCaracter(char* caracter,int cantLetras)
{
    bool mayus = (*caracter <= 90)? true : false;

    int numero = *caracter - cantLetras;

    if(mayus)
        numero = (numero<65)? 90 - (64 - numero): numero;
    else
        numero = (numero<97)? 122 - (96 - numero): numero;


    if(esVocal(numero))
        *caracter = '0' + vocalANumero(numero);
    else
        *caracter = numero;

}

void cifrarPalabra(char* inicio, char* fin,int cantLetras)
{


    for(char *i=inicio;i<=fin;i++)
    {
        desplazarCaracter(i,cantLetras);
    }

}


void cifrarLinea(char* linea)
{

    char *pl = linea,*iniPalabra;
    char *finPalabra;
    int contadorLetras=0;

    while(!esLetra(*pl))
        pl++;

    iniPalabra=pl;

    while(*pl!='\0')
    {
        if(esLetra(*pl))
        {
            contadorLetras++;
            finPalabra=pl;
        }

        if(!esLetra(*pl) || *(pl+1)=='\0')
        {
            cifrarPalabra(iniPalabra,finPalabra,contadorLetras);
            iniPalabra=pl+1;
            contadorLetras=0;
        }



        pl++;


    }

}

bool leerLinea(char* nombreArchivo, char* linea)
{
    FILE *pf, *pfTemporal;

    pf = fopen(nombreArchivo,"r");
    pfTemporal = fopen("temporal.tmp","w");

    if(pf==NULL || pfTemporal==NULL)
        return false;


    while(fgets(linea,TAM_LINEA,pf)!=NULL)
    {

        cifrarLinea(linea);
        printf("\nlinea: %s",linea);
        fprintf(pfTemporal,"%s",linea);
    }


    fclose(pf);
    fclose(pfTemporal);

    remove("entrada.txt");
    rename("temporal.tmp","entrada.txt");


    return true;
}
