#include <iostream>
#include "../StockItem/StockItem.h"

using namespace std;

int main()
{
    StockItem s1;
    s1.mostrar(); // va a mostrar el id = 0 , nombre = NULL, precio =0.0 y nArticulos = 0;
    cout << s1 << endl;
    StockItem s2(1231,"Lavarropas",5676,30);
    cout<<s2<<endl;
    char nom[500]="Aspiradora";
    StockItem s3(1256,nom, 12315,10);
    s3++; // suma 1 a la cantidad del stock
    s3.mostrar();
    cout<<endl<<"Electrodomestico 3"<<endl;
    s3.mostrar();
    cin>>s1;
    cout<<s1;
    return 0;
}
