#include <iostream>
#include "../ClaseCadenaPersona1/Cadena.h"

using namespace std;

int main()
{
Cadena c1("una cadena");
Cadena c2(c1);
Cadena c3;
Cadena c4;
//c2 = "otro ejemplo de cadena";
c4 = "otra cadena de varios caracteres";
cout << "Longitud de c1 = " << c1.longitud() << c1.palabra << endl;
cout << "Longitud de c2 = " << c2.longitud()  << c2.palabra << endl;
cout << "Longitud de c3 = " << c3.longitud()  << c3.palabra << endl;
cout << "Longitud de c4 = " << c4.longitud()  << c4.palabra << endl;
return 0;
}
