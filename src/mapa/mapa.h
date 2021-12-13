#ifndef MAPA_H
#define MAPA_H

#include "casilleros/casillero.h"
#include "casilleros/casilleroTransitable/casilleroTransitable.h"

class Mapa{

	private:
		  int cantidadFilas;
		  int cantidadColumnas;
		  Casillero*** casilleros;
		
	public:
	
	// Costructor
		Mapa(int cantFilas, int cantColumnas);
	
	// Destructor
		~Mapa();


	// Getters
		// Pre: -
		// Post: Devuelve la cantidad de filas
		int obtenerCantidadFilas ();

		// Pre: -
		// Post: Devuelve la cantidad de columnas
		int obtenerCantidadColumnas ();

		// Pre: -
        // Post: Devuelve un string con la posicion actual del jugador indicado
		std::string obtenerPosicionJugador(int jugador);

		// Pre: -
        // Post: Devuelve la posicion del jugador en los parametros recibidos
		void obtenerPosicionJugador(int *fila, int *columna, int jugador);

		// Pre: -
        // Post: Devuelve el tipo de casillero mediante el char
		char tipoCasillero(int fila, int columna);

		// Pre: -
        // Post: Devuelve el casillero indicado
		Casillero* obtenerCasillero(int fila, int columna);

		// Pre: -
        // Post: Devuelve la cantidad de casilleros transitables que se encuentran vacios
		int casillerosTransitablesVacios(CasilleroTransitable*** casillerosDisponibles);

		// Pre: -
        // Post: Devuelve la cantidad de edificios construidos
		int edificiosContruidos(string nombre, int jugador);
	
	
	
	
	// Setters
		// Pre: -
		// Post: Crea un objeto casillero transitable, intransitabloe o construible
		void agregarCasillero(int fila, int columna, char caracter);
		
		
	// Generales

		//Precondiciones: -
		//Postcondicions: Muestra un dibujo del mapa 
		void mostrarMapa ();

		// Pre: -
        // Post: Imprime el mapa
		void imprimirMapa(int fila, int columna, int index);
		
		// Pre: un numero mayor a 0
		// Post: devuelve un numero entre el limite y 0
		void pedirCoordenada(int &fila, int &columna);

		void AlduChequeo();
};

#endif //MAPA_H
