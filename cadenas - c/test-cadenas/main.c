#include <stdio.h>
#include <stdlib.h>
#include "../library-cadenas/cadenas.h"

int main()
{

    /*este programa toma como parametro un string con caracteres random y con la libreria creada normaliza el
    texto*/



    system("chcp 1252 >nul");
    char* stringPrueba1 = "###hol aaa tt yu ypyyy fa?)897786767cundó hola$%&%56123439";


    Palabra pal1;
    Secuencia sec1;

    sec1.cursor=stringPrueba1;
    LeerPalabra(stringPrueba1,&pal1,&sec1);
    putchar('\n');
    for(char* i=pal1.ini;i<=pal1.fin;i++){
        putchar(*i);
    }
    if((*(sec1.cursor))==' ')
            putchar(' ');

    while((*(sec1.cursor))!='\0'){
        if(LeerPalabra(stringPrueba1,&pal1,&sec1)){

            for(char* i=pal1.ini;i<=pal1.fin;i++){
                putchar(*i);

        }

        }
        if((*(sec1.cursor))==' ')
            putchar(' ');
    }






    return 0;
}
