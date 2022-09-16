#include "header.h"


using namespace std;

int main()
{
    system("chcp 1252 >nul");


    Fecha f(12,2,2019);
    //f.sumarFecha(254);
    //f.obtenerFechaNormal();
    f.mostrarFechaNormal();
    //cin >> f;
    bool result = (f == "12/2/2019");
    cout <<"resultado: " << result << endl;

    return 0;
}
