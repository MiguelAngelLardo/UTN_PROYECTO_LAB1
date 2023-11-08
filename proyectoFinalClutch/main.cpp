#include <iostream>
#include <locale>
#include <cstdlib> // Necesario para rand() y srand()
#include <ctime>   // Necesario para time()
#include "rlutil.h" //Posicionar, esconder, borrar pantalla, colores.
#include "funciones.h"
#include "estructuras.h"

using namespace std;

int main()
{
  rlutil::setBackgroundColor(rlutil::WHITE);
  rlutil::cls();//Borra pantalla para ver el fondo verde
  rlutil::setColor(rlutil::BLACK);

  setlocale(LC_ALL, "Spanish");
  srand(time(NULL));

  Jugador jugador1;
  Jugador jugador2;

  bool banderaUltimoGanador = false;

  //FUNCION MENU()
  mostrarMenu(jugador1, jugador2, banderaUltimoGanador);

  return 0;
}

/*

#include <iostream>
#include <fcntl.h>
#include <stdio.h>



using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"testing foreign character: \x2660" << endl;
    wcout << L"testing foreign character: \x2663" << endl;
    wcout << L"testing foreign character: \x2665" << endl;
    wcout << L"testing foreign character: \x2666" << endl;

    system("pause");

    return 0;
}
*/
