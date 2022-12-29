#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Comun/Comun.h"
#include "../Nodo/Nodo.h"
#include "../TDALista/TDALista.h"
#include "../Fecha/Fecha.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES	1
#define ARG_MEDICIONES	2
#define ARG_FACTURAS	3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10
#define TAM_MAX 100

int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar);
int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar);
void cargarMediciones(const char* nombreArchivoMediciones, Lista* pl);
void mostrarMedicion(void* elem, void* datosAccion);
int cmpMediciones(const void* e1, const void* e2);
void mostrarFactura(Factura fac);

int main(int argc, char* argv[])
{
	int ret = generarArchivos();

	if(ret != TODO_OK)
	{
		printf("Error al generar archivos\n");
		return ret;
	}

	printf("Archivos generados correctamente\n");

	puts("\nAntes de Actualizar:\n");

	mostrarClientes(argv[ARG_CLIENTES]);

	mostrarMediciones(argv[ARG_MEDICIONES]);

	Mes mesesAFacturar[MAX_MESES];

	int cantMesesAFacturar = extraerMesesAFacturar(argv, mesesAFacturar);

	//ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
	/// Descomente esta línea y comente la de arriba, para ejecutar su código
    ret = generarFacturas_ALU(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);

	if(ret != TODO_OK)
	{
		printf("Error al generar facturas\n");
		return ret;
	}

	puts("\nDespues de Actualizar:\n");

	mostrarFacturas(argv[ARG_FACTURAS]);

	mostrarClientes(argv[ARG_CLIENTES]);

	return ret;
}


int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar)
{
    char *fecha;
    Mes mes;
    int cantMeses = atoi(argv[ARG_CANT_MESES_A_FACTURAR]);

    for(int i=0;i<cantMeses;i++)
    {
        fecha = argv[i+6];
        sscanf(fecha,"%2d/%4d",&mes.mes,&mes.anio);
        mesesAFacturar[i]=mes;


    }

	return cantMeses;
}

bool leerLinea(char* linea, Medicion* med)
{
    char *c = strrchr(linea,'\n');
    if(!c)
        return false;
    *c='\0';

    c=strrchr(linea,'|');
    sscanf(c+1,"%d",&med->valorMedidor);
    *c='\0';

    c=strrchr(linea,'/');
    sscanf(c+1,"%d",&med->fechaMedicion.anio);
    *c='\0';

    c=strrchr(linea,'/');
    sscanf(c+1,"%d",&med->fechaMedicion.mes);
    *c='\0';

    c=strrchr(linea,'|');
    sscanf(c+1,"%d",&med->fechaMedicion.dia);
    *c='\0';


    sscanf(linea,"%d",&med->nroCliente);

    return true;
}


int cmpMediciones_ALU(const void* e1, const void* e2)
{
    Medicion* med1 = (Medicion*) e1;
    Medicion* med2 = (Medicion*) e2;

    int resultado = med1->nroCliente-med2->nroCliente;

    if(resultado!=0)
        return resultado;

    return cmpFechas(&med1->fechaMedicion,&med2->fechaMedicion);

}

bool cargarMediciones_ALU(Lista *pl, const char* nombreArch)
{

    FILE* pf = fopen (nombreArch,"r");

    Medicion med;
    char linea[TAM_MAX];

    while(fgets(linea,TAM_MAX,pf))
    {
        leerLinea(linea,&med);
        insertarEnListaOrdCDup(pl,&med,sizeof(Medicion),cmpMediciones_ALU);
    }


    fclose(pf);


    return true;

}

void imprimirMed(void* elem, void* datosAccion)
{
    Medicion* med=(Medicion*) elem;

    printf("\n===============================MEDICIONES=======================");
    printf("\n%d %d/%d/%d %d",med->nroCliente,med->fechaMedicion.dia,med->fechaMedicion.mes,med->fechaMedicion.anio,med->valorMedidor);

}

int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar)
{


    //CARGO MEDICIONES EN LISTA
    Lista listMed, listMedClieActual;
    crearLista(&listMed);
    crearLista(&listMedClieActual);
    cargarMediciones_ALU(&listMed,nombreArchivoMediciones);






    Medicion med;
    Cliente cli;
    int ultMedicion, dm, dd;
    double cm,cde;
    Fecha ultFechaMed;
    Factura fact;
    FILE *pf = fopen(nombreArchivoClientes,"r+b");
    FILE *pfFact = fopen(nombreArchivoFacturas,"wb");
    //RECORRO CADA MEDICION PARA HACER LA FACTURA
    while(!listaVacia(&listMed))
    {

        fread(&cli,sizeof(Cliente),1,pf);

        ultMedicion = cli.valorMedidor;
        ultFechaMed = cli.fechaUltMedicion;

        for(int i =0; i<cantMesesAFacturar;i++)
        {
            eliminarDeListaPrimero(&listMed,&med,sizeof(Medicion));
            insertarEnListaOrdCDup(&listMedClieActual,&med,sizeof(Medicion),cmpMediciones_ALU);
        }



        while(eliminarDeListaPrimero(&listMedClieActual,&med,sizeof(Medicion)))
        {
            dm=med.valorMedidor-ultMedicion;
            dd=difEnDiasEntreFechas(&ultFechaMed,&med.fechaMedicion);

            cde= (double) dm / (double) dd;
            cm = cde * cantDiasMes(med.fechaMedicion.mes,med.fechaMedicion.anio);

            //ESCRIBO LA FACTURA EN ARCHIVO
            fact.consumoMes=cm;
            fact.fechaUltMedicion=ultFechaMed;
            fact.mesFacturado=getMes(&ultFechaMed);
            fact.nroCliente=cli.nroCliente;
            fact.nroFactura=proximoNroFactura++;
            fact.valorMedidor=ultMedicion;

            fwrite(&fact,sizeof(Factura),1,pfFact);


            ultMedicion = med.valorMedidor;
            ultFechaMed = med.fechaMedicion;

        }

        // MODIFICO EL CLIENTE
        cli.fechaUltMedicion=ultFechaMed;
        cli.ultConsumoMes=cm;
        cli.valorMedidor=ultMedicion;
        cli.ultMesFacturado=getMes(&ultFechaMed);

        fseek(pf,(long int)-sizeof(Cliente),SEEK_CUR);
        fwrite(&cli,sizeof(Cliente),1,pf);
        fseek(pf,0L,SEEK_CUR);



    }

    fclose(pf);
    fclose(pfFact);

    return 0;
}

void mostrarMedicion(void* elem, void* datosAccion)
{
    Medicion* medicion = (Medicion*)elem;
    printf("%d|%d/%d/%d|%d\n", medicion->nroCliente, medicion->fechaMedicion.dia, medicion->fechaMedicion.mes, medicion->fechaMedicion.anio, medicion->valorMedidor);
}



void mostrarFactura(Factura fac)
{
    printf("%d|%d|%d|%d|%lf\n", fac.nroFactura, fac.nroCliente, fac.fechaUltMedicion.mes, fac.valorMedidor, fac.consumoMes);
}
