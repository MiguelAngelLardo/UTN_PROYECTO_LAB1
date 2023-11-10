#include <iostream>
#include <iomanip> // Necesario para setw
#include <cstdio> // Necesario para getchar()
#include "rlutil.h"
#include "funciones.h"
#include "estructuras.h"

using namespace std;

void nombresJugadores(Jugador &j1, Jugador &j2)
{
  setlocale(LC_ALL, "Spanish");
  char confirmacion;
  do
  {
    cout << endl << "CLUTCH" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Antes de comenzar deben registrar sus nombres:" << endl;
    cout << endl;

    cout << "Participante 1: ";
    cin.ignore(); // Limpiar el buffer del teclado antes de leer la cadena
    getline(cin, j1.nombre); //es para poner espacios entre nombres
    while(j1.nombre.length() > 15){
      cout << "Por favor ingrese un nombre mas corto (HASTA 15 LETRAS)." << endl;
      cout << "Participante 1: ";
      getline(cin, j1.nombre); //es para poner espacios entre nombres
    }

    cout << "Participante 2: ";
    getline(cin, j2.nombre);
    while(j2.nombre.length() > 15){
      cout << "Por favor ingrese un nombre mas corto (HASTA 15 LETRAS)." << endl;
      cout << "Participante 2: ";
      getline(cin, j2.nombre); //es para poner espacios entre nombres
    }

    cout << endl << ("Confirmar nombres (S/N): ");
    cin >> confirmacion;
    cout << "---------------------------------------------------------" << endl;

    while (!(confirmacion == 'S' || confirmacion == 's' || confirmacion == 'N' || confirmacion == 'n')){
      cout << "Por favor ingrese solo 'S' o 'N'." << endl;
      cout << ("Confirmar nombres(S/N): "); //no sale el '¿'
      cin >> confirmacion;
    }

    confirmacion = (confirmacion == 's') ? 'S': confirmacion; //para no usar funcion std::toUppers
    confirmacion = (confirmacion == 'n') ? 'N': confirmacion; //para no usar funcion std::toUppers
    cout << ((confirmacion == 'N') ? "Ingrese los nombres nuevamente: " : "") << endl; // si es 'n' vuelve a empezar el while
  }
  while(confirmacion != 'S');
}

void resetearMazo(Carta vMazo[]){
  for (int i = 0; i < MAZO; i++)
  {//Esta funcion arma el mazo con el palo, el valor, enMazo, bloqueada
    vMazo[i] = {PALOS[i / MAZO_VALOR], VALORES[i % MAZO_VALOR], true, false};//enMazo = true, bloqueada = flase;
  }
  //0/5 = 0 "diamante"
  //0%5 = 0 "10"
  //1/5 = 0 "diamante"
  //1%5 = 1 "J"
  //2/5 = 0 "diamante"
  //2%5 = 2 "Q"
  //4/5 = 0 "diamante"
  //4%5 = 4 "A"
  //5/5 = 1 "Pica"
  //5%5 = 0 "10"
}

void mostrarMazoEnMesa(Carta vMazo[])
{
  cout << "+--------------------+" << endl;
  cout << "|                    |" << endl;

  for (int x = 0; x < MAZO; x++)
  {
    if (vMazo[x].enMazo == true)
    {
      cout << "|     ";
      if(vMazo[x].palo == "Corazon" || vMazo[x].palo == "Diamante" )
      {
        rlutil::setColor(rlutil::RED);
        cout<< vMazo[x].valor << " " << vMazo[x].palo;
        rlutil::setColor(rlutil::BLACK);
      }
      else
      {
        cout<< vMazo[x].valor << " " << vMazo[x].palo;
      }
      cout << setw(15 - vMazo[x].valor.length() - vMazo[x].palo.length()) << "|" << endl;
    } ///15 es el ancho total deseado.
  }  ///.length devuelve la longitud de la cadena. => estas son restadas al ancho de 15

  cout << "|                    |" << endl;
  cout << "+--------------------+" << endl;
}

void mezclarMazo(Carta vArr[])
{
  setlocale(LC_ALL, "Spanish");

  cout << "Mezclando mazo, presione una tecla para continuar...." << endl;
  rlutil::anykey();

  int aleatorio1, aleatorio2;
  Carta aux;

  for(int x=0; x<100; x++)
  {
    aleatorio1= generarNumero(MAZO);//Me da 1 aleatoreo
    aleatorio2= generarNumero(MAZO);//Me da 2 aleatoreo
    aux=vArr[aleatorio1];//Indice 1 {"Diamante", "J", true}
    vArr[aleatorio1]=vArr[aleatorio2]; // Indice 12 {"Pica", "Q", true}
    vArr[aleatorio2]=aux;//Donde tenia PICA Q voy a guardar DIAMANTE J
  }
}

void repartirCartas(Jugador &j1, Jugador &j2, Carta arr[])
{
  int aleatorio;
  for (int i = 0; i < MAZO_MESA; i ++)///son 10 vueltas EFECTIVAS!!
  {
    aleatorio = generarNumero(MAZO);
    if(arr[aleatorio].enMazo == true)/// [1] - [5]
    {
      if(i%2 == 0) //Indice par se asocia al jugador 1 e impar al jugador 2
      {
        j1.corral[i/2]=arr[aleatorio];/// 0/2 = 0
      }
      else
      {
        j2.corral[i/2]=arr[aleatorio]; /// 1/2 = 0.5 (osea CERO)
      }

    arr[aleatorio].enMazo = false;
    }
    else
    {
      i--;
    }
  }
}

void mostrarCartasDeJugadores(Jugador &j1, Jugador &j2)
{
  //mostrar con cout que le queda a cada jugador
  cout << "+--------------------+" << endl;
  cout << "|                    |" << endl;

  /// JUGADOR 1

  cout << "| ";
  rlutil::setColor(rlutil::RED);
  cout << j1.nombre << setw(20 - j1.nombre.length()) ;
  rlutil::setColor(rlutil::BLACK);
  cout<< "|" << endl;
  for(int x=0; x<CARTAS_CORRAL; x++)
  {
    cout << "|     ";
    if (j1.corral[x].bloqueada) //si esta bloqueada le pone "*", de lo contrario es todo igual pero sin el "*"
    {
      if(j1.corral[x].palo == "Diamante" || j1.corral[x].palo == "Corazon")
      {
        rlutil::setColor(rlutil::LIGHTRED);
        cout << "* ";
        cout << j1.corral[x].palo << " " << j1.corral[x].valor << setw(13 - j1.corral[x].valor.length() - j1.corral[x].palo.length());
        rlutil::setColor(rlutil::BLACK);
        cout << "|";
      }
      else
      {
        cout << "* ";
        cout << j1.corral[x].palo << " " << j1.corral[x].valor << setw(13 - j1.corral[x].valor.length() - j1.corral[x].palo.length());
        cout << "|";
      }
    }
    else
    {
      if(j1.corral[x].palo == "Diamante" || j1.corral[x].palo == "Corazon")
      {
        rlutil::setColor(rlutil::LIGHTRED);
        cout << j1.corral[x].palo << " " << j1.corral[x].valor << setw(15 - j1.corral[x].valor.length() - j1.corral[x].palo.length());
        rlutil::setColor(rlutil::BLACK);
        cout << "|";
      }
      else
      {
        cout << j1.corral[x].palo << " " << j1.corral[x].valor << setw(15 - j1.corral[x].valor.length() - j1.corral[x].palo.length()) << "|";

      }
    }
    cout << endl;
  }

  cout << "|                    |" << endl;
  cout << "|                    |" << endl;
  cout << "|                    |" << endl;

  /// JUGADOR 2

  cout << "| ";
  rlutil::setColor(rlutil::BLUE);
  cout << j2.nombre << setw(20 - j2.nombre.length()) ;
  rlutil::setColor(rlutil::BLACK);
  cout<< "|" << endl;

  for(int x=0; x<CARTAS_CORRAL; x++)
  {
    cout << "|     ";
    if (j2.corral[x].bloqueada)
    {
      if (j2.corral[x].palo == "Diamante" || j2.corral[x].palo == "Corazon")
      {
        rlutil::setColor(rlutil::LIGHTRED);
        cout << "* ";
        cout << j2.corral[x].palo << " " << j2.corral[x].valor << setw(13 - j2.corral[x].valor.length() - j2.corral[x].palo.length());
        rlutil::setColor(rlutil::BLACK);
        cout << "|";
      }
      else
      {
        cout << "* ";
        cout << j2.corral[x].palo << " " << j2.corral[x].valor << setw(13 - j2.corral[x].valor.length() - j2.corral[x].palo.length());
        cout << "|";
      }
    }
    else
    {
      if (j2.corral[x].palo == "Diamante" || j2.corral[x].palo == "Corazon")
      {
        rlutil::setColor(rlutil::LIGHTRED);
        cout << j2.corral[x].palo << " " << j2.corral[x].valor << setw(15 - j2.corral[x].valor.length() - j2.corral[x].palo.length());
        rlutil::setColor(rlutil::BLACK);
        cout << "|";
      }
      else
      {
        cout << j2.corral[x].palo << " " << j2.corral[x].valor << setw(15 - j2.corral[x].valor.length() - j2.corral[x].palo.length()) << "|";
      }
    }
    cout << endl;
  }
  cout << "|                    |" << endl;
  cout << "+--------------------+" << endl;
}

void mostrarRonda(Jugador jA, Jugador jB, int &contRonda, int &turno)
{
  cout << "CLUTCH" << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "RONDA #" << contRonda  << " - TURNO#" << turno << endl;
  rlutil::setColor(rlutil::RED);
  cout <<jA.nombre;
  rlutil::setColor(rlutil::BLACK);
  cout <<  " vs ";
  rlutil::setColor(rlutil::BLUE);
  cout <<jB.nombre << endl << endl;
  rlutil::setColor(rlutil::BLACK);
}


void validarIngreso(int &posicionCorral){
  while (posicionCorral < 1 || posicionCorral > 5){
    cout << "Ingrese un valor valido ENTRE 1 y 5: ";
    cin >> posicionCorral;
  }
}

bool juegoFinalizado(Jugador &j) {

  for (int i = 0; i < CARTAS_CORRAL; i++) {
    if(j.corral[i].valor != VALORES[i]){
      return false;
    }
  }
  return true;
}

Jugador juegoInsitu(Jugador &j1, Jugador &j2, int returne, Carta vMazo[])  /// el returne viene de clutchStarter
{
    setlocale(LC_ALL, "Spanish");

    Jugador jugadorA;
    Jugador jugadorB;
    Jugador ganador;

    int dado, turno = 1, contRonda = 1, ultimaJugada = -1;

    if(returne == 1)
    {
      jugadorA = j1;
      jugadorB = j2;
    }
    else
    {
      jugadorA = j2;
      jugadorB = j1;
    }

    bool juegoTerminado = false;
    while(!juegoTerminado)
    {
      mostrarRonda(jugadorA, jugadorB, contRonda, turno);

      if(turno %2 != 0)
      {
        rlutil::setColor(rlutil::RED);
        cout << "TURNO DE " << jugadorA.nombre << endl;
        rlutil::setColor(rlutil::BLACK);
      }
      else
      {
        rlutil::setColor(rlutil::BLUE);
        cout << "TURNO DE " << jugadorB.nombre << endl;
        rlutil::setColor(rlutil::BLACK);
        contRonda ++;///siempre que turno sea par me aumenta uno la ronda
      }

      cout << "Pulse Enter para lanzar el dado! "<< endl;
      dado = lanzarDado();
      getchar();// Espera a que se presione una tecla

      cout << "LANZAMIENTO DADO #" << dado << endl;
      cout << endl << "Cartas Actuales" << endl;

      mostrarCartasDeJugadores(jugadorA, jugadorB);
      switch (dado)
      {
      case 1:
        turno%2 != 0 ? dadoCaraUno(jugadorA, vMazo) : dadoCaraUno(jugadorB, vMazo);
        ultimaJugada = 1;
        break;
      case 2:
        turno%2 != 0 ? dadoCaraDos(jugadorB, vMazo) : dadoCaraDos(jugadorA, vMazo);
        ultimaJugada = 2;
        break;
      case 3:
        turno%2 != 0 ? dadoCaraTres(jugadorA, jugadorB) : dadoCaraTres(jugadorB, jugadorA);
        ultimaJugada = 3;
        break;
      case 4:
        turno%2 != 0 ? dadoCaraCuatro(jugadorA) : dadoCaraCuatro(jugadorB);
        ultimaJugada = 4;
        break;
      case 5:
        turno%2 != 0 ? dadoCaraCinco(jugadorA) : dadoCaraCinco(jugadorB);
        ultimaJugada = 5;
        break;
      case 6:
        turno%2 != 0 ? dadoCaraSeis(jugadorA, jugadorB, vMazo, ultimaJugada) : dadoCaraSeis(jugadorB, jugadorA, vMazo, ultimaJugada);
        break;
      }

      turno++;
      juegoTerminado = juegoFinalizado(jugadorA) || juegoFinalizado(jugadorB);

      if(!juegoTerminado)
      {
        mezclarMazo(vMazo);
      }
    }

    rlutil::setColor(rlutil::MAGENTA);
    cout << endl << "SHOWDOWN!! MUESTRA TUS CARTAS!:D"<< endl;
    rlutil::setColor(rlutil::BLACK);
    mostrarCartasDeJugadores(jugadorA, jugadorB);

    cout << "PARAPAPA PA PA PAPA! HAY UN GANADORRR, ESTE ES: " ;
    if(juegoFinalizado(jugadorA))
    {
      rlutil::setBackgroundColor(rlutil::GREEN);
      cout << jugadorA.nombre << endl;
      rlutil::setBackgroundColor(rlutil::WHITE);

      mostrarPuntajes(jugadorA, jugadorB, ultimaJugada);

      ganador = jugadorA;
    }
    else
    {
      rlutil::setBackgroundColor(rlutil::GREEN);
      cout << jugadorB.nombre << endl;
      rlutil::setBackgroundColor(rlutil::WHITE);

      mostrarPuntajes(jugadorB, jugadorA,  ultimaJugada);

      ganador = jugadorB;
    }
    return ganador;
}



