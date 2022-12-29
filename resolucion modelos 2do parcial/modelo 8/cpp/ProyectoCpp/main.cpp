#include <iostream>
#include "Class.h"
using namespace std;

int main()
{
    float av1[]= {0.0, 1.0, 2.0, 3.0};
    float av2[]= {4.0, 5.0, 6.0, 7.0};
    float av3[]= {1.0, 2.0};

    FVector fv1(av1, sizeof(av1)/sizeof(float));
    FVector fv2(av2, sizeof(av2)/sizeof(float));
    FVector fv3(av3, sizeof(av3)/sizeof(float));

    if(fv2 == (fv1 += 4.0))
        {
        cout <<"Los vectores fv1 y fv2 son iguales"<<endl;
        cout <<fv1<<" = " <<fv2<<endl;
        }

    cout<<fv2-- <<endl;
    if(fv2 == fv1)
    {

    }else{
           cout <<"Los vectores fv1 y fv2 ahora son distintos"<<endl;
           cout <<fv1<<" != " <<fv2 <<endl;
    }

    try{
    cout<< fv1/fv3 <<endl;
    }catch(MiException& ex)
    {
     cout<<ex.getMensaje()<<endl;
    }
    cout << "Division de vectores fv1 y fv2: "<< fv1/fv2 <<endl;
    return 0;
}
