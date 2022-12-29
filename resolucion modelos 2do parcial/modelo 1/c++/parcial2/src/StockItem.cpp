#include "StockItem.h"
#include <queue>


using namespace std;

//StockItem::StockItem()
//{
//    this->Id=0;
//    this->nombre=NULL;
//    this->precio=0;
//    this->nArticulos=0;
//}

StockItem::StockItem() : Id(0),nombre(NULL),precio(0),nArticulos(0){}

StockItem::StockItem(int parId, const char* parNombre, float parPrecio, int parNArticulos)
{
    this->Id=parId;
    this->nombre= new char[strlen(parNombre+1)];
    this->precio=parPrecio;
    this->nArticulos=parNArticulos;

    strcpy(this->nombre,parNombre);
}

StockItem::~StockItem(){
    delete [] this->nombre;
}


void StockItem::mostrar()
{
    cout << this->Id << ", "
         << (!this->nombre? "NULL" : this->nombre) << ", "
         << this->precio << ", "
         << this->nArticulos << endl;
}



ostream& operator << (ostream& os, StockItem& stk)
{
    os << stk.Id << ", "
        << (!stk.nombre? "NULL" : stk.nombre) << ", "
        << stk.precio << ", "
        << stk.nArticulos;

    return os;
}


istream& operator>>(istream& is, StockItem& stk)
{

    cout << "Ingrese id: " << endl;
    is >> stk.Id;

    //AGREGO EL NOMBRE DEL PRODUCTO

    fflush(stdin);


    cout << "Ingrese nombre de producto: ";
    char c;
    int cont=0;
    queue<char> colaC;
    while((c=is.get()) != '\n' && c!=EOF)
    {
        colaC.push(c);

    }


    if(!stk.nombre || (strlen(stk.nombre) != colaC.size()))

    {
        delete [] stk.nombre;
        stk.nombre=new char[colaC.size()+1];
    }

    while(!colaC.empty())
    {
        stk.nombre[cont++]=colaC.front();
        colaC.pop();

    }

    stk.nombre[cont]='\0';



    cout << "Ingrese precio: " << endl;
    is >> stk.precio;


    cout << "Ingrese inventario: " << endl;
    is >> stk.nArticulos;

    return is;
}
