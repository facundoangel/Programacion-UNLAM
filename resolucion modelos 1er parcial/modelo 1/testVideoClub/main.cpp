#include <iostream>
#include "../videoClub/Videojuego.h"

using namespace std;

int main()
{

    Videojuego v1;
    v1.mostrar();
    Videojuego v2("tetris","puzzle","sega",true,2);
    cout << v2 <<endl;
    char nom[500] = "virtual tenis";
    Videojuego v3(nom,"deportes","sega",false,0);
    v3.prestar();
    cout << endl << "Video Juego 3" << endl;
    v3.mostrar();
    v2=++v3;
    v2.mostrar();
    v3.devolver();
    cin >> v1;
    cout << "---mostrando videojuegos---" << endl;
    cout << v1 << v2 << v3;



    return 0;
}


