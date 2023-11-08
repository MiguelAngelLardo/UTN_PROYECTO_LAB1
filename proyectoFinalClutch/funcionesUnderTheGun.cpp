#include <iostream>
#include "funciones.h"
#include "estructuras.h"


///Comprueba que no haya escalera y quien es el STARTER del juego.
bool straightHand (Jugador &j1, Jugador &j2){ ///SE USA UNA VEZ ESTA FX

  int contadorEscalera1 = 0;
  int contadorEscalera2 = 0;

  for(int x = 0; x < CARTAS_CORRAL; x ++){
    contadorEscalera1 += (j1.corral[x].valor == VALORES[x]) ? 1 : 0;
    contadorEscalera2 += (j2.corral[x].valor == VALORES[x]) ? 1 : 0;
  }
  return (contadorEscalera1 == 5 || contadorEscalera2 == 5) ? true : false;
}

int clutchStarter(Jugador j1, Jugador j2) /// validad el RETURN 0; ///SE USA UNA VEZ ESTA FX
{
  int contadores1[CARTAS_CORRAL] = {}; // indice [0] = A, [1] = K, [2] = Q, etc...
  int contadores2[CARTAS_CORRAL] = {};

  // cuenta en indice cero cuantas ASES tiene cada jugador
  for (int x = CARTAS_CORRAL -1; x >= 0; x--){
    for (int y = CARTAS_CORRAL-1; y >= 0; y--){
      contadores1[x] += (j1.corral[y].valor == VALORES[x]) ? 1 : 0;
      contadores2[x] += (j2.corral[y].valor == VALORES[x]) ?  1 : 0;
    }
  }

  // comparar
  for (int x = CARTAS_CORRAL-1; x >= 0; x--){
    if (contadores1[x] > contadores2[x]){
      return 1;
    }else if (contadores1[x] < contadores2[x]){
      return 2;
    }
  }
  return 0;
}
