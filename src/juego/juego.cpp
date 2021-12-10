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
#include "../diccionario/ABB.h"
#include "../diccionario/nodo.h"

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

	
	fstream archivoEdificios(PATH_EDIFICIOS, ios::in);

	//Edificio* edificio;
    string lecturaEdificios[CANT_CARACTERISTICAS_EDIFICIOS];


    while (archivoEdificios >> lecturaEdificios[0]){

        archivoEdificios >> lecturaEdificios[1];
        archivoEdificios >> lecturaEdificios[2];
        archivoEdificios >> lecturaEdificios[3];
        archivoEdificios >> lecturaEdificios[4];
		
		
		Parser parser = Parser(lecturaEdificios);
		//edificio = parser.procesarEntrada();
		int *datosEdificios = new int;
		datosEdificios[0] = parser.piedra();
		datosEdificios[1] = parser.madera();
		datosEdificios[2] = parser.metal();
		
		this->abb->insertarNodo(parser.edificio(), datosEdificios);

		//agregarEdificio(edificio);

	}
	
	archivoEdificios.close();
}

bool Juego::verificarEdificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidadMax){
	////////////////Falta cant max y construidos por jugador///////////////
	
	/*
	bool existe = false;
	
	for(int i = 0; i < cantidadEdificios; i++){
		//Verifica que exista el edificio ingresado
		if(this->abb->buscar(nombreIngresado)->obtenerClave() == nombreIngresado){
			*piedraNecesaria = this->abb->buscar(nombreIngresado)->obtenerDatos()[0];
			*maderaNecesaria = this->abb->buscar(nombreIngresado)->obtenerDatos()[1];
			*metalNecesario = this->abb->buscar(nombreIngresado)->obtenerDatos()[2];
			
			*construidos = listaEdificios[i]->obtenerCantConstruidos(); 
			*cantidadMax = listaEdificios[i]->obtenerCantMaxConstruido();
			existe = true;
		}
	}
	
	if(!existe){
		cout << "El edificio '" << nombreIngresado << "' no existe" << endl << endl;
		return false;
	}
	*/
	return true;
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
/////////////////////////// Falta max const y brinda material/////////////////////
	
	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos\tTodavía puede construir\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	
	abb->imprimirTablaOrdenada();
	
	/*long nombreMasLargo = 0;
	long nombre = 0;
	for(int i = 0; i < this -> cantidadEdificios; i++){
		nombre = this->abb->obtenerNodo(i).obtenerClave().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}*/
	
	/*
	for(int i = 0; i < this->cantidadEdificios; i++){
		long espacio = nombreMasLargo - this->abb->obtenerNodo(i).obtenerClave().length();
		cout << "             " << this->abb->obtenerNodo(i).obtenerClave();
		cout << setw(5 + (int)espacio);
		cout << this->abb->obtenerNodo(i).obtenerDatos()[0] << setw(16);
		cout << this->abb->obtenerNodo(i).obtenerDatos()[1] << setw(16);
		cout << this->abb->obtenerNodo(i).obtenerDatos()[2] << setw(23);
		//cout << this -> listaEdificios[i] -> obtenerCantMaxConstruido() - this -> listaEdificios[i] -> obtenerCantConstruidos() << endl;
		
		if(this -> listaEdificios[i] -> brindaMaterial())
			cout << " Sí"  << endl;
		else
			cout << "No" << endl;
	}*/
	cout << endl << endl;
	
}

void Juego::recolectarRecursos(){
	/*
	for(int i = 0; i < this -> cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> brindaMaterial())
			agregarRecursos(this->abb->obtenerNodo(i).obtenerClave());		
	}
	*/
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}


void Juego::cerrarEdificios(){

	for(int i = 0; i < this->cantidadEdificios; i++)
		delete this->listaEdificios[i];
   
	delete[] this->listaEdificios;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------

void leerCoordenadas (ifstream& archivoUbicaciones, int* fila, int* columna) {
	char aux;
    archivoUbicaciones >> aux;
    archivoUbicaciones >> *fila;
    archivoUbicaciones >> aux;
    archivoUbicaciones >> *columna;
    archivoUbicaciones >> aux;
}

void colocarMateriales (ifstream& archivoUbicaciones, Mapa* mapa) {
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

void colocarJugador (ifstream& archivoUbicaciones, Mapa* mapa, int jugador) {
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

void colocarEdificiosJugador (ifstream& archivoUbicaciones, Juego* juego, int jugador) {
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

bool isEmpty(ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

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
	
	if(fila < 0 || fila > mapa->obtenerCantidadFilas()){
		cout << "La fila ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}
	
	if(columna < 0 || columna > mapa->obtenerCantidadColumnas()){
		cout << "La columna " << columna << " ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}
	if(mapa->obtenerCasillero(fila, columna)->obtenerCaracter() != CARACTER_VACIO){
		cout << "El casillero (" << fila << "," << columna << ") está ocupado" << endl;
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

void Juego::cerrarMapa(){

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
bool generarPiedra(Juego* juego, Casillero* casillero) {
	bool generoPiedra = false;
	int cantidadPiedra = rand() % 2 + 1;
	int contadorPiedra = 0;
	string nombre = PIEDRA;
	if(generoPiedra == false) {
		if(casillero -> obtenerCaracter() == CARACTER_VACIO) {
			Material* material = new Material(nombre, LLUVIA_PIEDRA);
			static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
			contadorPiedra++;
			if(contadorPiedra == cantidadPiedra)
				generoPiedra = true;
		}
	}
}

bool generarMadera(Juego* juego, Casillero* casillero) {
	bool generoMadera = false;
	int cantidadMadera = rand() % 3;
	int contadorMadera = 0;
	string nombre = MADERA;
	if(generoMadera == false) {
		if(casillero -> obtenerCaracter() == CARACTER_VACIO) {
			Material* material = new Material(nombre, LLUVIA_PIEDRA);
			static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
			contadorMadera++;
			if(contadorMadera == cantidadMadera)
				generoMadera = true;
		}
	}
}

bool generarMetal(Juego* juego, Casillero* casillero) {
	bool generoMetal = false;
	int cantidadMetal = rand() % 2 + 2;
	int contadorMetal = 0;
	string nombre = METAL;
	if(generoMetal == false) {
		if(casillero -> obtenerCaracter() == CARACTER_VACIO) {
			Material* material = new Material(nombre, LLUVIA_PIEDRA);
			static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
			contadorMetal++;
			if(contadorMetal == cantidadMetal)
				generoMetal = true;
		}
	}
}

bool generarAndycoins(Juego* juego, Casillero* casillero) {
	bool generoAndycoins = false;
	int cantidadAndycoins = rand() % 2;
	int contadorAndycoins = 0;
	string nombre = ANDYCOINS;
	if(generoAndycoins == false) {
		if(casillero -> obtenerCaracter() == CARACTER_VACIO) {
			Material* material = new Material(nombre, LLUVIA_PIEDRA);
			static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
			contadorAndycoins++;
			if(contadorAndycoins == cantidadAndycoins)
				generoAndycoins = true;
		}
	}
	return generoAndycoins;
}
*/

// Esta funcion hace rand para generar la cantidad de bolsas de materiales que haya que poner de cada uno
int generarCantidadMaterial(string nombre) {
	int cantidad = 0;
	if(nombre == PIEDRA)  {
		cantidad = rand() % 2 + 1;
		cout << "Cantidad piedra: " << cantidad << endl;
	}
	else if(nombre == MADERA) {
		cantidad = rand() % 3;
		cout << "Cantidad madera: " << cantidad << endl;
	}
	else if(nombre == METAL) {
		cantidad = rand() % 2 + 2;
		cout << "Cantidad metal: " << cantidad << endl;
	}
		
	else if(nombre == ANDYCOINS) {
		cantidad = rand() % 2;
	}

	return cantidad;
}

// Esta funcion la hice para ver cuantos transitables hay pero no funciona, se traba despues de obtener casilleros
int obtenerCantidadTransitables(Juego* juego) {
	int filas = juego -> obtenerMapa() -> obtenerCantidadFilas();
	int columnas = juego -> obtenerMapa() -> obtenerCantidadColumnas();
	int cantidadDisponibles = 0;
	for(int i = 0; i < filas; i++) {
		for(int j = 0; j < columnas; j++) {
			Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(filas, columnas);
			char tipo = casillero -> obtenerTipo();
			if(tipo == BETUN || tipo == MUELLE || tipo == CAMINO) {
				if(casillero -> obtenerCaracter() == CARACTER_VACIO)
					cantidadDisponibles++;
			}
		}
	}
	return cantidadDisponibles;
}

// Esta funcion es para generar los materiales, depende del nombre que reciba llama a cantidad material
// para ver cuantas bolsas tengo que poner de ese
void generarMaterial(Juego* juego, string nombreMaterial) {
	obtenerCantidadTransitables(juego);
	bool generoMaterial = false;
	int cantidadMaterial = generarCantidadMaterial(nombreMaterial);
	int contadorMaterial = 0;
	
	while(generoMaterial == false) {
		int filRandom = rand() % (juego -> obtenerMapa() -> obtenerCantidadFilas());
		int colRandom = rand() % (juego -> obtenerMapa() -> obtenerCantidadColumnas());
		Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(filRandom,colRandom);
		char tipoCasillero = casillero -> obtenerTipo();
		//cout << "posicion: (" << filRandom << ", " << colRandom << ") tipo casillero : " << tipoCasillero << endl;
		if(tipoCasillero != LAGO && tipoCasillero != TERRENO) {
		//	cout << "Caracter Casillero: " << casillero -> obtenerCaracter() << endl;
			if(casillero -> obtenerCaracter() == CARACTER_VACIO) {
				Material* material = new Material(nombreMaterial, LLUVIA_PIEDRA);
				static_cast<CasilleroTransitable *>(casillero) -> depositarMaterial(material);
				contadorMaterial++;
				if(contadorMaterial == cantidadMaterial)
					generoMaterial = true;
			}
		}
	}
}

// Creo que se esta rompiendo porque pone mas maderas de las que deberia, no entiendo porque
void Juego::lluviaElementos() {
	generarMaterial(this, PIEDRA);
	generarMaterial(this, MADERA);
	generarMaterial(this, METAL);
	generarMaterial(this, ANDYCOINS);
}

void Juego::guardarYSalir(){
	cerrarMateriales();
	//cerrarUbicaciones();
	cerrarMapa();
}
