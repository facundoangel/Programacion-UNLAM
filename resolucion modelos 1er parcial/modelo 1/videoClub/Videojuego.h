#ifndef VIDEOJUEGO_H_INCLUDED
#define VIDEOJUEGO_H_INCLUDED

using namespace std;

class Videojuego
{

    private:
        char* Titulo;
        char Genero[100];
        char *Fabricante;
        bool Entregado;
        int DiasDePrestamo;
        static void remplazarTitulo(Videojuego& vj, char* entrada);


    public:
        Videojuego();
        Videojuego(const char* titulo,const char* genero,const char* fabricante, bool entregado,int diasDePrestamo);
        Videojuego(const Videojuego& vj);
        Videojuego(char* titulo);
        ~Videojuego();

        inline void mostrar()
        {
            if(this->Titulo)
                cout << "Nombre: " << this->Titulo << endl;
            else
                cout << "Sin nombre" << endl;

        }
        inline void prestar() {this->Entregado=true; this->DiasDePrestamo=1;}
        inline void devolver() {this->Entregado=false; this->DiasDePrestamo=0;}
        Videojuego& operator =(Videojuego& vj);
        Videojuego& operator ++();



        friend ostream& operator << (ostream& os, Videojuego& vj);
        friend istream& operator >> (istream& is, Videojuego& vj);


};




#endif // VIDEOJUEGO_H_INCLUDED
