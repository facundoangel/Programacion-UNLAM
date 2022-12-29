#include "enunciados.h"
#define TAM_LINEA 100

void crearArchivos()
{
    FILE *pfProd, *pfPed;

    pfProd = fopen("prodEnStock.bin", "wb");
    pfPed = fopen("pedidos.txt", "w");

    // escribe un vector de productos
    Producto productos[] = {
        {"gas-000001", "coca cola", 100.9, 200},
        {"lim-000002", "ayudin", 180, 200},
        {"hig-000003", "cepillo dientes", 214.19, 80},
        {"com-000004", "galletitas", 300.99, 400},
        {"com-000005", "chocolate", 200.99, 300},
        {"com-000006", "chicles", 100.99, 500},
        {"com-000007", "jamon", 400.99, 300},
        {"com-000008", "mantecol", 100.99, 500},
        {"ele-000009", "television", 2000.99, 300},
    };
    // escribe un vector de productos con codigos repetidos de clientes y de
    Pedidos Pedidos[] = {
        {"01/01/2017", 12, "gas-000001", 2000},
        {"01/01/2022", 1, "lim-000002", 201},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"01/01/2019", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
        {"11/10/2022", 12, "gas-000001", 20},
        {"01/01/2022", 1, "lim-000002", 200},
        {"20/01/2019", 40, "hig-000003", 50},
    };

    fwrite(productos, sizeof(Producto), sizeof(productos) / sizeof(Producto), pfProd);

    int cantPedidos = sizeof(Pedidos) / sizeof(Pedidos[0]);
    for (int i = 0; i < cantPedidos; i++)
    {
        fprintf(pfPed, "%s;%d;%s;%d\n", Pedidos[i].fecha, Pedidos[i].codCliente, Pedidos[i].codProd, Pedidos[i].cantPedida);
    }

    fclose(pfProd);
    fclose(pfPed);
}

void crearCola(Cola *pl)
{
    pl->pri = NULL;
    pl->ult = NULL;
}

bool encolar(Cola *pl, Pedidos pedFaltante, size_t tamElem)
{
    Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
    nue->info = malloc(tamElem);
    nue->tamElem = tamElem;
    memcpy(nue->info, &pedFaltante, tamElem);

    if (!pl->pri && !pl->ult)
    {

        nue->sig = NULL;
        pl->pri = nue;
        pl->ult = nue;
        return true;
    }

    pl->ult->sig = nue;
    pl->ult = nue;

    return true;
}

bool colaVacia(Cola *pl)
{
    return pl->pri == NULL && pl->ult == NULL;
}

bool desencolar(Cola *pl, Pedidos *pedFaltante)
{
    if(pl->pri==NULL || pl->ult==NULL)
    {
        printf("\nERROR: Cola Vacia");
        return false;
    }

    Nodo *nae = pl->pri;
    memcpy(pedFaltante, nae->info, sizeof(Pedidos));

    if (pl->pri == pl->ult)
    {
        pl->pri = NULL;
        pl->ult = NULL;
    }
    else
    {
        pl->pri = pl->pri->sig;
    }
    free(nae->info);
    free(nae);

    return true;
}

void leerLinea(char* linea,Pedidos* ped)
{
    char *c;

    c = strchr(linea,'\n');
    *c = '\0';

    c = strrchr(linea,';');
    sscanf(c+1,"%d",&ped->cantPedida);
    *c='\0';

    c-=10;
    strcpy(ped->codProd,c);
    c--;
    *c='\0';

    c=strrchr(linea,';');
    sscanf(c+1,"%d",&ped->codCliente);
    *c='\0';

    strcpy(ped->fecha,linea);



}

bool cargarPedidos(Cola *pend)
{
    FILE *pf = fopen("prodEnStock.bin", "r+b");
    FILE *pfPed = fopen("pedidos.txt", "r");
    if (pf == NULL)
    {
        return false;
    }

    Producto prod;
    Pedidos ped, pedFaltantes = {"", 0, "", 0};
    char linea[TAM_LINEA];

    fread(&prod, sizeof(Producto), 1, pf);

    while (!feof(pf))
    {

        while (fgets(linea, TAM_LINEA, pfPed))
        {

            leerLinea(linea,&ped);

            printf("\ncomparando: %s y %s",prod.codProd,ped.codProd);
            if (strcmp(ped.codProd, prod.codProd) == 0)
            {
            printf("\nProducto igual");
                if (prod.stock < ped.cantPedida)
                {

                    pedFaltantes.cantPedida += ped.cantPedida - prod.stock;
                    prod.stock = 0;
                    pedFaltantes.codCliente = ped.codCliente;
                    strcpy(pedFaltantes.codProd, ped.codProd);
                    strcpy(pedFaltantes.fecha, ped.fecha);
                }
                else
                {
                    prod.stock -= ped.cantPedida;
                }
                fseek(pf,(int) -sizeof(Producto), SEEK_CUR);
                fwrite(&prod, sizeof(Producto), 1, pf);
                fseek(pf,0,SEEK_CUR);
                printf("\nStock nuevo para %s -> %d",prod.codProd,prod.stock);
            }
        }

        if (pedFaltantes.cantPedida != 0)
        {
            encolar(pend, pedFaltantes, sizeof(pedFaltantes));
        }
        fread(&prod, sizeof(Producto), 1, pf);
        fseek(pfPed,0,SEEK_SET);
        pedFaltantes.cantPedida = 0;
    }

    fclose(pf);

    return true;
}

bool generarArchivoFaltantes(Cola *pend)
{
    FILE *pf = fopen("faltantes.txt", "w");
    char linea[TAM_LINEA];
    Pedidos ped;

    while (!colaVacia(pend))
    {
        desencolar(pend, &ped);
        fprintf(pf, "%s-%d-%s-%d\n", ped.fecha, ped.codCliente, ped.codProd, ped.cantPedida);
    }

    fclose(pf);

    return true;
}


void cargarFaltantes(Cola* pc)
{
    FILE *pf = fopen("faltantes.txt","w");
    Pedidos ped;
    printf("\n=============CREACION DE ARCHIVO DE FALTANTES===============");
    while(!colaVacia(pc))
    {
        desencolar(pc,&ped);
        printf("\nfaltante de: %s por %d unidades",ped.codProd,ped.cantPedida);
        fprintf(pf,"%s - %d - %s - %d\n",ped.fecha,ped.codCliente,ped.codProd,ped.cantPedida);

    }

    fclose(pf);

}
