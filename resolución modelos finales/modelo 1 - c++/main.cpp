#include <iostream>

using namespace std;

//=====================================================================================================================0

class Hora
{
private:
    long segundos;

public:
    Hora(){this->segundos=0;}
    Hora(int hh, int mm, int ss){this->segundos=hh*3600;this->segundos+=mm*60;this->segundos+=ss;}
    Hora(int hh, int mm){this->segundos=hh*3600;this->segundos+=mm*60;}
    Hora(const Hora& hor){this->segundos=hor.segundos;}
    Hora(long segundos):segundos(segundos){}


    Hora operator*(int mult) const;
    Hora& operator=(const Hora& hor){this->segundos=hor.segundos;return *this;}
    Hora operator-(const Hora& hor) const;
    Hora& operator+=(const Hora& hor){this->segundos+=hor.segundos; return *this;}
    Hora& operator+=(int ss){this->segundos+=ss; return *this;}


    friend Hora operator*(int mult,const Hora& hor);
    friend ostream& operator<<(ostream& os, const Hora& hor);


};


//METODOS

Hora Hora::operator*(int mult) const
{
    Hora nue(this->segundos);

    nue.segundos*=mult;

    return nue;
}

Hora operator*(int mult,const Hora& hor)
{
    Hora nue(hor.segundos);

    nue.segundos*=mult;

    return nue;
}

ostream& operator<<(ostream& os, const Hora& hor)
{



    int hora = hor.segundos / 3600;
    int minu = (hor.segundos % 3600)/60;
    int segu = (hor.segundos % 3600)%60;

    while(segu >= 60 || segu<0)
    {
        if(segu >= 60)
        {
            segu-=60;
            minu++;
        }
        if(segu<0)
        {
            segu+=60;
            minu--;
        }
    }

    while(minu >= 60 || minu<0)
    {
        if(minu >= 60)
        {
            minu-=60;
            hora++;
        }
        if(minu<0)
        {
            minu+=60;
            hora--;
        }
    }

    while(hora >= 24 || hora<0)
    {
        if(hora >= 24)
            hora-=24;
        if(hora<0)
            hora+=24;
    }

    os << hora << ":" << minu << ":" << segu;

    return os;
}



Hora Hora::operator-(const Hora& hor) const
{
    Hora nue(this->segundos);

    nue.segundos-=hor.segundos;

    return nue;
}

//=====================================================================================================================0

void probarHora(int hh, int mm, int ss, long segundos)
{
    Hora    h1(hh, mm, ss),
            h2(segundos),
            h3(h1 * 3),
            h4(3 * h3),
            h5,
            h6(hh, mm);



    cout << "h1 = " << h1 << endl <<
    "h2 = " << h2 << endl <<
    "h3 = " << h3 << endl <<
    "h4 = " << h4 << endl <<
    "h5 = " << h5 << endl <<
    "h6 = " << h6 << endl << endl;

    h5 = h2 += h3 += h4 += ss;
    //h2=Hora(15,25,30);


    cout << "h1 - h2 = " << h1 - h2 << endl <<
    "h1 = " << h1 << endl <<
    "h2 = " << h2 << endl <<
    "h3 = " << h3 << endl <<
    "h4 = " << h4 << endl <<
    "h5 = " << h5 << endl << endl;
}

int main()
{
    probarHora(10,20,30,56400);
    return 0;
}
