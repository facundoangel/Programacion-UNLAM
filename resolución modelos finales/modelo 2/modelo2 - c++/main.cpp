#include <iostream>
#include <string.h>

using namespace std;

class Medicion
{
private:
    float medicion;
    char* unidad;
public:
    Medicion():medicion(0),unidad(NULL){}
    Medicion(const Medicion& med);
    Medicion(float paramMed, const char* paramUnid);
    Medicion& operator = (Medicion med);
    Medicion operator - (Medicion& med) const;
    ~Medicion();


    //friend ostream& operator<< (ostream& os, Medicion med);
    friend ostream& operator<< (ostream& os, Medicion med);
    friend Medicion operator+ (float num, Medicion med);
};

Medicion::Medicion(const Medicion& med)
{
    this->medicion=med.medicion;
    this->unidad = new char[strlen(med.unidad)+1];
    strcpy(this->unidad,med.unidad);
}

Medicion::Medicion(float paramMed, const char* paramUnid)
{
    this->medicion=paramMed;
    this->unidad = new char[strlen(paramUnid)+1];
    strcpy(this->unidad,paramUnid);
}

Medicion& Medicion::operator = (Medicion med)
{
    if(strcmp(this->unidad,med.unidad)==0)
    {
        this->medicion=med.medicion;
    }

    return *this;
}

Medicion Medicion::operator - (Medicion& med) const
{
    Medicion nue(this->medicion,this->unidad);

    if(strcmp(nue.unidad,med.unidad)==0)
    {
        nue.medicion-=med.medicion;
    }
    else{
        throw "Distintas unidades de medidas";
    }

    return nue;
}

Medicion::~Medicion()
{
    delete [] this->unidad;
}

ostream& operator<< (ostream& os, Medicion med)
{
    os << med.medicion << med.unidad;

    return os;
}

Medicion operator+ (float num, Medicion med)
{
    Medicion nue(med.medicion,med.unidad);

    nue.medicion+=num;

    return nue;

}


int main()
{
    system("chcp 1252 > nul");

    Medicion med(45.5,"cº");
    Medicion med2(0.5,"cº");
    Medicion med3= med-med2;
    Medicion med4(3,"Lts");
    cout << "Resultado 1: " << 10.0 + med << endl;

    try{
        cout <<"Resultado 2: "<< med-med4 << endl;

    }catch(...){
        cout << "Error: Algo ocurrio" <<endl;
    }
    return 0;
}
