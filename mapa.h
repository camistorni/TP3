#ifndef MAPA_H
#define MAPA_H

#include "casilleros/casillero.h"

class Mapa{

	private:
		  int cantidadFilas;
		  int cantidadColumnas;
		  Casillero*** casilleros;

		
	public:
	
		//Costructor
		Mapa();
		~Mapa();
		
		//Precondiciones: -
		//Postcondicions: Inicializa la memoria del mapa
		void inicializarMapa(int cantFilas, int cantColumnas);
	
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de filas
		int obtenerCantidadFilas ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de columnas
		int obtenerCantidadColumnas ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el tipo de casillero
		Casillero* tipoCasillero(int fila, int columna);

		//Precondiciones: -
		//Postcondicions: Crea un objeto casillero transitable, intransitabloe o construible
		Casillero* identificarCasillero(int fila, int columna, char caracter);
		
		//Precondiciones: -
		//Postcondiciones: Agrega el casillero leído a la lista de casilleros
		void agregarCasillero(Casillero* casillero);
		
		bool sePuedeDemoler (int fila, int columna);

      	Casillero* obtenerCasillero(int fila, int columna);


		void imprimirMapa(int fila, int columna);

		//Precondiciones: -
		//Postcondicions: Muestra un dibujo del mapa 
		void mostrarMapa ();
			
		//Precondiciones: un numero mayor a 0
		//Postcondicions: devuelve un numero entre el limite y 0
		void pedirCoordenada(int &fila, int &columna);

		

	


		//Precondiciones: -
		//Postcondiciones: Libera la memoria utilizada por los casilleros
		void liberarCasilleros ();
	private:
		void identificarContenido (Casillero* casillero);

};



#endif //MAPA_H
