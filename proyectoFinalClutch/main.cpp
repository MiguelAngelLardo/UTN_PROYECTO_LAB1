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
