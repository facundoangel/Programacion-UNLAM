/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
***************************************************************************************/

#include <iostream>

using namespace std;


/** Figura **/

class Figura
{
public:
    virtual double area() const=0;
    virtual double perimetro()=0;
};


//double Figura::area() const
//{
//	return 0;
//}
//
//
//double Figura::perimetro()
//{
//	return 0;
//}


/** Circulo **/

#define PI 3.14159265358979323846

class Circulo : public Figura
{
private:
	double radio;

public:
	Circulo(double radio);

	double area() const override;
	double perimetro() override;
};


Circulo::Circulo(double radio)
: radio(radio)
{}


double Circulo::area() const
{
	return PI * radio * radio;
}


double Circulo::perimetro()
{
	return 2 * PI * radio;
}


/** Cuadrado **/

class Cuadrado : public Figura
{
private:
	double lado;

public:
	Cuadrado(double lado);

	double area() const override;
    double perimetro() override;
};


Cuadrado::Cuadrado(double lado)
: lado(lado)
{}


double Cuadrado::area() const
{
	return lado * lado;
}


double Cuadrado::perimetro()
{
	return 4 * lado;
}


/** Main **/

void imprimirFigura(Figura& figura);


int main()
{
    //Figura fig; /** Corrija el codigo para que no se pueda crear un objeto de clase Figura. Luego comente la linea para que el programa compile. **/
    Circulo circulo(5);
    Cuadrado cuadrado(4);

    imprimirFigura(circulo);
    imprimirFigura(cuadrado);

    return 0;
}


void imprimirFigura(Figura& figura)
{
    cout << "Area: " << figura.area() << endl;
    cout << "Perimetro: " << figura.perimetro() << endl;
}
