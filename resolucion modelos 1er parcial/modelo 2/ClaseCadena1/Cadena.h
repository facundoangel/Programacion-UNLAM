#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED

class Cadena{

    private:



    public:
        char* palabra;
        Cadena();
        Cadena(const char *cad);
        Cadena(Cadena& cad);
        ~Cadena();


        Cadena& operator =(const Cadena& cad);
        int longitud();


};

#endif // CADENA_H_INCLUDED
