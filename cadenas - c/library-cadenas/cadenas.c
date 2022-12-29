#include "cadenas.h"
#include <stdio.h>

bool LeerPalabra(char* stringALeer,Palabra* pal,Secuencia* sec){



    char* i=sec->cursor;



    while((!esLetra(*i))){
        i++;
        if((*i) == '\0'){
            sec->cursor='\0';
            return false;
        }

    }



    if(esLetra(*i)){
        //printf("\nCadena No Nula\n\n");
        pal->ini=i;

        sec->cursor=i+1;
        sec->fin=false;
    }



    while(!sec->fin){

        if(esLetra(*i)){
            sec->cursor=i+1;
            pal->fin=i;
            //printf("\nif(letra)");
        }else if((*i)=='\0'){
            sec->cursor=i;
            sec->fin=true;
            pal->fin=i-1;
            //printf("\nif(fin)");
            return true;
        } else if((*i)==' '){
            sec->cursor=i;
            sec->fin=true;
            pal->fin=i-1;
            //printf("\nif(espacio)");
            return true;
        }else if(!esLetra(*i)){
            sec->cursor=i;
            pal->fin=i-1;
            sec->fin=true;
            //printf("\nif(no letra)");
            return true;
            }
        ++i;
    }






    //return true;
}
