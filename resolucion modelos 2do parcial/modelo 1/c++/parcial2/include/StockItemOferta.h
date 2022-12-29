#ifndef STOCKITEMOFERTA_H
#define STOCKITEMOFERTA_H

#include <iostream>
#include <StockItem.h>
#include <Fecha.h>
#include <Cadena.h>


class StockItemOferta : public StockItem
{
    private:
        Fecha desde;
        Fecha hasta;
        float descuento;
    public:
        StockItemOferta(int paramID,
                 char* paramNombre,
                 float paramPrecio,
                 int paramNArticulos,
                 Fecha paramDesde,
                 Fecha paramHasta,
                 float paramDescuento);
        void operator++(int);
        void mostrar();
        //StockItemOferta& precioDescuento();
        Cadena precioDescuento();



        friend ostream& operator <<(ostream& os, StockItemOferta& st);


};

#endif // STOCKITEMOFERTA_H
