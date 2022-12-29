#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <string.h>

using namespace std;

class StockItem{

    private:
        int Id;
        char * nombre;
        float precio;
        int nArticulos;


    public:

        StockItem();
        StockItem(int id, char* nombre, float precio, int cantArticulos);
        ~StockItem();

        StockItem& operator ++(int);
        void mostrar() const;


        friend ostream& operator << (ostream& os, StockItem& sk);
        friend istream& operator >> (istream& is, StockItem& sk);


};


#endif // STOCKITEM_H
