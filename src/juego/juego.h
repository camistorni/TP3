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

		//int cantidadMateriales, cantidadEdificios, cantidadUbicaciones;
	
	public:

		//Costructor 
		Juego();
		~Juego();

		int obtenerCantidadMateriales();
		int obtenerCantidadEdificios();
		Jugador* obtenerJugador();
		int obtenerJugadorActivo();
		Jugador** obtenerJugadores();
		void establecerJugadorActivo(int jugador);
		Edificio* obtenerEdificio(std::string nombreEdificio);
		Mapa* obtenerMapa();
		bool esPartidaNueva();
		ABB* obtenerAbb();
		

		// Pre: -
		// Post: Guarda los edificios en el archivo "edificios" y elimina la lista. Guarda los materiales en el archivo "materiales" y elimina la lista. Guarda las ubicaciones en el archivo "ubicaciones" y elimina la lista. Libera la memoria utilizada para el mapa
		void guardarYSalir();

		//Precondiciones: -
		//Postcondiciones: Guarda los datos de todos los archivos
		void leerArchivos();
		
		void mostrarMapa();
		//Precondiciones: -
		//Postcondiciones: Guarda los datos del archivo de materiales
		void leerMateriales();

		//Precondiciones: -
		//Postcondiciones: Guarda los datos del archivo de edificios
		void leerOpcionesEdificios();
		
		//Precondiciones: -
		//Postcondiciones: Guarda los datos del archivo de ubicaciones
		void leerUbicaciones();
		
		//Precondiciones: -
		//Postcondiciones: Guarda los datos del archivo de mapa
		void leerMapa();

		
		//Precondiciones: -
		//Postcondiciones: Imprime los materiales disponibles
		void mostrarInventario();

		
		//Precondiciones: Se tiene que haber leído bien el archivo de edificio
		//Postcondiciones: Agrega el edificio leído a la lista de edificios disponibles
		void agregarEdificio(Edificio* edificio);
		
		//Precondiciones: -
		//Postcondiciones: Agrega cantidades de material dependiendo del edificio ingresado
		void agregarRecursos(string nombreEdificio);
		
		//Precondiciones: -
		//Postcondiciones: Recolecta los materiales generados por los edificios
		void recolectarRecursos();
		
		//Precondiciones: Se tiene que haber leído bien el archivo de ubicaciones //(modificar)
		//Postcondiciones: Agrega la ubicación leída a la lista de ubicaciones
		int identificarEdificio(string tipoEdficio);
		
		//Precondiciones: -
		//Postcondiciones: Imprime los edificios construidos
		void listarEdificiosConstruidos();
		
		//Precondiciones: -
		//Postcondiciones: Imprime todos los edificios y sus especificaciones
		void listarEdificios();

		//Precondiciones: -
		//Postcondiciones: Verifica que exista el edificio ingresado y, si existe, guarda los datos del edificio en las variables ingresadas
		bool verificarEdificio(string nombreIngresado, int* piedraNecesaria, int* maderaNecesaria, int* metalNecesario);
		
		//Precondiciones: -
		//Postcondiciones: Verifica que haya las coordenadas ingresadas estén disponibles para construir
		bool verificarCoordenadas(int fila, int columna);
		
		//Precondiciones: -
		//Postcondiciones: Imprime un mensaje de error si algún material es insuficiente
		
		//Precondiciones: Se debe verificar que haya suficientes materiales, que el edificio ingresado exista, y que las coordenadas estén disponibles
		//Postcondiciones: Pregunta al usuario si de verdad quiere construir y, si afirma, construye el edificio ingresado y modifica la lista de materiales y edificios
		bool construirEdificio(string nombreIngresado);

		//Precondiciones: -
		//Postcondiciones: - (modificar)
		void demolerEdificioCoordenada();

		void aumentarMaterialesDerrumbe(Edificio* edificio);

		void consultarCoordenada();

		void lluviaElementos();

		void modificarMateriales();

		

		//Precondiciones: -
		//Postcondiciones: Guarda los edificios en el archivo "edificios" y elimina la lista
		void cerrarEdificios();

		//Precondiciones: -
		//Postcondiciones: Guarda los materiales en el archivo "materiales" y elimina la lista
		void cerrarMateriales();
		
		//Precondiciones: -
		//Postcondiciones: Guarda las ubicaciones en el archivo "ubicaciones" y elimina la lista
		void cerrarUbicaciones();
		
		//Precondiciones: -
		//Postcondiciones: Libera la memoria utilizada para el mapa
		void cerrarMapa();
		
		//Precondiciones: -
		//Postcondiciones: Imprime el menu de opciones
		void mostrarMenu();
		
		//Precondiciones: -
		//Postcondiciones: Pide al usuario que ingrese una opcion y verifica que sea válida
		int pedirOpcion();

		//Precondiciones: La opcion ingresada debe ser válida
		//Postcondiciones: Procesa la opcion ingresada por el usuario
		void procesarOpciones(int opcion);
		
		//PRE: -
		//POS: Crea los vértices del grafo
		void crearVertices(int fila, int columna);
		
		//PRE: Los vértices deben estar bien agregados
		//POS: Crea caminos entre cada vértice del grafo
		void crearCaminos();
		
		//PRE: -
		//POS: Devuelve los valores de cada casillero del mapa
		int valoresCaminos(int x, int y);
		
		//PRE: -
		//POS: Imprime el camino minimo ingresado
		void mostrarCaminoMinimo(string origen, string destino, int *energia);
		
		string obtenerCoordenadaJugador();

		void modificarEdificio(std::string nombre, string material, int nuevoValor);

		
		
};

#endif
