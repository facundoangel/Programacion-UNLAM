#ifndef SOLUCION2DOPARCIALCENTROTELE
#define SOLUCION2DOPARCIALCENTROTELE

#include "../Fecha/Fecha.h"


typedef struct
{
	int nroCliente;
	char nombre[201];
}
Cliente;



typedef struct
{
	int nroCliente;
	int nroReg;
}
IndCli;


typedef struct
{
	int nroCliente;
	char nroFactura[14];
	Fecha fechaVencimiento;
	Fecha fechaPago;
	double importe;
}
Pago;


typedef struct
{
	int nroCliente;
	int cantFactImpagasFueraTerm;
}
FacturasImpagasFueraTerm;




#endif // SOLUCION2DOPARCIALCENTROTELE
