#include <iostream>
#include "rlutil.h"
#include "funciones.h"
#include "estructuras.h"

void dadoCaraUno(Jugador &j, Carta mazo[]) ///elige del propio corral y cambia por mazo
{
    int posicion;
    Carta top; // La primera del mazo
    Carta cartaJugador; //La carta del jugador que quiere cambiar.

    cout << "Intercambiar una carta del propio corral con una del mazo" << endl;
    cout << endl << "Ingrese el número de la carta que quiere seleccionar de su propio corral: ";
    cin >> posicion; ///Selecciono mi carta
    validarIngreso(posicion);

    for (int x = 0; x < MAZO; x++)
    {
      if (mazo[x].enMazo)
      {
        top = mazo[x]; //la primera coincidencia.Osea la primer carta True
        mazo[x].enMazo = false; // ponemos en false;
        x = MAZO;
      }
    }

    cartaJugador = j.corral[posicion - 1]; //esto es para ir al indice del array
    j.corral[posicion-1].bloqueada = false;///pongo en false una carta bloqueada

    for (int x = 0; x < MAZO; x++)
    {
      if (cartaJugador.palo == mazo[x].palo && cartaJugador.valor == mazo[x].valor)
      {///Por ej 10 de picas es true en el jugador y false en el mazo => aqui lo pongo en true en el mazo
        mazo[x].enMazo = true; // en la coincidnecia, ponemos true.
      }
    }

    j.corral[posicion -1] = top;

    cout << "La carta " << top.palo << " " << top.valor << " es la carta tomada del mazo" << endl;
}

void dadoCaraDos(Jugador &j, Carta mazo[]){///elige del contrario y cambia por mazo
  int posicion;
  Carta top; // La primera del mazo
  Carta cartaJugadorContrario; //La carta del jugador que quiere cambiar.

  cout << "Intercambiar una carta del corral CONTRARIO con una del mazo" << endl;
  cout << endl << "Ingrese el número de la carta que quiere seleccionar del corral de su oponente: ";
  cin >> posicion; ///Selecciono mi carta
  validarIngreso(posicion);

  while(j.corral[posicion-1].bloqueada)
  {
    cout << "No puedes usar una carta bloqueada." << endl;

    cout << "INGRESE OTRA CARTA para Intercambiar una carta del corral CONTRARIO con una del mazo" << endl;
    cout << endl << "Ingrese el número de la carta que quiere seleccionar del corral de su oponente: ";
    cin >> posicion; ///Selecciono mi carta
    validarIngreso(posicion);
  }

  for (int x = 0; x < MAZO; x++)
  {
    if (mazo[x].enMazo)
    {
      top = mazo[x]; //la primera coincidencia.Osea la primer carta True
      mazo[x].enMazo = false; // ponemos en false;
      x = MAZO;
    }
  }

  cartaJugadorContrario = j.corral[posicion - 1]; //esto es para ir al indice del array

  for (int x = 0; x < MAZO; x++)
  {
    if (cartaJugadorContrario.palo == mazo[x].palo && cartaJugadorContrario.valor == mazo[x].valor)
    {///Por ej 10 de picas es true en el jugador y false en el mazo => aqui lo pongo en true en el mazo
      mazo[x].enMazo = true; // en la coincidnecia, ponemos true.
    }
  }

  j.corral[posicion -1] = top;

  cout << "La carta " << top.palo << " " << top.valor << " es la carta tomada del mazo" << endl;
}

void dadoCaraTres(Jugador &j1, Jugador &j2){ ///Cambio una mia por una del contrario
  int posicionA, posicionB;

  cout << "Intercambiar una carta del propio corral con una del oponente" << endl;
  cout << "Ingrese la posicion de la carta de su corral: ";
  cin >> posicionA;
  validarIngreso(posicionA);
  cout << "Ingrese la posicion de la carta del corral contrario: ";
  cin >> posicionB;
  validarIngreso(posicionB);


  while(j1.corral[posicionA-1].bloqueada || j2.corral[posicionB - 1].bloqueada)
  {
    cout << endl << "No puedes usar una carta bloqueada." << endl;

    cout << "INGRESE OTRA CARTA para Intercambiar una carta del propio corral con una del oponente" << endl;
    cout << "Ingrese la posicion de la carta de su corral: ";
    cin >> posicionA;
    validarIngreso(posicionA);
    cout << "Ingrese la posicion de la carta del corral contrario: ";
    cin >> posicionB;
    validarIngreso(posicionB);
  }

  /// Siempre el jugador 2 va a ser el jugador pasivo, independientemte si este es el A o el B -> le da al jugador j1 10 ptos en la ultima mano
  j2.sinRobo = false;

  Carta aux;
  aux = j1.corral[posicionA -1];
  j1.corral[posicionA -1] = j2.corral[posicionB -1];
  j2.corral[posicionB -1] = aux;
}

void dadoCaraCuatro(Jugador &j){/// Cambio 1 mia por otra mia
  int posicionA, posicionB;

  cout << "Intercambiar una carta del propio corral con otra de tu propio corral" << endl;
  cout << "Primer Carta: ";
  cin >> posicionA;
  validarIngreso(posicionA);
  cout << "Segunda Carta: ";
  cin >> posicionB;
  validarIngreso(posicionB);

  Carta aux;
  aux = j.corral[posicionA -1];
  j.corral[posicionA -1] = j.corral[posicionB -1];
  j.corral[posicionB -1] = aux;
}

void dadoCaraCinco(Jugador &j){///Bloque mi carta para que dado 2 y dado 3 no la modifique.
  int posicion;

  cout << "Bloquear una carta de su corral para que no sea utilizada con la cara 2 y 3 del dado" << endl;
  cout << "Ingrese la posicion de la carta de su corral: ";
  cin >> posicion;
  validarIngreso(posicion);

  j.corral[posicion-1].bloqueada = true;

  cout << "FELICITACIONES! Ahora la carta: " << j.corral[posicion-1].palo << " " << j.corral[posicion-1].valor << " ha sido BLOQUEADA!!" << endl;
}

void dadoCaraSeis(Jugador &j1, Jugador &j2, Carta vMazo[], int &ultimaJugada) {
  int opcion;

  do{
    cout << "PUEDES ELEGIR CUALQUIERA DE ESTAS OPCIONES: " << endl;
    cout << "1- Elige una carta de tu propio corral y cambiala por una del mazo." << endl;
    cout << "2- Elige una carta del corral CONTRARIO y cambiala por una del mazo." << endl;
    cout << "3- Elige una carta de TU corral y cambiala por una del corral CONTRARIO." << endl;
    cout << "4- Cambiar una carta de TU corral por otra de TU corral (Intercambio)." << endl;
    cout << "5- Bloquear Carta (Inhibe la función del dado DOS y dado Tres)." << endl;
    cout << "0- NO HACER NADA y PASAR EL TURNO." << endl;
    cout << "Elige una opción: ";
    cin >> opcion;
    cout << endl;
    if (opcion < 0 || opcion > 5) {
      cout << "Opción no válida. Debes elegir un número del 0 al 5." << endl;
    }
  }while(opcion < 0 || opcion > 5);

  switch (opcion) {
    case 1:
      dadoCaraUno(j1, vMazo);
      ultimaJugada = 1;
      break;
    case 2:
      dadoCaraDos(j2, vMazo);
      ultimaJugada = 2;
      break;
    case 3:
      dadoCaraTres(j1, j2);
      ultimaJugada = 3;
      break;
    case 4:
      dadoCaraCuatro(j1);
      ultimaJugada = 4;
      break;
    case 5:
      dadoCaraCinco(j1);
      ultimaJugada = 5;
      break;
    case 0:
      /// si j1 pasa turno son 10ptos que no se suman
      j1.sinPasarTurno = false;
      cout << "PASESTE DE TURNO! Pasando el turno sin hacer nada." << endl;
      ultimaJugada = 0;
  }
}
