#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <iostream>
#include <string.h>
#include "StockAbstract.h"


using namespace std;

class StockItem : public StockAbstract
{
    private:
        int Id;
        char* nombre;
        float precio;
        int nArticulos;



    public:

        int getId(){return this->Id;}
        char* getNombre(){return this->nombre;}
        float getPrecio(){return this->precio;}
        int getNArticulos(){return this->nArticulos;}
        void incrementNArticulos(){this->nArticulos+=1;}

        StockItem();
        StockItem(int parId, const char* parNombre, float parPrecio, int parNArticulos);
        ~StockItem();
        void mostrar();


   friend ostream& operator<<(ostream& os, StockItem& stk);
   friend istream& operator>>(istream& os, StockItem& stk);
};

#endif // STOCKITEM_H
