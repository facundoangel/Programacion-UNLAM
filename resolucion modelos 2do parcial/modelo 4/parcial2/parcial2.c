#include "parcial2.h"

void crearArchivos()
{
    FILE *pf = fopen("productos.dat", "wb");

    Producto productos[] = {
        {"COCA", "gaseosa", 320.50, 200},
        {"FANTA", "gaseosa", 320.50, 200},
        {"SPR", "gaseosa", 320.50, 200},
        {"PEP", "gaseosa", 320.50, 200},
        {"MAN", "fruta", 320.50, 200},
        {"PERA", "fruta", 214.15, 599},
        {"ANANA", "frura", 311, 600},
        {"NARANJA", "fruta", 320.50, 200},
        {"LIMON", "fruta", 320.50, 200},
        {"PAPAYA", "fruta", 320.50, 200},
        {"MELON", "fruta", 320.50, 200},
        {"DURAZNO", "fruta", 320.50, 200},
        {"POMELA", "fruta", 320.50, 200},
        {"MANDARINA", "fruta", 320.50, 200},
        {"CEREZA", "fruta", 320.50, 200},
        {"UVA", "fruta", 320.50, 200},
        {"KIWI", "fruta", 320.50, 200},
        {"FRUTILLA", "fruta", 320.50, 200},
        {"MANGO", "fruta", 320.50, 200},
        {"PINA", "fruta", 320.50, 200},
        {"BANANA", "fruta", 320.50, 200},
        {"CIRUELA", "fruta", 320.50, 200},
        {"COCO", "fruta", 320.50, 200},
        {"PAPAYA", "fruta", 320.50, 200},
        {"MELON", "fruta", 320.50, 200},
        {"DURAZNO", "fruta", 320.50, 200},
        {"POMELA", "fruta", 320.50, 200},
        {"MANDARINA", "fruta", 320.50, 200},
        {"CEREZA", "fruta", 320.50, 200},
        {"UVA", "fruta", 320.50, 200},
        {"KIWI", "fruta", 320.50, 200},
        {"FRUTILLA", "fruta", 320.50, 200},
        {"MANGO", "fruta", 320.50, 200},
        {"PINA", "fruta", 320.50, 200},
        {"BANANA", "fruta", 320.10, 450}};

    int ce = sizeof(productos) / sizeof(Producto);

    fwrite(productos, sizeof(Producto), ce, pf);

    fclose(pf);

    FILE *pfPed = fopen("pedidos.txt", "w");

    Pedido pedidos[] = {
        {{1, 1, 2019}, 1, "COCA", 10},
        {{1, 2, 2019}, 101, "FANTA", 10},
        {{11, 8, 2022}, 72, "SPRITE", 10},
        {{5, 11, 2019}, 80, "COCA", 10},
        {{5, 11, 2020}, 99, "FANTA", 10},
        {{5, 12, 2019}, 12, "SPRITE", 10},
        {{2, 12, 2022}, 55, "MOTOROLA", 30},
        {{2, 12, 2022}, 12, "MANDARINA", 30},
        {{2, 12, 2022}, 99, "MANDARINA", 30},
        {{2, 12, 2022}, 55, "MANDARINA", 30},
        {{2, 12, 2022}, 55, "MANDARINA", 30},
        {{2, 12, 2022}, 55, "HAMBUR", 30},
        {{2, 12, 2022}, 55, "UVA", 40},
        {{2, 12, 2022}, 55, "UVA", 30},
        {{2, 12, 2022}, 200, "UVA", 100},
        {{2, 12, 2022}, 55, "UVA", 30},
        {{2, 12, 2022}, 70, "UVA", 30},
        {{2, 12, 2022}, 55, "KIWI", 30},
        {{2, 12, 2022}, 55, "KIWI", 30},
        {{2, 12, 2022}, 12, "ANANA", 30},
        {{2, 12, 2022}, 200, "ANANA", 30},
        {{2, 12, 2022}, 55, "ANANA", 30},
        {{2, 12, 2022}, 55, "ANANA", 30},

    };

    int cePed = sizeof(pedidos) / sizeof(pedidos[0]);

    for (int i = 0; i < cePed; i++)
    {
        fprintf(pfPed, "%d/%d/%d;%d;%s;%d\n", pedidos[i].fecha.d, pedidos[i].fecha.m, pedidos[i].fecha.a, pedidos[i].codClie, pedidos[i].codProd, pedidos[i].cantPedida);
    }

    fclose(pfPed);
}

int comparar(void *a, void *b)
{
    Indice *ind1 = (Indice *)a;
    Indice *ind2 = (Indice *)b;

    return strcmp(ind1->codProd, ind2->codProd);
}

void leerRegistro(Arbol *pa, char *nombreArch, FILE *pf, Cmp cmp, size_t tamElem, int m)
{

    Indice ind;
    Producto prod;

    fseek(pf, m * sizeof(Producto), SEEK_SET);
    fread(&prod, sizeof(Producto), 1, pf);
    strcpy(ind.codProd, prod.codProd);
    ind.indice = m;

    printf("\ncodigo:%s indice:%s", prod.codProd, prod.descripcion);

    insertarNodoA(pa, &ind, tamElem, cmp);
}

void imprimirIndice(void *elem)
{
    NodoA *nodo = (NodoA *)elem;
    Indice *ind = nodo->elem;

    printf("%s | %d", ind->codProd, ind->indice);
}

void ordenarYSacarDuplicadosProductos()
{


    FILE *pf = fopen("productos.dat", "rb");
    Producto prod;

    fread(&prod, sizeof(Producto), 1, pf);
    printf("\nCODIGO\tDESC\tPRECIO\tSTOCK");

    while (!feof(pf))
    {
        printf("\n%s\t%s\t%.2f\t%d", prod.codProd, prod.descripcion, prod.pu, prod.stock);
        fread(&prod, sizeof(Producto), 1, pf);
    }

    fclose(pf);

}


void mostrarArchProductos()
{
    FILE *pf = fopen("productos.dat", "rb");
    Producto prod;

    fread(&prod, sizeof(Producto), 1, pf);
    printf("\nCODIGO\tDESC\tPRECIO\tSTOCK");

    while (!feof(pf))
    {
        printf("\n%s\t%s\t%.2f\t%d", prod.codProd, prod.descripcion, prod.pu, prod.stock);
        fread(&prod, sizeof(Producto), 1, pf);
    }

    fclose(pf);
}
