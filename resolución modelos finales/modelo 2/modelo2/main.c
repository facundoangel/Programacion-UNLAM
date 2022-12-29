#include <stdio.h>
#include <string.h>
#include "TDALista.h"

#define TAM_LINEA 100

// Define la estructura Pedido
typedef struct
{
  int nroPedido;
  char codPro[11];
  int cantPedida;
  char codSector;
  char oficina[21];
} Pedido;

int cmpPedidosXProd(const void *e1, const void *e2)
{
  Pedido *ped1 = (Pedido *)e1;
  Pedido *ped2 = (Pedido *)e2;

  return strcmp(ped1->codPro, ped2->codPro);
}

int cmpPedidosXSector(const void *e1, const void *e2)
{
  Pedido *ped1 = (Pedido *)e1;
  Pedido *ped2 = (Pedido *)e2;

  int resultado = ped1->codSector-ped2->codSector;

  if(resultado!=0)
    return resultado;

  return strcmp(ped1->codPro,ped2->codPro);
}

void actualizarProducto(void* elem, const void* actualizador)
{
    Pedido *ped = (Pedido *)elem;
    Pedido *pedActualizador = (Pedido *)actualizador;

    ped->cantPedida+=pedActualizador->cantPedida;

}


void leerLinea(char* linea,Pedido* ped)
{
    char* c = strrchr(linea,'\n');

    if(!c)
    {
        c = strrchr(linea,'\0');
        if(!c)
            return;
    }

    *c='\0';

    c = strrchr(linea,'|');
    strcpy(ped->oficina,c+1);
    *c='\0';

    c = strrchr(linea,'|');
    sscanf(c+1,"%c",&ped->codSector);
    *c='\0';

    c = strrchr(linea,'|');
    sscanf(c+1,"%d",&ped->cantPedida);
    *c='\0';

    c = strrchr(linea,'|');
    strcpy(ped->codPro,c+1);
    *c='\0';

    sscanf(linea,"%d",&ped->nroPedido);
}


void generarArchivo()
{
    // Crea un array de 20 elementos de tipo Pedido
  Pedido pedidos[] = {
      {1, "YERBA", 10, 'A', "Oficina 1"},
      {2, "CAFE", 20, 'B', "Oficina 2"},
      {3, "CAFE", 30, 'C', "Oficina 3"},
      {4, "ARROZ", 40, 'B', "Oficina 2"},
      {5, "CAFE", 50, 'B', "Oficina 2"},
      {6, "ACEITE", 60, 'A', "Oficina 1"},
      {7, "ARROZ", 70, 'A', "Oficina 1"}};
  int ce = sizeof(pedidos) / sizeof(pedidos[0]);

  FILE *pf = fopen("Pedidos.txt", "w");

  for (int i = 0; i < ce; i++)
  {
    fprintf(pf, "%d|%s|%d|%c|%s\n", pedidos[i].nroPedido, pedidos[i].codPro, pedidos[i].cantPedida, pedidos[i].codSector, pedidos[i].oficina);
  }

  fclose(pf);
}

int main()
{


    generarArchivo();


  //LEO EL ARCHIVO DE PEDIDOS=========================================================


  Lista listProductos, listSectores;
  crearLista(&listProductos);
  crearLista(&listSectores);

  Pedido ped;


  FILE* pfPed = fopen("Pedidos.txt","r");
  char linea[TAM_LINEA];

  while(fgets(linea,TAM_LINEA,pfPed))
  {
    leerLinea(linea,&ped);
    //printf("\nProducto:%s   nro ped:%d",ped.codPro,ped.nroPedido);
    insertarOrdSDup(&listProductos,&ped,sizeof(Pedido),cmpPedidosXProd,actualizarProducto);
    insertarOrdSDup(&listSectores,&ped,sizeof(Pedido),cmpPedidosXSector,actualizarProducto);
  }

    fclose(pfPed);


    //MUESTRO LISTAS POR PANTALLA====================================================================


//    printf("\n=====================LISTA PRODUCTOS=====================");
//    while(!listaVacia(&listProductos))
//    {
//        eliminarPrimero(&listProductos,&ped,sizeof(Pedido));
//        printf("\nProducto:%s   cant:%d",ped.codPro,ped.cantPedida);
//    }
//    printf("\n=====================LISTA PRODUCTOS=====================");
//    while(!listaVacia(&listSectores))
//    {
//        eliminarPrimero(&listSectores,&ped,sizeof(Pedido));
//        printf("\nProducto:%s   sector:%s cant:%d",ped.codPro,ped.oficina,ped.cantPedida);
//    }





    //GENERO ARCHIVO BINARIO CON RESULTADO DE LA FUNCION "eliminarUltimosNdeLaLista" SOBRE LA LISTA DE COMPRAS

    FILE *pfResultado = fopen("resultadoCompras.bin","wb");
    eliminarUltimosNdeLaLista(&listProductos,2);
    while(!listaVacia(&listProductos))
    {
        eliminarPrimero(&listProductos,&ped,sizeof(Pedido));
        fwrite(&ped,sizeof(Pedido),1,pfResultado);
        printf("\nProducto:%s   cant:%d",ped.codPro,ped.cantPedida);
    }

    fclose(pfResultado);

    return 0;
}
