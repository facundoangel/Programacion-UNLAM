#include <iostream>


using namespace std;

class Complejo
{
    private:
        int real;
        int imaginario;
    public:
        Complejo(int real,int imaginario);
        Complejo operator + (Complejo comp) const;
        Complejo operator * (Complejo comp) const;

    friend ostream& operator << (ostream& os, Complejo& comp);
    friend Complejo operator * (int num, Complejo comp);


};

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


Complejo::Complejo(int real, int imaginario)
{
    this->real=real;
    this->imaginario=imaginario;
}

Complejo Complejo::operator + (Complejo comp) const
{
    Complejo nue(0,0);

    nue.real=this->real+comp.real;
    nue.imaginario=this->imaginario+comp.imaginario;


    return nue;
}

Complejo Complejo::operator * (Complejo comp) const
{
    Complejo nue(0,0);

    nue.real=this->real*comp.real-this->imaginario*comp.imaginario;
    nue.imaginario=this->real*comp.imaginario+this->imaginario*comp.real;


    return nue;
}

ostream& operator << (ostream& os, Complejo& comp)
{
    os << "(" << comp.real << "," << comp.imaginario <<")";
    return os;
}

Complejo operator * (int num, Complejo comp)
{
    Complejo nue(0,0);

    nue.real=num*comp.real;
    nue.imaginario=num*comp.imaginario;


    return nue;
}




