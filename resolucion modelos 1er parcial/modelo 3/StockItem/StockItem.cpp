#include <iostream>
#include "StockItem.h"
#include <queue>


using namespace std;

StockItem::StockItem()
{
    this->Id=0;
    this->nArticulos=0;
    this->precio=0;
    this->nombre = NULL;


}

StockItem::StockItem(int id, char* nombre, float precio, int cantArticulos)
{
    this->Id=id;
    this->nArticulos=cantArticulos;
    this->precio=precio;

    this->nombre=new char[strlen(nombre)+1];
    strcpy(this->nombre,nombre);

}



StockItem::~StockItem()
{
    delete [] this->nombre;
}

StockItem& StockItem::operator ++(int)
{
    this->nArticulos++;

    return *this;
}


void StockItem::mostrar() const
{
    cout << "id: " << this->Id << ", "
         << "nombre: " <<  ((this->nombre==NULL) ? "NULL" : this->nombre) << ", "
         << "precio: " <<  this->precio << ", "
         << "nArticulos: " <<  this->nArticulos << endl;
}



ostream& operator << (ostream& os, StockItem& sk)
{

    os << "id: " << sk.Id << ", "
         << "nombre: " <<  ((sk.nombre==NULL) ? "NULL" : sk.nombre) << ", "
         << "precio: " <<  sk.precio << ", "
         << "nArticulos: " <<  sk.nArticulos;

    return os;
}


istream& operator >> (istream& is, StockItem& sk)
{
    char c;
    queue<char> colaC;

    cout << "Ingrese el id: " << endl;
    cin >> sk.Id;
    fflush(stdin);


    //CAMBIO EL NOMBRE
    cout << "Ingrese el nombre: " << endl;
    while((c = is.get()) != '\n' && c != EOF)
    {
        colaC.push(c);
    }

    sk.nombre = new char[colaC.size()+1];


    int cont=0;
    while(!colaC.empty())
    {
        c=colaC.front();
        sk.nombre[cont]=c;
        cont++;
        colaC.pop();
    }

    cout << "Ingrese el precio: " << endl;
    cin >> sk.precio;

    cout << "Ingrese el stock: " << endl;
    cin >> sk.nArticulos;

    return is;
}
