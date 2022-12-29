/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
** DNI:                                                       													**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**                      																					   	**
******************************************************************************************************************
** Nota:																									   	**
*****************************************************************************************************************/

#include <iostream>

using namespace std;

class Complejo{
private:
    int entero;
    int decimal;

public:
    Complejo(const int entero, const int decimal);
    Complejo(const Complejo& com);
    Complejo& operator =(const Complejo& com);
    Complejo operator + (const Complejo& com);
    Complejo operator *(const Complejo& com);


    friend ostream& operator << (ostream& os, Complejo& com);
    friend Complejo operator *(int num,Complejo& com);


};


Complejo::Complejo(const int entero, const int decimal){

    this->entero = entero;
    this->decimal = decimal;
}

Complejo::Complejo(const Complejo& com)
{
    this->entero=com.entero;
    this->decimal=com.decimal;
}

Complejo Complejo::operator+(const Complejo& com)
{
    Complejo nuevoComplejo(0,0);

    nuevoComplejo.entero+=com.entero+this->entero;
    nuevoComplejo.decimal+=com.decimal+this->decimal;

    return nuevoComplejo;
}

Complejo& Complejo::operator=(const Complejo& com)
{
    this->entero=com.entero;
    this->decimal=com.decimal;

    return *this;
}

Complejo Complejo::operator *(const Complejo& com)
{
    Complejo nuevoComplejo(0,0);

    nuevoComplejo.entero = this->entero*com.entero - this->decimal*com.decimal;
    nuevoComplejo.decimal = this->entero * com.decimal + this->decimal*com.entero;

    return nuevoComplejo;
}

ostream& operator << (ostream& os, Complejo& com)
{
    os << com.entero << "." << com.decimal;
    return os;
}

Complejo operator *(int num,Complejo& com)
{
    Complejo nuevoComplejo(0,0);

    nuevoComplejo = com;

    nuevoComplejo.entero*=num;
    nuevoComplejo.decimal*=num;

    return nuevoComplejo;

}

int main()
{
    Complejo c1(1, 2);
    Complejo c2(2, 1);

    Complejo c3 = c1 + c2;

    cout << c3 << " = " << c1 << " + " << c2 << endl;

    Complejo c4 = 5 * c3;

    cout << c4 << " = " << 5 << " * " << c3 << endl;

    Complejo c5 = c3 * c4;

    cout << c5 << " = " << c3 << " * " << c4 << endl;


    return 0;
}
