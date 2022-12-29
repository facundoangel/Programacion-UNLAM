#include <iostream>

#include <StockItem.h>
#include <StockAbstract.h>
#include <StockItemOferta.h>


using namespace std;

void mostrarPolimorficos(StockAbstract& st);

int main()
{
    StockItem s1;

    s1.mostrar();
    cout << s1 << endl;

    char nom[500]="Aspiradora";
    Fecha desde(5,10,2022);
    Fecha hasta(15,10,2022);
    StockItemOferta s3(1256,nom, 12315,10, desde,hasta, 0.5);
    s3++; // suma 1 a la cantidad del stock
    //Cadena cad("123");
    cout << s3.precioDescuento()<<endl; // muestra todos los datos del producto, las fechas
//     //durante las cuales está en oferta y el precio con el descuento
     cout<<endl<<"====================Mostrar Electrodomesticos en forma polimorfica======================"<<endl;
     mostrarPolimorficos(s1);
     mostrarPolimorficos(s3);
     //cin>>s1;
     cout<<s1;

    return 0;
}

void mostrarPolimorficos(StockAbstract& st)
{
    st.mostrar();
}



