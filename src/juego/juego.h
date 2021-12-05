#ifndef JUEGO_H
#define JUEGO_H

#include "../materiales/materiales.h"
#include "../mapa/mapa.h"
#include "../edificios/edificio.h"
#include "../edificios/edificio.h"
#include "../edificios/edificio.h"
#include "../jugadores/jugador.h"
#include "grafo/Grafo.h"

#include <iostream>
#include "../constantes/constantes.h"

using namespace std;

class Juego{

	private:
		Mapa* mapa;
		Grafo *grafo;
		Edificio** listaEdificios;
		Jugador** jugadores;
		int jugadorActivo;
		int cantidadEdificios, cantidadMateriales;

		//int cantidadMateriales, cantidadEdificios, cantidadUbicaciones;
	
	public:

		//Costructor 
		Juego();
		~Juego();

		int obtenerCantidadMateriales();
		Jugador* obtenerJugador();
		int obtenerJugadorActivo();
		Jugador** obtenerJugadores();
		void establecerJugadorActivo(int jugador);
		Edificio* obtenerEdificio(std::string nombreEdificio);
		Mapa* obtenerMapa();
		
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
		bool verificarEdificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidadMax);
		
		//Precondiciones: -
		//Postcondiciones: Verifica que haya la suficiente cantidad de materiales para construir un edificio especifico
		bool verificarMateriales(string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario, int construidos, int cantidadMax);
		
		//Precondiciones: -
		//Postcondiciones: Verifica que haya las coordenadas ingresadas estén disponibles para construir
		bool verificarCoordenadas(int fila, int columna);
		
		//Precondiciones: -
		//Postcondiciones: Imprime un mensaje de error si algún material es insuficiente
		void imprimirMensajeError(string nombreEdificio, string material, int cantidad, int cantidadNecesaria);
		
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

		//Precondiciones: -
		//Postcondiciones: Guarda los edificios en el archivo "edificios" y elimina la lista. Guarda los materiales en el archivo "materiales" y elimina la lista. Guarda las ubicaciones en el archivo "ubicaciones" y elimina la lista. Libera la memoria utilizada para el mapa
		void guardarYSalir();
		
		void crearVertices(int fila, int columna);
		void crearCaminos();
		int valoresCaminos(int x, int y);
		void mostrarCaminoMinimo(string origen, string destino);
		
		
};

#endif