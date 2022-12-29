#include <iostream>
#include <math.h>

using namespace std;

//===================================CLASE PUNTO====================================================
class Punto
{
    private:
        int x;
        int y;
    public:
        Punto();
        Punto(int x, int y);
        Punto(const Punto& pun);

    friend ostream& operator <<(ostream& os, Punto pun);
    friend class Recta;
};

ostream& operator <<(ostream& os, Punto pun)
{
    os<<"("<<pun.x<<","<<pun.y<<")";

    return os;
}

Punto::Punto()
{
    this->x=0;
    this->y=0;
}

Punto::Punto(const Punto &pun)
{
    this->x=pun.x;
    this->y=pun.y;
}

Punto::Punto(int x, int y)
{
    this->x=x;
    this->y=y;
}

//==================================================================================================
//===================================CLASE RECTA====================================================
class Recta
{
    private:
        Punto p1;
        Punto p2;
    public:
        Recta(Punto punto1, Punto punto2);
        Punto operator&&(Recta r2);
        float operator-(Punto pun);

    friend ostream& operator <<(ostream& os, Recta& rec);

};

float Recta::operator-(Punto pun)
{
    float numerador = abs((this->p2.y-this->p1.y)*pun.x-(this->p2.x-this->p1.x)*pun.y+this->p2.x*this->p1.y-this->p2.y*this->p1.x);
    float denominador = sqrt(pow(this->p2.y-this->p1.y,2)+pow(this->p2.x-this->p1.x,2));

    return numerador/denominador;
}

ostream& operator <<(ostream& os, Recta& rec)
{
    os << " r: " << "a" << rec.p1 << " + " << rec.p2;

    return os;
}

Punto Recta::operator&&(Recta r2)
{
    Punto nue;

    nue.x=(this->p1.x*this->p2.y-this->p1.y*this->p2.x)*(r2.p1.x-r2.p2.x)-(this->p1.x-this->p2.x)*(r2.p1.x*r2.p2.y-r2.p1.y*r2.p2.x);
    nue.x/=(this->p1.x-this->p2.x)*(r2.p1.y-r2.p2.y)-(this->p1.y-this->p2.y)*(r2.p1.x-r2.p2.x);


    nue.y=(this->p1.x*this->p2.y-this->p1.y*this->p2.x)*(r2.p1.y-r2.p2.y)-(this->p1.y-this->p2.y)*(r2.p1.x*r2.p2.y-r2.p1.y*r2.p2.x);
    nue.y/=(this->p1.x-this->p2.x)*(r2.p1.y-r2.p2.y)-(this->p1.y-this->p2.y)*(r2.p1.x-r2.p2.x);


    return nue;
}

Recta::Recta(Punto punto1, Punto punto2)
{
    this->p1=punto1;
    this->p2=punto2;
}

//==================================================================================================

int main()
{
    Recta r1(Punto(2, 0), Punto(0, 2));
    Recta r2(Punto(1, 0), Punto(1, 2));

    Punto p(2, 2);

   cout << "Punto de Interseccion entre las rectas " << r1 << " y " << r2 << ": " << (r1 && r2) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r1 << ": " << (r1 - p) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r2 << ": " << (r2 - p) << endl;

    return 0;
}
