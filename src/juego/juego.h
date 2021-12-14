#ifndef JUEGO_H
#define JUEGO_H

#include "../materiales/materiales.h"
#include "../mapa/mapa.h"
#include "../edificios/edificio.h"
#include "../edificios/edificio.h"
#include "../edificios/edificio.h"
#include "../jugadores/jugador.h"
#include "grafo/Grafo.h"
#include "../diccionario/ABB.h"

#include <iostream>
#include "../constantes/constantes.h"

using namespace std;

class Juego{

	private:
		Mapa* mapa;
		Grafo *grafo;
		ABB* abb;
		Edificio** listaEdificios;
		Jugador** jugadores;
		int jugadorActivo;
		int cantidadEdificios, cantidadMateriales;
		bool partidaNueva;
		bool partidaGanada;

		//int cantidadMateriales, cantidadEdificios, cantidadUbicaciones;
	
	public:

		//Costructor 
		Juego();
		// Destructor
		~Juego();

		// Pre: -
		// Post: Devuelve la cantidad de material
		int obtenerCantidadMateriales();
		// Pre: -
		// Post: Devuelve la cantidad de edificios existentes
		int obtenerCantidadEdificios();
		// Pre: -
		// Post: Devuelve el numero del jugador que se encuentra activo en el momento
		int obtenerJugadorActivo();
		// Pre: -
		// Post: Devuelve al jugador que se encuentra activo en el momento
		Jugador* obtenerJugador();
		// Pre: -
		// Post: Devuelve el mapa del juego
		Mapa* obtenerMapa();
		// Pre: -
		// Post: Devuelve el ABB del juego
		ABB* obtenerAbb();
		// Pre: -
		// Post: Devuelve true si se trata de una partida nueva y false en caso contrario
		bool esPartidaNueva();

		// Pre: -
		// Post: Setea al jugador activo como el parametro recibido
		void establecerJugadorActivo(int jugador);

		
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos para el archivo de materiales
		
		// Pre: -
		// Post: Lee los datos del archivo de materiales
		void leerMateriales();

		// Pre: -
		// Post: Guarda los materiales en el archivo "materiales" y elimina la lista
		void cerrarMateriales();


//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos para el archivo de edificios

		// Pre: -
		// Post: Lee los datos del archivo de edificios
		void leerOpcionesEdificios();

		// Pre: -
		// Post: Verifica que exista el edificio ingresado y, si existe, guarda los datos del edificio en las variables ingresadas
		bool verificarEdificio(string nombreIngresado, int* piedraNecesaria, int* maderaNecesaria, int* metalNecesario);
		
		// Pre: -
		// Post: Imprime todos los edificios y sus especificaciones
		void listarEdificios();



//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos para el archivo de ubicaciones

		// Pre: -
		// Post: Lee los datos del archivo de ubicaciones
		void leerUbicaciones();

		// Pre: -
		// Post: Guarda las ubicaciones en el archivo "ubicaciones" y elimina la lista
		void cerrarUbicaciones();
		

//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos para el archivo de mapa

		// Pre: -
		// Post: Lee los datos del archivo de mapa
		void leerMapa();

		// Pre: -
		// Post: Verifica que haya las coordenadas ingresadas estén disponibles para construir
		bool verificarCoordenadas(int fila, int columna);
		
//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos para el grafo

		// Pre: -
		// Post: Crea los vértices del grafo
		void crearVertices(int fila, int columna);
		
		// Pre: Los vértices deben estar bien agregados
		// Post: Crea caminos entre cada vértice del grafo
		void crearCaminos();
		
		// Pre: -
		// Post: Devuelve los valores de cada casillero del mapa
		int valoresCaminos(int x, int y);
		
		// Pre: -
		// Post: Imprime el camino minimo ingresado
		void mostrarCaminoMinimo(string origen, string destino, int *energia);
		

//----------------------------------------------------------------------------------------------------------------------------------------------------
// Métodos

		// Pre: -
		// Post: Recolecta los materiales generados por los edificios
		void recolectarRecursos();
		
		// Pre: -
		// Post: Deposita los materiales de la lluvia en el mapa
		void lluviaElementos();

		// Pre: -
		// Post: Modifica los valores necesarios para construir un edificio
		void modificarEdificio(std::string nombre, string material, int nuevoValor);		

		void seGanoLaPartida(bool ganada);
		bool seGanoLaPartida();
};

#endif
