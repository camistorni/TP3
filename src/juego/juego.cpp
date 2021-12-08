#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "../materiales/materiales.h"
#include "../juego/juego.h"
#include "../edificios/parser.h"
#include "../edificios/edificio.h"
#include "../mapa/casilleros/casillero.h"
#include "../mapa/casilleros/casilleroConstruible/casilleroConstruible.h"
#include "../mapa/casilleros/casilleroInaccesible/casilleroInaccesible.h"
#include "../mapa/casilleros/casilleroTransitable/casilleroTransitable.h"
#include "../constantes/constantes.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

Juego::Juego () {
	jugadores = new Jugador*[2];
	jugadores[0] = new Jugador("Jugador 1");
	jugadores[1] = new Jugador("Jugador 2");
	cantidadMateriales = 0;
	jugadorActivo = -1;
	partidaNueva = false;
	leerMateriales();
	//leerOpcionesEdificios();
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

bool Juego::verificarMateriales(string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario, int construidos, int cantidadMax){
	int error = false;
	if (jugadores[jugadorActivo] -> buscarMaterial("piedra") -> obtenerCantidadMaterial() < piedraNecesaria) {
		imprimirMensajeError(nombreIngresado, "piedra", jugadores[jugadorActivo] -> buscarMaterial("piedra") -> obtenerCantidadMaterial(), piedraNecesaria);
		error = true;
	}
	if (jugadores[jugadorActivo] -> buscarMaterial("madera") -> obtenerCantidadMaterial() < piedraNecesaria) {
		imprimirMensajeError(nombreIngresado, "madera", jugadores[jugadorActivo] -> buscarMaterial("piedra") -> obtenerCantidadMaterial(), piedraNecesaria);
		error = true;
	}
	if (jugadores[jugadorActivo] -> buscarMaterial("metal") -> obtenerCantidadMaterial() < piedraNecesaria) {
		imprimirMensajeError(nombreIngresado, "metal", jugadores[jugadorActivo] -> buscarMaterial("piedra") -> obtenerCantidadMaterial(), piedraNecesaria);
		error = true;
	}
	if(construidos == cantidadMax){
		std::cout << "Se ha llegado a la cantidad máxima permitida de: "<< nombreIngresado << ". (Cantidad máxima = " << cantidadMax << "). No se pueden construir más" << endl;
		error = true;
	}	
	return !error;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerOpcionesEdificios(){
/////////////////////////// Revisar cuando esté el diccionario //////////////77///

	/*
	fstream archivoEdificios(PATH_EDIFICIOS, ios::in);

	Edificio* edificio;
    string lecturaEdificios[CANT_CARACTERISTICAS_EDIFICIOS];


    while (archivoEdificios >> lecturaEdificios[0]){

        archivoEdificios >> lecturaEdificios[1];
        archivoEdificios >> lecturaEdificios[2];
        archivoEdificios >> lecturaEdificios[3];
        archivoEdificios >> lecturaEdificios[4];
		
		
		Parser parser = Parser(lecturaEdificios);
		edificio = parser.procesarEntrada();


		agregarEdificio(edificio);

	}
	
	archivoEdificios.close();
	*/
}

bool Juego::verificarEdificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidadMax){

	//////////////////////////////// Diccionario etc
	/*
	bool existe = false;
	int i = 0;
	while(!existe || i < cantidadEdificios) {
		//Verifica que exista el edificio ingresado
		if(listaEdificios[i]->obtenerTipo() == nombreIngresado){
			*piedraNecesaria = listaEdificios[i]->obtenerPiedra();
			*maderaNecesaria = listaEdificios[i]->obtenerMadera();
			*metalNecesario = listaEdificios[i]->obtenerMetal();
			*construidos = listaEdificios[i]->obtenerCantConstruidos();
			*cantidadMax = listaEdificios[i]->obtenerCantMaxConstruido();
			existe = true;
		}
	}
	*/
	return true;
}

void Juego::listarEdificiosConstruidos(){
/////////////////////////// Revisar cuando esté el diccionario //////////////77///

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
		nombre = listaEdificios[i]->obtenerTipo().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}
	for(int i = 0; i < this ->cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> obtenerCantConstruidos() != 0){
		
			long espacio = nombreMasLargo - listaEdificios[i]->obtenerTipo().length();
			std::cout << "             " << listaEdificios[i]->obtenerTipo();
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

void Juego::agregarEdificio(Edificio* edificio){

    Edificio** nuevaListaEdificios = new Edificio*[(this -> cantidadEdificios) + 1];
    
    
    for (int i = 0; i < (this -> cantidadEdificios); i++){
        nuevaListaEdificios[i] = this -> listaEdificios[i];
    }
    
 
    nuevaListaEdificios[this -> cantidadEdificios] = edificio;

    if (cantidadEdificios != 0){
        delete [] listaEdificios;
    } 
    
    this -> listaEdificios = nuevaListaEdificios;
    this -> cantidadEdificios++;
	
}

void Juego::listarEdificios(){
/////////////////////////// Revisar cuando esté el diccionario //////////////77///

	/*
	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos\tTodavía puede construir\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	
	long nombreMasLargo = 0;
	long nombre = 0;
	for(int i = 0; i < this -> cantidadEdificios; i++){
		nombre = this -> listaEdificios[i] -> obtenerTipo().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}	
	for(int i = 0; i < this->cantidadEdificios; i++){
		long espacio = nombreMasLargo - this -> listaEdificios[i] -> obtenerTipo().length();
		cout << "             " << this -> listaEdificios[i] -> obtenerTipo();
		cout << setw(5 + (int)espacio);
		cout << this -> listaEdificios[i] -> obtenerPiedra() << setw(16);
		cout << this -> listaEdificios[i] -> obtenerMadera() << setw(16);
		cout << this -> listaEdificios[i] -> obtenerMetal() << setw(23);
		cout << this -> listaEdificios[i] -> obtenerCantMaxConstruido() - this -> listaEdificios[i] -> obtenerCantConstruidos() << endl;
	}
	*/
}

void Juego::recolectarRecursos(){
	/*
	for(int i = 0; i < this -> cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> brindaMaterial())
			agregarRecursos(this -> listaEdificios[i] -> obtenerTipo());		
	}
	*/
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void leerCoordenadas (fstream &archivoUbicaciones, int* fila, int* columna) {
	char aux;
    archivoUbicaciones >> aux;
    archivoUbicaciones >> *fila;
    archivoUbicaciones >> aux;
    archivoUbicaciones >> *columna;
    archivoUbicaciones >> aux;
}

void colocarMateriales (fstream &archivoUbicaciones, Mapa* mapa) {
	cout << "Materiales:" << endl;
	int fila, columna;
	std::string nombre;
	while(archivoUbicaciones >> nombre && nombre != "1"){
    	leerCoordenadas(archivoUbicaciones, &fila, &columna);
		Casillero* casillero = mapa -> obtenerCasillero(fila, columna);
		char tipo = casillero -> obtenerTipo();
		if (tipo != CAMINO && tipo != BETUN && tipo != MUELLE){
			cout << "No se puede colocar " << nombre << " en el terreno de la posición (" << fila << ", " << columna << ")" << endl;
		} else {
			if (casillero -> obtenerCaracter() != CARACTER_VACIO){
				cout << "No se puede colocar " << nombre << " en la posición (" << fila << ", " << columna << "), esta ya está ocupada " << endl;
			} else {
				cout << "Se agregó " << nombre << " en la posición (" << fila << ", " << columna << ")" << endl;
				Material* material = new Material(nombre, 1);
				static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
			}
		}
    }
}

void colocarJugador (fstream &archivoUbicaciones, Mapa* mapa, int jugador) {
	int fila, columna;
    leerCoordenadas(archivoUbicaciones, &fila, &columna);
	Casillero* casillero = mapa -> obtenerCasillero(fila, columna);
	if (casillero -> obtenerCaracter() == CARACTER_VACIO){
		cout << "Se colocó al Jugador " << jugador + 1 << " en la posición (" << fila << ", " << columna << ")" << endl;
		casillero -> setearJugador(jugador);
	} else {
		cout << "No se pudo colocar al Jugador " << jugador + 1 << " en la posición (" << fila << ", " << columna << ") ya que esta está ocupada." << endl;
	}
}

void colocarEdificiosJugador (fstream &archivoUbicaciones, Juego* juego, int jugador) {
	int fila, columna;
	std::string nombre;
	while(archivoUbicaciones >> nombre && nombre != "2"){
    	leerCoordenadas(archivoUbicaciones, &fila, &columna);
		Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
		char tipo = casillero -> obtenerTipo();
		if (tipo != TERRENO){
			cout << "No se puede colocar " << nombre << " en el terreno de la posición (" << fila << ", " << columna << ")" << endl;
		} else {
			if (casillero -> obtenerCaracter() != CARACTER_VACIO){
				cout << "No se puede colocar " << nombre << " en la posición (" << fila << ", " << columna << "), esta ya está ocupada "<< endl;
			} else {
				static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> agregarEdifico(nombre, jugador);
				cout << "Se agregó " << nombre << " en la posición (" << fila << ", " << columna << ") para el Jugador " << jugador + 1 << endl;
			}
		}
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerUbicaciones() {
	fstream archivoUbicaciones(PATH_UBICACIONES, ios::in);
	if(!archivoUbicaciones.is_open())
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
}
*/
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

// Falta verificar si hay algo construido para ver si se puede construir un edificio, colocar un material, o 
// posicionar un jugador

bool Juego::verificarCoordenadas(int fila, int columna) {
	
	if(fila < 0 || fila > mapa->obtenerCantidadFilas()){
		cout << "La fila ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}
	
	if(columna < 0 || columna > mapa->obtenerCantidadColumnas()){
		cout << "La columna ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}

	return true;
}

//parte de grafos
void Juego::crearVertices(int filas, int columnas) {

	//agrega todos los vertices (todas las coordenadas)
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			string coordX = to_string(j);
			string coordY = to_string(i);
			string coordActual = coordX + coordY;
			grafo.agregarVertice(coordActual);
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
				grafo.agregarCamino(coordActual, izquierda, valoresCaminos(izquierdaX, izquierdaY));
				
			if (arribaY > 0)
				grafo.agregarCamino(coordActual, arriba, valoresCaminos(arribaX, arribaY));
				
			if(derechaX < columnas)
				grafo.agregarCamino(coordActual, derecha, valoresCaminos(derechaX, derechaY));
				
			if(abajoY < filas)
				grafo.agregarCamino(coordActual, abajo, valoresCaminos(abajoX, abajoY));
		}
	}
}

int Juego::valoresCaminos(int x, int y) {
	
	char casillero = this->obtenerMapa()->obtenerCasillero(x, y)->obtenerCaracter();
 
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
	grafo.usarDijkstra();
	grafo.caminoMinimo(origen, destino);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria){
	cout << "No hay suficiente " << material << "." << endl;
	cout << "Hay " << cantidad << " " << material << " disponibles. Se necesitan "<< cantidadNecesaria << " para construir " << nombre_edificio << endl << endl;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
void Juego::aumentarMaterialesDerrumbe(Edificio* edificio){
	for (int i = 0; i < cantidadMateriales; i++){
		if (material[i] -> obtenerNombreMaterial() == "piedra"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + edificio -> obtenerPiedra());
		}
		else if (material[i] -> obtenerNombreMaterial() == "madera"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + edificio -> obtenerMadera());
		}
		else if (material[i] -> obtenerNombreMaterial() == "metal"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + edificio -> obtenerMetal());
		}
	}
}
*/

/////////////////////////// Revisar cuando esté el diccionario //////////////77///
/* 
void Juego::lluviaElementos(){
	bool generoPiedra = false;
	bool generoMadera = false;
	bool generoMetal = false;
	int cantidadPiedra = 1 + rand() % 2;
	int cantidadMadera =  rand() % 2;
	int cantidadMetal = 2 + rand() % 5;
	int contadorPiedra = 0;
	int contadorMadera = 0;
	int contadorMetal = 0;

	while (!generoMadera || !generoMetal || !generoPiedra){
		int fil_random = rand()% (mapa -> obtenerCantidadFilas());
		int col_random = rand()% (mapa -> obtenerCantidadColumnas());
		if (mapa -> obtenerCasillero(fil_random,col_random) -> esTransitable()){
			if (!generoPiedra){
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("piedra");
				contadorPiedra ++;
				if (cantidadPiedra == contadorPiedra){
					generoPiedra = true;
				}
			}
			else if (!generoMadera){
				if (cantidadMadera == 0){
					generoMadera = true;
				}
				else {
					mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
					mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("madera");
					contadorMadera ++;
				}
			}
			else if (!generoMetal){

				mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("metal");
				contadorMetal ++;
				if (cantidadMetal == contadorMetal){
					generoMetal = true;
				}
			}
		}			
	}
}
*/
