#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "../../mapa/mapa.h"
#include "../juego.h"
using namespace std;

void shuffleString(string* vector, int largo);
void shuffleInt(int* vector, int largo);
int valoresLluvia(string material);
void imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria);
void leerCoordenadas(ifstream& archivoUbicaciones, int* fila, int* columna);
void colocarMateriales (ifstream& archivoUbicaciones, Mapa* mapa);
void colocarJugador (ifstream& archivoUbicaciones, Mapa* mapa, int jugador);
void colocarEdificiosJugador (ifstream& archivoUbicaciones, Juego* juego, int jugador);
bool isEmpty(ifstream& pFile);

#endif