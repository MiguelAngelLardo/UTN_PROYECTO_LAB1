#include <iostream>
#include <iomanip> // Necesario para setw
#include<windows.h>//Para reproducir musica
#include<mmsystem.h>//Para reproducir musica
#include <thread> // Incluye la biblioteca de hilos para reproducir la musica separadamente
#include "rlutil.h"
#include "funciones.h"
#include "estructuras.h"

void reproducirSonidoEstd() {
    PlaySound(TEXT("mk1.wav"), NULL, SND_ASYNC);//ASYNC es para que se corte la musica con enter
}

void mostrarHito(Jugador &ganadorMaximo){
  thread sonido(reproducirSonidoEstd);

  cout << endl << endl;

  cout << "+-----------------------+" << endl;
  cout << "|                       |" << endl;
  cout << "|HITO: " << ganadorMaximo.nombre << setw(18 - ganadorMaximo.nombre.length()) << "|" << endl;
  cout << "|------------------------" << endl;
  cout << "|TOTAL: " << ganadorMaximo.puntajeHistorico << " puntos" << setw(10 - to_string(ganadorMaximo.puntajeHistorico).length()) << "|" << endl;
  cout << "|                       |" << endl;
  cout << "+-----------------------+" << endl;

  cout << "Presione una tecla para continuar..." << endl;
  rlutil::anykey();
  rlutil::cls();
  PlaySound(NULL, 0, 0);
  sonido.join();//esta es para que el programa no se rompa al salir de ESTADISTICA
}


