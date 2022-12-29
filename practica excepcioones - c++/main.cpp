#include <iostream>
#include "Numero.h"

using namespace std;



int main()
{
    Numero num1(4);
    Numero num2(2);


    try{
        cout << num1-100 << endl;
    } catch(ErrorPersonalizado& e)
    {
        cout << e.getMessage() << endl;
    }

    return 0;
}
