/*
Parte 1 - C

 La fábrica de muebles Cerejeira necesita procesar las transferencias de mercaderías entre sus depósitos.  Dispone del archivo de texto de longitud variable Transferencias.txt, cuya estructura es:
 { dep_origen: entero, cod_prod: cadena(15), dep_destino: entero, cod_prod: cadena(15), cantidad: double }. Este archivo representa las transferencias de mercadería entre sus depósitos. No está ordenado.
 El archivo a actualizar se denomina Depositos.dat, es binario y su estructura es:
 { nro_dep: entero, cod_prod: cadena(15), stock: entero } No está ordenado.


 Se dispone de un archivo de índices denominado Depositos.idx, para acceder en forma directa al archivo de Depósitos. El mismo está ordenado por nro de depósito, y luego por código de producto. Deberá cargar este índice en un árbol, de manera que quede balanceado, y las búsquedas sean eficientes.


 Tenga en cuenta que, por motivos de eficiencia, en el proceso que actualiza los depósitos, se le impuso la restricción de no poder leer los registros del archivo de transacciones más de una vez, y para el de depósitos sólo deberá acceder a los registros que serán actualizados. Este último no puede cargarse en su totalidad en memoria, dado que se espera que su tamaño en el futuro haga inviable cargarlo.
 Para procesar el archivo de transacciones, debe utilizar el TDA lista implementada con lista dinámica doble-mente enlazada.  Debe resolver la función actualizarDepositos_ALU() y todas las que ésta invoque.
 Debe colocar el sufijo _ALU a todas las funciones que desarrolle. Sólo debe modificar y entregar el archivo main.c. No modifique ni entregue otro archivo.  Escriba su apellido, nombres y su DNI en la cabecera del archivo main.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arbol.h"
#include "Lista.h"

#define TAM_MAX 100

typedef struct
{
    int nro_dep;
    char cod_prod[15];
    int stock;
} Deposito;

typedef struct
{
    int nro_dep;
    char cod_prod[15];
    int pos;
} IndDepo;

typedef struct
{
    int dep_origen;
    char cod_prod[15];
    int dep_destino;
    double cantidad;
} Transferencia;

// FUNCIONES AUXILIARES
int cmpInd(const void *e1, const void *e2)
{
    IndDepo *ind1 = (IndDepo *)e1;
    IndDepo *ind2 = (IndDepo *)e2;

    int resultado =ind1->nro_dep - ind2->nro_dep;

    if(resultado!=0)
        return resultado;

    return strcmp(ind1->cod_prod,ind2->cod_prod);
}
void imprimirIndice(const void *elem, void *aux)
{
    IndDepo *ind = (IndDepo *)elem;
    printf("%d|%d|%s\n", ind->nro_dep, ind->pos,ind->cod_prod);
}
bool leerLineaTrans(char *linea, Transferencia *tran)
{
    char *c = strrchr(linea, '\n');

    if (!c)
    {
        c = strrchr(linea, '\0');
        if (!c)
            return false;
    }
    else
    {
        *c = '\0';
    }

    c = strrchr(linea, ';');
    sscanf(c + 1, "%lf", &tran->cantidad);
    *c = '\0';

    c = strrchr(linea, ';');
    sscanf(c + 1, "%d", &tran->dep_destino);
    *c = '\0';

    c = strrchr(linea, ';');
    strcpy(tran->cod_prod, c + 1);
    *c = '\0';

    sscanf(linea, "%d", &tran->dep_origen);

    return true;
}
int cmpTrans(const void *e1, const void *e2)
{
    Transferencia *tran1 = (Transferencia *)e1;
    Transferencia *tran2 = (Transferencia *)e2;

    return tran1->dep_origen - tran2->dep_origen;
}

// FUNCIONES
void generarArchivos()
{
    // generar vector de depósitos
    Deposito depositos[] = {
        {110, "CAFE", 1000},
        {110, "MATE", 2000},
        {110, "YERBA", 3000},
        {110, "LECHE", 4000},
        {220, "CAFE", 5000},
        {220, "MATE", 6000},
        {220, "YERBA", 7000},
        {220, "LECHE", 8000},
        {230, "CAFE", 9000},
        {230, "MATE", 1000},
        {230, "LECHE", 6000},
        {240,"LECHE",4000}
        };

    int ceDep = sizeof(depositos) / sizeof(Deposito);

    // generar vector de transferencias
    Transferencia transferencias[10] = {
        {220, "YERBA", 230, 800},
        {230, "MATE", 220, 1200},
        {220, "YERBA", 110, 500},
        {110, "CAFE", 220, 200},
        {240, "LECHE", 230, 1700},
        {220, "LECHE", 240, 1000},
        {110, "MATE", 230, 300},
        {230, "CAFE", 110, 400},
        {220, "CAFE", 110, 600},
        {110, "LECHE", 220, 700}};
    int ceTran = sizeof(transferencias) / sizeof(Transferencia);

    FILE *pfTran = fopen("Transferencias.txt", "w");
    if (pfTran == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < ceTran; i++)
    {
        fprintf(pfTran, "%d;%s;%d;%.0lf\n", transferencias[i].dep_origen, transferencias[i].cod_prod, transferencias[i].dep_destino, transferencias[i].cantidad);
    }

    fclose(pfTran);

    FILE *pfDep = fopen("Depositos.dat", "wb");
    if (pfDep == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < ceDep; i++)
    {
        fwrite(&depositos[i], sizeof(Deposito), 1, pfDep);
    }

    fclose(pfDep);
}
void generarArchivoIndice()
{
    Deposito dep;
    IndDepo ind;
    int cont = 0;

    Lista listOrd;
    crearLista(&listOrd);

    FILE *pfDep = fopen("Depositos.dat", "rb");

    if (pfDep == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fread(&dep, sizeof(Deposito), 1, pfDep);
    while (!feof(pfDep))
    {
        ind.nro_dep = dep.nro_dep;
        ind.pos = cont;
        strcpy(ind.cod_prod,dep.cod_prod);
        insertarEnListaOrdCDup(&listOrd,&ind,sizeof(IndDepo),cmpInd);
        cont++;
        fread(&dep, sizeof(Deposito), 1, pfDep);
    }

    fclose(pfDep);
    FILE *pfInd = fopen("Depositos.idx", "wb");
    printf("\n========INDICES DE DEPOSITO=========\n");
    while(eliminarPrimero(&listOrd,&ind,sizeof(IndDepo)))
    {
        printf("%d|%d|%s\n", ind.nro_dep, ind.pos,ind.cod_prod);
        fwrite(&ind, sizeof(IndDepo), 1, pfInd);
    }
    fclose(pfInd);
}

bool cargarIndicesEnArbolRec(Arbol *pa, FILE *pf, size_t tamElem, int li, int ls)
{
    if (li > ls)
        return true;

    int m = (li + ls) / 2;

    void *elem = malloc(tamElem);
    fseek(pf, m * tamElem, SEEK_SET);
    fread(elem, tamElem, 1, pf);

    NodoA *nue = crearNodoA(elem, tamElem);
    if (!nue)
        return false;

    *pa = nue;
    free(elem);

    if (!cargarIndicesEnArbolRec(&(*pa)->hDer, pf, tamElem, m + 1, ls))
        return false;

    return cargarIndicesEnArbolRec(&(*pa)->hIzq, pf, tamElem, li, m - 1);
}

bool cargarIndicesEnArbol(Arbol *pa, const char *nomArc, size_t tamElem)
{
    FILE *pf = fopen(nomArc, "rb");
    fseek(pf, 0L, SEEK_END);

    if (!pf)
        return false;

    int cantReg = ftell(pf) / tamElem;

    cargarIndicesEnArbolRec(pa, pf, tamElem, 0, cantReg - 1);

    fclose(pf);

    return true;
}



int main()
{
    generarArchivos();
    generarArchivoIndice();

    // CREAR ARBOL Y CARGARLO CON LOS INDICES DE LOS DEPOSITOS
    Arbol ar;
    crearArbol(&ar);
    cargarIndicesEnArbol(&ar, "Depositos.idx", sizeof(IndDepo));
    printf("\n============ARBOL DE INDICES==============\n");
    graficarArbol(&ar, imprimirIndice);

    // CREAR LISTA ENLAZADA DOBLEMENTE Y CARGARLA CON LAS TRANSFERENCIAS
    Lista listTrans;
    crearLista(&listTrans);
    char linea[TAM_MAX];
    Transferencia tran;
    Deposito dep;
    IndDepo indDep;

    FILE *pfTrans = fopen("Transferencias.txt", "r");
    while (fgets(linea, TAM_MAX, pfTrans))
    {
        leerLineaTrans(linea, &tran);
        insertarEnListaOrdCDup(&listTrans, &tran, sizeof(Transferencia), cmpTrans);
    }
    fclose(pfTrans);




    // LEO LA LISTA DE TRANSFERENCIAS Y ACTUALIZO LOS ESTADOS DE LOS DESPOSITOS
    FILE *pfDep = fopen("Depositos.dat","r+b");
    while (eliminarPrimero(&listTrans, &tran, sizeof(Transferencia)))
    {
        //LE RESTO MERCADERIA AL DEPOSITO DE ORIGEN
        indDep.nro_dep=tran.dep_origen;
        strcpy(indDep.cod_prod,tran.cod_prod);
        buscarEnArbol(&ar,&indDep,sizeof(IndDepo),cmpInd);
        fseek(pfDep,indDep.pos*sizeof(Deposito),SEEK_SET);
        fread(&dep,sizeof(Deposito),1,pfDep);
        dep.stock-=(int)tran.cantidad;
        fseek(pfDep,(long int)-sizeof(Deposito),SEEK_CUR);
        fwrite(&dep,sizeof(Deposito),1,pfDep);



        //LE RESTO MERCADERIA AL DEPOSITO DE DESTINO
        indDep.nro_dep=tran.dep_destino;
        buscarEnArbol(&ar,&indDep,sizeof(IndDepo),cmpInd);
        fseek(pfDep,indDep.pos*sizeof(Deposito),SEEK_SET);
        fread(&dep,sizeof(Deposito),1,pfDep);
        dep.stock+=(int)tran.cantidad;
        fseek(pfDep,(long int)-sizeof(Deposito),SEEK_CUR);
        fwrite(&dep,sizeof(Deposito),1,pfDep);
    }


    //MUESTRO ARCHIVOS DE DESPOSITO ACTUALIZADO
    printf("\n=========================DEPOSITO ACTUALIZADO=======================");
    fseek(pfDep,0L,SEEK_SET);
    fread(&dep,sizeof(Deposito),1,pfDep);
    while(!feof(pfDep))
    {
        printf("\n%d    %s    %d",dep.nro_dep,dep.cod_prod,dep.stock);
        fread(&dep,sizeof(Deposito),1,pfDep);
    }
    fclose(pfDep);

    return 0;
}
