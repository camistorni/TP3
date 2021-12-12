#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "../materiales/materiales.h"
#include "juego.h"
#include "../edificios/parser.h"
#include "../edificios/edificio.h"
#include "../mapa/casilleros/casillero.h"
#include "../mapa/casilleros/casilleroConstruible/casilleroConstruible.h"
#include "../mapa/casilleros/casilleroInaccesible/casilleroInaccesible.h"
#include "../mapa/casilleros/casilleroTransitable/casilleroTransitable.h"
#include "../constantes/constantes.h"
#include "../diccionario/ABB.h"
#include "../diccionario/nodo.h"
#include "utils/utils.h"
#include "../diccionario/receta/receta.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

Juego::Juego () {
	jugadores = new Jugador*[2];
	jugadores[0] = new Jugador("Jugador 1");
	jugadores[1] = new Jugador("Jugador 2");
	grafo = new Grafo();
	abb = new ABB();
	cantidadMateriales = 0;
	jugadorActivo = -1;
	partidaNueva = false;
	leerMateriales();
	leerOpcionesEdificios();
	leerMapa();
	leerUbicaciones();
}

Juego::~Juego() {
	cerrarMateriales();	
	//cerrarUbicaciones();
	//cerrarMapa();
	for(int i = 0; i < 2; i++) {
		delete jugadores[i];
	}
	delete[] jugadores;
	jugadores = NULL;
	delete mapa;
	//mapa = NULL;
	/*for(int j = 0; j < cantidadEdificios; j++) {
		delete listaEdificios[j];
	}
	delete[] listaEdificios;*/
}

Jugador** Juego::obtenerJugadores(){
	return jugadores;
}

int Juego::obtenerCantidadMateriales() {
	return cantidadMateriales;
}

Jugador* Juego::obtenerJugador() {
	return jugadores[jugadorActivo];
}

int Juego::obtenerJugadorActivo() {
	return jugadorActivo;
}

void Juego::establecerJugadorActivo(int jugador) {
	jugadorActivo = jugador;
}

Mapa* Juego::obtenerMapa() {
	return mapa;
}

bool Juego::esPartidaNueva() {
	return partidaNueva;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerMateriales() {

	fstream archivoMateriales(PATH_MATERIALES, ios::in);
	
	Material *material;
	
	string nombre, cantidadMaterialJugador1, cantidadMaterialJugador2;
	
	while(archivoMateriales >> nombre) {
		archivoMateriales >> cantidadMaterialJugador1;
		archivoMateriales >> cantidadMaterialJugador2;
		
		material = new Material;
		*material = Material(nombre, stoi(cantidadMaterialJugador1));
		jugadores[0] -> agregarMaterial(material, cantidadMateriales);

		material = new Material;
		*material = Material(nombre, stoi(cantidadMaterialJugador2));
		jugadores[1] -> agregarMaterial(material, cantidadMateriales);

		cantidadMateriales++;
	}
	archivoMateriales.close();
}

void Juego::cerrarMateriales() {
	ofstream archivoMateriales(PATH_MATERIALES);
	if(archivoMateriales.is_open()) {
		for(int i = 0; i < cantidadMateriales; i++){
			archivoMateriales <<  jugadores[0] -> obtenerMateriales()[i] -> obtenerNombreMaterial() << " " << 
			jugadores[0] -> obtenerMateriales()[i] -> obtenerCantidadMaterial() << " " << 
			jugadores[1] -> obtenerMateriales()[i] -> obtenerCantidadMaterial() << endl;
			
			delete jugadores[0] -> obtenerMateriales()[i];
			delete jugadores[1] -> obtenerMateriales()[i];
		}
		
		delete[] jugadores[0] -> obtenerMateriales();
		//this -> jugadores[0] -> establecerMateriales() = nullptr;
		delete[] jugadores[1] -> obtenerMateriales();
	}
	
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerOpcionesEdificios(){
/////////////////////////// Revisar cuando esté el diccionario //////////////77///

	
	fstream archivoEdificios(PATH_EDIFICIOS, ios::in);
	string edificio;
	int piedra, madera, metal, maximoContruibles;

    while (archivoEdificios >> edificio){

        archivoEdificios >> piedra;
        archivoEdificios >> madera;
        archivoEdificios >> metal;
        archivoEdificios >> maximoContruibles;
		
		Receta* receta = new Receta(piedra, madera, metal, maximoContruibles);
		
		abb->insertarNodo(edificio, receta);

		cantidadEdificios++;
	}
	Receta* receta;
	if((receta = abb -> buscar(ASERRADERO)) != NULL) receta -> setearProduccion(MADERA);
	if((receta = abb -> buscar(MINA)) != NULL) receta -> setearProduccion(PIEDRA);
	if((receta = abb -> buscar(MINA_ORO)) != NULL) receta -> setearProduccion(ANDYCOINS);
	if((receta = abb -> buscar(ESCUELA)) != NULL) receta -> setearProduccion(ANDYCOINS);
	if((receta = abb -> buscar(FABRICA)) != NULL) receta -> setearProduccion(METAL);
	if((receta = abb -> buscar(PLANTA_ELECTRICA)) != NULL) receta -> setearProduccion(ENERGIA);

	archivoEdificios.close();
}

bool Juego::verificarEdificio(string nombreIngresado, int* piedraNecesaria, int* maderaNecesaria, int* metalNecesario){
	bool error = false;
	Receta* receta = new Receta();
	if ((receta = abb->buscar(nombreIngresado)) == NULL){
		cout << "El edificio '" << nombreIngresado << "' no existe" << endl << endl;
		error = true;
	} else if(
		mapa -> edificiosContruidos(nombreIngresado, jugadorActivo) >=
		abb -> buscar(nombreIngresado) -> obtenerMaterial(MAXIMO_CONSTRUIBLES)
	) {
		cout <<"Ya no puedes construir edificios del tipo " << nombreIngresado << endl;
		error = true;
	} else {
		for (size_t i = 0; i < 3; i++){
			if(obtenerJugador() -> buscarMaterial(MATERIALES_CONSTRUCCION[i]) -> obtenerCantidadMaterial() < receta -> obtenerMaterial(MATERIALES_CONSTRUCCION[i])){
				cout <<"Te faltan " << receta -> obtenerMaterial(MATERIALES_CONSTRUCCION[i]) - obtenerJugador() -> buscarMaterial(MATERIALES_CONSTRUCCION[i]) ->obtenerCantidadMaterial() << " de " << MATERIALES_CONSTRUCCION[i] << " para contruir el edificio" << endl;
				error = true;
			}
		}
	}
	if(!error){
		*piedraNecesaria = receta -> obtenerMaterial(PIEDRA);
		*maderaNecesaria = receta -> obtenerMaterial(MADERA);
		*metalNecesario = receta -> obtenerMaterial(METAL);
	}
	return error;
}

void Juego::listarEdificiosConstruidos(){
	////////////////////Arreglar cantidad construidos y edificios construidos ///////////////////
	////////////////////Falta alguna manera de imprimir solo nombres/////////////////////////////
/*
	int construidosTotal = 0;
	long nombreMasLargo = 0;
	long nombre = 0;
	
	std::cout << endl << endl;
	std::cout << "Lista de edificios construidos:" << endl << endl;
	
	std::cout << "            ═════════════════════════════════════════════════════════" << endl;
	std::cout << "             Nombre\t\tCantidad\t\tCoordenadas"<< endl;
	std::cout << "            ═════════════════════════════════════════════════════════" << endl;
	
	for(int i = 0; i < this ->cantidadEdificios; i++){
		nombre = this->abb->obtenerNodo(i)->obtenerClave().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}
	for(int i = 0; i < this ->cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> obtenerCantConstruidos() != 0){
		
			long espacio = nombreMasLargo - this->abb->obtenerNodo(i)->obtenerClave().length();
			std::cout << "             " << this->abb->obtenerNodo(i)->obtenerClave();
			std::cout << setw(8 + (int)espacio);
			std::cout << this -> listaEdificios[i] -> obtenerCantConstruidos() << setw(20);
			
			for(int j = 0; j < listaEdificios[i] -> obtenerCantConstruidos(); j++)
		 		std::cout << "(" << this -> listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerFila() << ", " << this -> listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerColumna() << ")";
			
			construidosTotal += listaEdificios[i]->obtenerCantConstruidos();
			std::cout << endl;
		}
	}
	std::cout << endl << endl;
	std::cout << "Cantidad total de edificios construidos: " << construidosTotal << endl << endl;
	*/
}

void Juego::listarEdificios(){
/////////////////////////// Falta max const y brinda material/////////////////////
	
	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos permitidos\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	abb -> imprimirTablaOrdenada();
	cout << endl << endl;

}

void Juego::recolectarRecursos(){
	string nombre;
	int cantidad;
	Casillero* casillero;
	for(int i = 0; i < mapa -> obtenerCantidadFilas(); i++) {
		for(int j = 0; j < mapa -> obtenerCantidadColumnas(); j++) {
			if((casillero = mapa -> obtenerCasillero(i, j)) -> obtenerTipo() == TERRENO){
				if(static_cast<CasilleroConstruible *>(casillero) -> recolectar(&nombre, &cantidad, jugadorActivo)){
					cout << "Se recolectaron " << cantidad << " de " << nombre << endl;
					jugadores[jugadorActivo] -> buscarMaterial(nombre) -> modificarCantidad(cantidad);
				}
			}
		}
	}
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}


void Juego::cerrarEdificios(){

	for(int i = 0; i < this->cantidadEdificios; i++)
		delete this->listaEdificios[i];
   
	delete[] this->listaEdificios;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------


void Juego::leerUbicaciones() {
	ifstream archivoUbicaciones(PATH_UBICACIONES, ios::in);
	if(!archivoUbicaciones.is_open() || isEmpty(archivoUbicaciones))
		partidaNueva = true;
	else {
		partidaNueva = false;
		jugadorActivo = 0;
		colocarMateriales(archivoUbicaciones, mapa);
		colocarJugador(archivoUbicaciones, mapa, 0);
		colocarEdificiosJugador(archivoUbicaciones, this, 0);
		colocarJugador(archivoUbicaciones, mapa, 1);
		colocarEdificiosJugador(archivoUbicaciones, this, 1);
	}
	
	archivoUbicaciones.close();
}


/*
void Juego::cerrarUbicaciones() {

	ofstream archivoUbicaciones(PATH_UBICACIONES);

	for(int i = 0; i < cantidadEdificios; i++){
		for(int j = 0; j < listaEdificios[i] -> obtenerCantConstruidos(); j++){
			
			cout << listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerFila() << " - " << listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerColumna() << endl;
			archivoUbicaciones << this -> listaEdificios[i] -> obtenerTipo() << " ("
								<< listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerFila() << ", "
								<< listaEdificios[i] -> obtenerEdificiosConstruidos(j) -> obtenerColumna() << ')' << '\n';
		}

	}
	cerrarEdificios();
	archivoUbicaciones.close();
}*/

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerMapa() {
	fstream archivoMapa(PATH_MAPA, ios::in);	
	if(!(archivoMapa.is_open())) {
        cout  << "No se pudo abrir el archivo " << PATH_MAPA << endl;
        return;
    }
	int filas, columnas;
	char caracter;
	archivoMapa >> filas;
	archivoMapa >> columnas;
	Mapa *mapa = new Mapa(filas , columnas);
	
	for(int i = 0; i < mapa -> obtenerCantidadFilas(); i++){
		for(int j = 0; j < mapa -> obtenerCantidadColumnas(); j++){

			archivoMapa >> caracter;
			mapa -> agregarCasillero(i, j, caracter);
		}
	}
	
	this->mapa = mapa;
	archivoMapa.close();
}


bool Juego::verificarCoordenadas(int fila, int columna) {
	bool error = false;
	if(fila < 0 || fila > mapa->obtenerCantidadFilas()){
		cout << "La fila ingresada está fuera de rango. No se puede construir el edificio" << endl;
		error = true;
	} else if(columna < 0 || columna > mapa->obtenerCantidadColumnas()){
		cout << "La columna " << columna << " ingresada está fuera de rango. No se puede construir el edificio" << endl;
		error = true;
	} else if (mapa->obtenerCasillero(fila, columna) -> obtenerTipo() != TERRENO){
		cout << "No se puede construir en este tipo de casillero" << endl;
		error = true;
	} else if(mapa->obtenerCasillero(fila, columna)->obtenerCaracter() != CARACTER_VACIO){
		cout << "El casillero (" << fila << "," << columna << ") está ocupado" << endl;
		error = true;
	}	
	return error;
}

//parte de grafos
void Juego::crearVertices(int filas, int columnas) {

	//agrega todos los vertices (todas las coordenadas)
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			string coordX = to_string(j);
			string coordY = to_string(i);
			string coordActual = coordX + ',' + coordY;
			this->grafo->agregarVertice(coordActual);
		}
	}
}

//crear caminos entre cada coordenada
void Juego::crearCaminos() {	

	int filas = this->obtenerMapa()->obtenerCantidadFilas();
	int columnas = this->obtenerMapa()->obtenerCantidadColumnas();
	
	crearVertices(filas, columnas);
	
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			string coordX = to_string(j);
			string coordY = to_string(i);
			string coordActual = coordX + ',' + coordY;
			
			int arribaX = j;
			int arribaY = i - 1;
			string arriba = to_string(arribaX) + ',' + to_string(arribaY);

			int abajoX = j;
			int abajoY = i + 1;
			string abajo = to_string(abajoX) + ',' + to_string(abajoY);

			int izquierdaX = j - 1;
			int izquierdaY = i;
			string izquierda = to_string(izquierdaX) + ',' + to_string(izquierdaY);

			int derechaX = j + 1;
			int derechaY = i;
			string derecha = to_string(derechaX) + ',' +to_string(derechaY);

			if(izquierdaX > 0)
				this->grafo->agregarCamino(coordActual, izquierda, valoresCaminos(izquierdaX, izquierdaY));
				
			if (arribaY > 0)
				this->grafo->agregarCamino(coordActual, arriba, valoresCaminos(arribaX, arribaY));
				
			if(derechaX < columnas)
				this->grafo->agregarCamino(coordActual, derecha, valoresCaminos(derechaX, derechaY));
				
			if(abajoY < filas)
				this->grafo->agregarCamino(coordActual, abajo, valoresCaminos(abajoX, abajoY));
		}
	}
}

int Juego::valoresCaminos(int x, int y) {
	
	char casillero = this->obtenerMapa()->obtenerCasillero(x, y)->obtenerTipo();
 
	if(casillero == 'C')
		return 4;
		
	if((casillero == 'L' && obtenerJugadorActivo() == 0) || (casillero == 'M' && obtenerJugadorActivo() == 1))
		return 2;
	
	if((casillero == 'L' && obtenerJugadorActivo() == 1) || (casillero == 'M' && obtenerJugadorActivo() == 0))
		return 5;	
	
	if(casillero == 'T')
		return 25;
	
	//default: betun
	return 0;
}

void Juego::mostrarCaminoMinimo(string origen, string destino) {
	const char* destino2 = destino.c_str();
	int destinoX = destino2[0] - '0';
	int destinoY = destino2[2] - '0';
	
	if(verificarCoordenadas(destinoX, destinoY)) {
		grafo -> usarDijkstra();
		grafo -> caminoMinimo(origen, destino);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void Juego::lluviaElementos() {
	CasilleroTransitable** casillerosDisponibles = new CasilleroTransitable*[0];
	int transitables = mapa -> casillerosTransitablesVacios(&casillerosDisponibles);
	if (transitables < 3) return;
	int cantidadMateriales[4] = {1, 3, 2 ,1};
	string materiales[5] = {PIEDRA, MADERA, METAL, ANDYCOINS, MATERIAL_NULO};
	string* bolsas = new std::string[3];
	bolsas[0] = bolsas[1] = METAL;
	bolsas[2] = PIEDRA;
	int asignados = 3;
	int orden[4] = {0, 1, 2 ,3};
	shuffleInt(orden, asignados);
	for (int i = 0; i < 5; i++){
		if (asignados < transitables){
			int agregados = i < 4 ? (rand()%(1+cantidadMateriales[orden[i]]))%(1 + transitables) : transitables - asignados;
			string* nuevasBolsas = new std::string[asignados + agregados];
			copy(bolsas, bolsas + asignados , nuevasBolsas);
			for (int j = 0; j < agregados; j++)
				nuevasBolsas[asignados + j] = materiales[i < 4 ? orden[i] : i];
			asignados += agregados;
			bolsas = nuevasBolsas;
		}	
	}
	shuffleString(bolsas, asignados);
	for (int i = 0; i < asignados; i++)
		if (bolsas[i] != MATERIAL_NULO) {
			CasilleroTransitable* casillero = casillerosDisponibles[i];
			casillero -> depositarMaterial(new Material(bolsas[i], valoresLluvia(bolsas[i])));
		}
}

void Juego::modificarEdificio(std::string nombre, string material, int nuevoValor){
	abb -> buscar(nombre) -> modificarMaterial(material, nuevoValor);
}





void Juego::guardarYSalir(){
	cerrarMateriales();
	//cerrarUbicaciones();
	//cerrarMapa();
}
