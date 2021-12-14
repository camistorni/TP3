#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "../../mapa/mapa.h"
#include "../juego.h"
using namespace std;

// Pre: Recibir el vector y el largo del mismo
// Post: Mezcla el vector recibida de manera aleatoria
void shuffleString(string* vector, int largo);
// Pre: Recibir el vector y el largo del mismo
// Post: Mezcla el vector recibida de manera aleatoria
void shuffleInt(int* vector, int largo);
// Pre: -
// Post: Devuelve la cantidad de material necesario para la lluvia de recursos
int valoresLluvia(string material);
// Pre: -
// Post: Imprime los errores
void imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria);
// Pre: Recibir el archivo abierto
// Post: Lee las coordenadas y las guarda en los punteros recibidos
void leerCoordenadas(ifstream& archivoUbicaciones, int* fila, int* columna, string residuo);
// Pre: Recibir el archivo abierto
// Post: Guarda en el archivo recibido los valores de los punteros con formato
void guardarCoordenadas(ofstream &archivoUbicaciones, int fila, int columna);
// Pre: Recibir el archivo abierto
// Post: Guarda los materiales en el archivo recibido
void guardarMateriales(ofstream &archivoUbicaciones, Juego *juego, int fila, int columna);
// Pre: Recibir el archivo abierto
// Post: Coloca en el mapa los datos recibidos en el archivo
void colocarMateriales (ifstream& archivoUbicaciones, Mapa* mapa);
// Pre: Recibir el archivo abierto
// Post: Coloca en el mapa al jugador correspondiente
void colocarJugador (ifstream& archivoUbicaciones, Mapa* mapa, int jugador);
// Pre: Recibir el archivo abierto
// Post: Coloca en el mapa los edificios recibidos en el archivo
void colocarEdificiosJugador (ifstream& archivoUbicaciones, Juego* juego, int jugador);
// Pre: Recibir el archivo abierto
// Post: Escribe en el archivo los datos necesarios
void guardarEdificios(ofstream &archivoUbicaciones, Juego *juego, int fila, int columna, int jugador);
// Pre: Recibir el archivo abierto
// Post: Se fija si el archivo recibido tiene información
bool isEmpty(ifstream& pFile);
// Pre: -
// Post: Escribe el archivo de materiales con todos sus valores en 0
void escribirNuevoArchivoMateriales();
// Pre: -
// Post: Escribe el archivo de ubicaciones vacio
void escribirNuevoArchivoUbicaciones();

#endif
