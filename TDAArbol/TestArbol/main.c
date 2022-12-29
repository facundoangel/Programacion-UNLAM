#include <stdio.h>
#include <stdlib.h>
#include "../TDAArbol/arbol.h"


#define ARC_EMP 1

typedef struct{

    int dni;
    char nombre[20];
    char apellido[20];
    int edad;
} Empleado;




void crearArchivoBin(char* arcNombre)
{
    Empleado empleados[] = {{123,"facundo","angel",25},
                            {222,"federico","perez",20},
                            {333,"daniel","gonzalez",45},
                            {111,"ramon","diarte",45},
                            {555,"santiago","iraola",20}};
    int ce = sizeof(empleados) / sizeof(Empleado);
    FILE* pf = fopen(arcNombre,"wb");

    fwrite(empleados,sizeof(Empleado),ce,pf);

    fclose(pf);
}

NodoA* leer(NodoA* nodo,FILE* pf,int pos)
{
    Empleado emp;
    Indice ind;


    fseek(pf,pos*sizeof(Empleado),SEEK_SET);
    fread(&emp,sizeof(Empleado),1,pf);

    ind.dni=emp.dni;
    ind.pos=pos;

    nodo->elem=(Indice*)malloc(sizeof(Indice));
    if(!nodo->elem)
        return NULL;

    memcpy(nodo->elem,&ind,sizeof(Indice));

    return nodo;
}


void imprimirIndice(Arbol *pa,int n)
{
    if(!*pa)
        return;

    Indice* ind = (*pa)->elem;
    printf("\n");

    while(n>0)
    {
        printf("\t");
        n--;
    }

    printf("%d | %d",ind->pos,ind->dni);
}

int main(int argc, char* argv[])
{

    system("chcp 1252 > nul");

    Arbol ar;
    //int num = 2;
    crearArchivoBin(argv[ARC_EMP]);


    crearArbol(&ar);
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);
//    num = 5;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);
//    num = 7;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);
//    num = 3;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);

//    int numBuscado = 5;
//    if(buscarEnArbol(&ar,&numBuscado,sizeof(int),compararElem))
//        printf("\nEncontrado!!!");
    //eliminarNodoA(&ar,&numBuscado,sizeof(int),compararElem);
//    if(buscarEnArbol(&ar,&numBuscado,sizeof(int),compararElem))
//        printf("\nEncontrado!!!");


    //eliminarRama(&ar);
    //buscarYEliminarRama(&ar,&numBuscado,sizeof(int),compararElem);
    //buscarYEliminarNodoA(&ar,&numBuscado,sizeof(int),compararElem);


//    if(buscarEnArbol(&ar,&numBuscado,sizeof(int),compararElem))
//        printf("\nEncontrado!!!");
//
//
//    numBuscado = 3;
//    if(buscarEnArbol(&ar,&numBuscado,sizeof(int),compararElem))
//        printf("\nEncontrado!!!");


//    num = 1;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);
//    num = 0;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);
//    num = 10;
//    insertarNodoAIterativa(&ar,&num,sizeof(int),compararElem);

    //1357910111315
    int numEntrada[] = {8,4,14,2,6,17,17,3,5,7,11,10,12,20,16,1};
    int ce = sizeof(numEntrada)/sizeof(numEntrada[0]);

    for(int i=0;i<ce;i++)
        insertarNodoAIterativa(&ar,&numEntrada[i],sizeof(int),compararElem);


    printf("\n=============RECORRIDO DEL ARBOL EN PREORDEN:=============\n");
    recorrerArbolPre(&ar);
    printf("\n=============RECORRIDO DEL ARBOL EN INORDEN:=============\n");
    recorrerArbolOrden(&ar);
    printf("\n=============RECORRIDO DEL ARBOL EN POSORDEN:=============\n");
    recorrerArbolPos(&ar);

    int cantNodos = contarNodos(&ar);
    printf("\ncantidad de nodos: %d",cantNodos);

    int cantNiveles = contarNiveles(&ar);
    printf("\ncantidad de niveles: %d",cantNiveles);


    printf("\n=============REPRESENTACIÓN GRÁFICA DEL ARBOL=============\n");
    graficarARbol(&ar);
    printf("\ncompleto: %d",esArbolCompleto(&ar));
    printf("\nbalanceado: %d",esArbolBalanceado(&ar));
    printf("\narbol AVL: %d",esArbolAVL(&ar));

    printf("\nNodos hasta el nivel %d: %d ",5,contarNodosXNivel(&ar,5));


    printf("\n=============CARGA DE ARCHIVO EN ARBOL=============\n");
    Arbol ar2;
    crearArbol(&ar2);
    FILE *pf = fopen(argv[ARC_EMP],"rb");
    cargarArchivoEnArbol(&ar2,pf,leer,sizeof(Empleado));
    graficarARbolIndice(&ar2,imprimirIndice);

    return 0;
}
