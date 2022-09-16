    #include "header.h"

    using namespace std;

    //Declaracion de variables estaticas
    const int Fecha::diasXMes[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
    const int Fecha::cantDiasXMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    Fecha::Fecha(){
        this->d = 1;
        this->m = 1;
        this->a = 0;
        diaRel=1;
        obtenerFechaNormal();



    }

    Fecha::Fecha(int d, int m, int a){

        this->a = a;
        this->m = m;
        this->d = d;
        obtenerDiaRel();
        obtenerFechaNormal();

    }


    int Fecha::calcularDiasXmes(int m, int y){

        return Fecha::diasXMes[m];

    }

      void Fecha::sumarFecha(int dias){
            diaRel+=dias;
            obtenerFechaNormal();

      }

      void Fecha::ajustarFecha(){

            int i = 1;

            while(!fechaValida(this->a,this->m,this->d))
            {

                this->d= this->d - cantDiasXMes[i];
                this->m++;
                i++;

            }

      }


      void Fecha::obtenerDiaRel(){
            int cantDiasAnios = this->a - ANIO_BASE;
            cantDiasAnios = cantDiasAnios * 365 + cantDiasAnios / 4 - cantDiasAnios / 100 + cantDiasAnios / 400;
            int cantDiasMeses = Fecha::calcularDiasXmes(this->m,this->a);
            diaRel = cantDiasAnios + cantDiasMeses + this->d;

      }

      void Fecha::obtenerFechaNormal(){


          //calculo la cantidad de años transcurridos en esos dias
          int aniosTranscurridos = diaRel / 365;
          this->a = diaRel / 365 ;
          //calculo la cantidad de dias transcurridos del año actual
          int diaDelAnioo = diaRel % 365;


          //asigno valores provisorios a this->d y this->m
          this->m = 1;
          this->d = diaDelAnioo - (aniosTranscurridos / 4) + (aniosTranscurridos / 100) - (aniosTranscurridos  / 400);
          this->a+=ANIO_BASE;


          ajustarFecha();



      }

      bool Fecha::fechaValida(int a, int m, int d){
            if(d>=1 && d<=cantDiasXMes[m])
                if(m>=1 && m<=12)
                    if(a>=ANIO_BASE)
                        return true;

            return false;
      }

      int Fecha::obtenerDia(){
            return this->d;
      }

      int Fecha::obtenerMes(){
            return this->m;
      }

      int Fecha::obtenerAnio(){
            return this->a;
      }

      void Fecha::establecerDia(int d){
            this->d = d;
      }

      void Fecha::establecerMes(int m){
            this->m = m;
      }


      void Fecha::establecerAnio(int a){
            this->a = a;
      }

      bool Fecha::operator == (string f){
            string fechaClase = to_string(this->d) + "/" + to_string(this->m) + "/" + to_string(this->a);
            //cout << fechaClase << endl;
            return f == fechaClase ;
      }



      ostream& operator << (ostream& o,Fecha& f){

            cout << "=======================================" << endl;
            o << "Fecha: " << f.obtenerDia() << " / " << f.obtenerMes() << " / "<< f.obtenerAnio();
            cout << "\n=======================================" << endl;


            return o;
      }


      istream& operator >> (istream& i, Fecha& f){
            int dias, mes, anio;
            cout << "Ingresar día: " << endl;
            i >> dias;
            f.establecerDia(dias);

            cout << "Ingresar mes: " << endl;
            i >> mes;
            f.establecerMes(mes);


            cout << "Ingresar año: " << endl;
            i >> anio;
            f.establecerAnio(anio);

            cout << f;

            return i;
      }


     void Fecha::mostrarDiaRel(){

        cout << "==================================" << endl;
        cout << "dia rel: " << diaRel << endl;
        cout << "==================================" << endl;
     }

     void Fecha::mostrarFechaNormal(){

        cout << "==================================" << endl;
        cout << "fecha: " << this->d << " / " << this->m << " / " << this->a << endl;
        cout << "==================================" << endl;
     }
