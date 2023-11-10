#include <iostream>
#include <locale>
#include <iomanip> // Necesario para setw
#include "rlutil.h"
#include "funciones.h"
#include "estructuras.h"

using namespace std;

void mostrarPuntajes(Jugador &ganador, Jugador &perdedor, int ultimaJugada)
{
  setlocale(LC_ALL, "Spanish");

  cout << "La ultima jugada fue: " << ultimaJugada << endl;

  int ptjGanar = 15;
  int ptjUltRob = 0;
  int ptjcartasMal = 0; //lo suma en el for
  int ptjSinPasar = 0;
  int ptjSinRobo = 0;
  int total = 0;

  //Procesar ganador:

  if(ultimaJugada == 3){
    ptjUltRob = 10;
  }

  if(ganador.sinPasarTurno){
    ptjSinPasar = 10;
  }

  if(ganador.sinRobo){
      ptjSinRobo = 5;
  }

  for(int x = 0; x < CARTAS_CORRAL; x++)
  {
    if(perdedor.corral[x].valor != ganador.corral[x].valor)
    {
      ptjcartasMal+=5;
    }
  }

  total = ptjGanar + ptjUltRob + ptjcartasMal + ptjSinPasar + ptjSinRobo;
  ganador.puntajeHistorico = total;

  cout << endl;
  cout << "--------------------------------------------------------------------------" << endl;
  cout << "RESULTADOS DE LA PARTIDA" << endl;
  cout << "--------------------------------------------------------------------------" << endl;
  cout << "Ganar la partida:" << setw(31) << " | " << ptjGanar << " pts" << endl;
  cout << "Robo ultima carta al jugador rival:" << setw(13) << " | "  << ptjUltRob << " pts" << endl;
  cout << "Cartas mal ubicadas del rival x" << ptjcartasMal / 5 << setw(16) << " | " << ptjcartasMal << " pts"<< endl;
  cout << "Sin pasar de turno:" << setw(29) << " | "<< ptjSinPasar <<  " pts" << endl;
  cout << "Sin haber sufrido un robo del rival:" << setw(12) << " | " << ptjSinRobo << " pts" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "TOTAL:" << setw(42) << " | " << total << " pts" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "Presione una tecla para continuar" << endl;
  rlutil::anykey();
  rlutil::cls();


}







