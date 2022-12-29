#include "StockItemOferta.h"

#include <string>

using namespace std;

//StockItemOferta::StockItemOferta(int paramID,
//                                 char* paramNombre,
//                                 float paramPrecio,
//                                 int paramNArticulos,
//                                 Fecha paramDesde,
//                                 Fecha paramHasta,
//                                 float paramDescuento) :
//    StockItem(paramID,paramNombre,paramPrecio,
//              paramNArticulos),
//              desde(paramDesde),
//              hasta(paramHasta),
//              descuento(paramDescuento)
//{}


StockItemOferta::StockItemOferta(int paramID,
                                 char* paramNombre,
                                 float paramPrecio,
                                 int paramNArticulos,
                                 Fecha paramDesde,
                                 Fecha paramHasta,
                                 float paramDescuento): StockItem(paramID,paramNombre,paramPrecio,paramNArticulos)
{
    this->desde=paramDesde;
    this->hasta=paramHasta;
    this->descuento=paramDescuento;
}


void StockItemOferta::operator ++(int)
{
    this->incrementNArticulos();
}


// StockItemOferta& StockItemOferta::precioDescuento()
// {
//    return *this;
//
//
// }

void StockItemOferta::mostrar()
{
    cout << (this->getId()) << ", "
         << (!this->getNombre()? "NULL" : this->getNombre()) << ", "
         << (this->getPrecio()) << ", "
         << (this->getNArticulos()) << ", "
         << "precio con desc: " << this->getPrecio()*this->descuento << ", "
         << "desde: " << this->desde << ", "
         << "hasta: " << this->hasta << endl;

}

Cadena StockItemOferta::precioDescuento()
{

    char fechaDesde[20];
    char fechaHasta[20];
    char descuento[20];
    char id[15];
    char nARticulos[18];
    char precio[20];
    char nombre[30];

    sprintf(fechaDesde,"desde: %2d/%2d/%2d ",this->desde.getDia(),this->desde.getMes(),this->desde.getAnio());
    sprintf(fechaHasta,"hasta: %2d/%2d/%2d ",this->hasta.getDia(),this->hasta.getMes(),this->hasta.getAnio());
    sprintf(descuento,"desc: %.2f ",this->descuento);
    sprintf(id,"id:%d ",this->getId());
    sprintf(precio,"precio: %.2f ",this->getPrecio());
    sprintf(nombre,"nombre: %s ",this->getNombre());
    sprintf(nARticulos,"cant: %d ",this->getNArticulos());


    char response[150];
//    printf("\n%s",fechaDesde);
//    printf("\n%s",fechaHasta);
//    printf("\n%s",descuento);
//    printf("\n%s",id);
//    printf("\n%s",precio);
//    printf("\n%s",nombre);
//    printf("\n%s",nARticulos);

    strcpy(response,fechaDesde);
    strcat(response,fechaHasta);
    strcat(response,descuento);
    strcat(response,id);
    strcat(response,nombre);
    strcat(response,precio);
    strcat(response,nARticulos);

    Cadena res(response);

    return res;
}




ostream& operator <<(ostream& os, StockItemOferta& st)
{

    os << (StockItem&) st << " precio con desc:  "
        << st.descuento * st.getPrecio() << "  Desde:"
        << st.desde << "  Hasta:"
        << st.desde << endl;

    return os;
}
