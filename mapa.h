#ifndef MAPA_H
#define MAPA_H

#include "casilleros/casillero.h"

class Mapa{

	private:
		  int cantidad_filas;
		  int cantidad_columnas;
		  Casillero*** casilleros;

		
	public:
	
		//Costructor
		Mapa();
		
		//Precondiciones: -
		//Postcondicions: Inicializa la memoria del mapa
		void inicializar_mapa(int cant_filas, int cant_columnas);
	
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de filas
		int obtener_cantidad_filas ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de columnas
		int obtener_cantidad_columnas ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el tipo de casillero
		Casillero* tipo_casillero(int fila, int columna);

		//Precondiciones: -
		//Postcondicions: Crea un objeto casillero transitable, intransitabloe o construible
		Casillero* identificar_casillero(int fila, int columna, char caracter);
		
		//Precondiciones: -
		//Postcondiciones: Agrega el casillero leído a la lista de casilleros
		void agregar_casillero(Casillero* casillero);
		
		bool se_puede_demoler (int fila, int columna);

      	Casillero* obtener_casillero(int fila, int columna);


		//Precondiciones: -
		//Postcondicions: Muestra un dibujo del mapa 
		void mostrar_mapa ();
			
		//Precondiciones: un numero mayor a 0
		//Postcondicions: devuelve un numero entre el limite y 0
		void pedir_coordenada(int &fila, int &columna);

		

	


		//Precondiciones: -
		//Postcondiciones: Libera la memoria utilizada por los casilleros
		void liberar_casilleros ();
	private:
		void identificar_contenido (Casillero* casillero);

};



#endif //MAPA_H
