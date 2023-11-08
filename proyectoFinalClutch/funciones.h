#pragma once //guards
#include<iostream>
#include "estructuras.h"

///FUNCIONES DE MENÚ
void mostrarMenu(Jugador &j1, Jugador &j2, bool &banderaUltimoGanador);
void manejarOpcion(int opcion, Jugador &j1, Jugador &j2, Jugador &ganadorMaximo, bool &banderaUltimoGanador);

///FUNCIONES DE INGRESO DATOS PRIMARIOS
void nombresJugadores(Jugador &j1, Jugador &j2);

///FUNCIONES RANDOM
int generarNumero(int tamanio);

///FUNCIONES JUGAR
void resetearMazo(Carta vMazo[]);
void mezclarMazo(Carta vArr[]);
void repartirCartas(Jugador &j1, Jugador &j2, Carta arr[]);
void mostrarRonda(Jugador jA, Jugador jB, int &contRonda);
void mostrarMazoEnMesa(Carta vMazo[]);
void mostrarCartasDeJugadores(Jugador &j1, Jugador &j2);
void validarIngreso(int &posicionCorral);


///FUNCIONES UNDER THE GUN
int clutchStarter(Jugador j1, Jugador j2);
bool straightHand (Jugador &j1, Jugador &j2);

///FUNCIONES DADO
int lanzarDado();
void dadoCaraUno(Jugador &j, Carta mazoMano[]);
void dadoCaraDos(Jugador &j, Carta mazo[]);
void dadoCaraTres(Jugador &j1, Jugador &j2);
void dadoCaraCuatro(Jugador &j);
void dadoCaraCinco(Jugador &j);
void dadoCaraSeis(Jugador &j1, Jugador &j2, Carta vMazo[], int &ultimaJugada);

///JUEGO IN SITU
Jugador juegoInsitu(Jugador &j1, Jugador &j2, int returne, Carta vMazo[]);


///FIN DE JUEGO
bool juegoFinalizado(Jugador &jugador);

///PUNTAJES
void mostrarPuntajes(Jugador &ganador, Jugador &perdedor, int ultimaJugada);

///ESTADISTICA
void mostrarHito(Jugador &ganadorMaximo);
void reproducirSonidoEstd();


///CREDITOS
void mostrarCreditos(int &opcion, Jugador &j1, Jugador &j2);
void reproducirSonidoCred();

