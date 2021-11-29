#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "materiales.h"
#include "juego.h"
#include "edificios/edificio.h"
#include "edificios/tiposEdificios.h"
#include "edificios/parser.h"
#include "edificios/edificio.h"
#include "casilleros/casillero.h"
#include "casilleros/casilleroConstruible.h"
#include "casilleros/casilleroInaccesible.h"
#include "casilleros/casilleroTransitable.h"
#include "constantes.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

Juego::Juego () {
	Jugador* jugadoresAux[2] = {new Jugador("Jugador 1"), new Jugador("Jugador 2")};
	jugadores = jugadoresAux;
	cantidadMateriales = 0;
	jugadorActivo = -1;
	leerMateriales();
	leerOpcionesEdificios();
	leerMapa();
	leerUbicaciones();
}

Juego::~Juego(){
	cerrarMateriales();
	cerrarUbicaciones();
	cerrarMapa();
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

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerMateriales(){

	fstream archivoMateriales(PATH_MATERIALES, ios::in);
	
	Material *material;
	string nombre, cantidadMaterialJugador1, cantidadMaterialJugador2;
	
	while(archivoMateriales >> nombre){
		archivoMateriales >> cantidadMaterialJugador1;
		archivoMateriales >> cantidadMaterialJugador2;
		
		material = new Material;
		*material = Material(nombre, stoi(cantidadMaterialJugador1));

		jugadores[0] -> agregarMaterial(material, cantidadMateriales);

		material = new Material;
		*material = Material(nombre, stoi(cantidadMaterialJugador2));

		jugadores[1] -> agregarMaterial(material, cantidadMateriales);
		cantidadMateriales ++;
	}
	
	archivoMateriales.close();
}

void Juego::cerrarMateriales(){

	ofstream archivoMateriales(PATH_MATERIALES);
	
	for(int i = 0; i < this -> jugadores[0] -> obtenerCantidadMateriales(); i++){
		archivoMateriales << this -> jugadores[0] -> obtenerMaterial(i).obtenerNombreMaterial() << ' ' << 
		this -> jugadores[0] -> obtenerMaterial(i).obtenerCantidadMaterial() << " " << 
		this -> jugadores[1] -> obtenerMaterial(i).obtenerCantidadMaterial() << endl;

		//delete this -> jugadores[0] -> obtenerMaterial(i);
		//delete this -> jugadores[1] -> obtenerMaterial(i);
	}
	
	//delete[] this -> jugadores[0] -> obtenerMateriales();
	// this -> jugadores[0] -> establecerMateriales() = nullptr;
	//delete[] this -> jugadores[1] -> obtenerMateriales();
	
}

bool Juego::verificarMateriales(string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario, int construidos, int cantidadMax){
	int error = false;
	int i = 0;
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
	
	fstream archivoEdificios(PATH_EDIFICIOS, ios::in);

	TipoEdificio* tipoEdificio;
    string lecturaEdificios[CANT_CARACTERISTICAS_EDIFICIOS];


    while (archivoEdificios >> lecturaEdificios[0]){

        archivoEdificios >> lecturaEdificios[1];
        archivoEdificios >> lecturaEdificios[2];
        archivoEdificios >> lecturaEdificios[3];
        archivoEdificios >> lecturaEdificios[4];
		
		
		Parser parser = Parser(lecturaEdificios);
		tipoEdificio = parser.procesarEntrada();


		agregarTipoEdificio(tipoEdificio);

	}
	
	archivoEdificios.close();
}

bool Juego::verificarEdificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidadMax){
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
	return existe;
}

void Juego::listarEdificiosConstruidos(){

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

}

void Juego::agregarTipoEdificio(TipoEdificio* tipoEdificio){

    TipoEdificio** nuevaListaEdificios = new TipoEdificio*[(this -> cantidadEdificios) + 1];
    
    
    for (int i = 0; i < (this -> cantidadEdificios); i++){
        nuevaListaEdificios[i] = this -> listaEdificios[i];
    }
    
 
    nuevaListaEdificios[this -> cantidadEdificios] = tipoEdificio;

    if (cantidadEdificios != 0){
        delete [] listaEdificios;
    } 
    
    this -> listaEdificios = nuevaListaEdificios;
    this -> cantidadEdificios++;
	
}

void Juego::listarEdificios(){

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
}

void Juego::agregarRecursos(string nombreEdificio){
	
	if(nombreEdificio == "mina"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "piedra")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(PIEDRA_AGREGADA_POR_MINA);
		}
	}
		
	if(nombreEdificio == "aserradero"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "madera")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(MADERA_AGREGADA_POR_ASERRADERO);
		}		
	}
	
	if(nombreEdificio == "fabrica"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "metal")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(METAL_AGREGADO_POR_FABRICA);
		}		
	}

	if(nombreEdificio == "escuela") {
		for(int i = 0; i < cantidadMateriales; i++) {
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "andycoins")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(ANDYCOINS_AGREGADAS_POR_ESCUELA);
		}
	}

	if(nombreEdificio == "planta electrica") {
		for(int i = 0; i < cantidadMateriales; i++) {
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "energia")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(ENERGIA_AGREGADA_POR_PLANTA_ELECTRICA);
		}
	}

	if(nombreEdificio == "mina oro") {
		for(int i = 0; i < cantidadMateriales; i++) {
			if(this -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() == "andycoins")
				this -> obtenerJugador() -> obtenerMateriales()[i] -> modificarCantidad(ANDYCOINS_AGREGADAS_POR_MINA_ORO);
		}
	}
}

void Juego::recolectarRecursos(){
	for(int i = 0; i < this -> cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> brindaMaterial())
			agregarRecursos(this -> listaEdificios[i] -> obtenerTipo());		
	}
	
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}

void Juego::cerrarEdificios(){
	
	for(int i = 0; i < this -> cantidadEdificios; i++){
		listaEdificios[i] -> liberarEdificosConstruidos();
		delete this -> listaEdificios[i];
	}
   
	delete[] this -> listaEdificios;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
void Juego::leerUbicaciones(){

	fstream archivoUbicaciones(PATH_UBICACIONES, ios::in);
	Edificio* edificio;
	
	int posicion_edificio;

	char caracter;
	int fila = '0';
	int columna = '0';
	string tipoEdificio;
	
	while(archivoUbicaciones >> tipoEdificio){
		archivoUbicaciones >> caracter;
		archivoUbicaciones >> fila;
		archivoUbicaciones >> caracter;
		archivoUbicaciones >> columna;
		archivoUbicaciones >> caracter;


		edificio  = new Edificio (fila , columna);
		posicion_edificio = identificarEdificio(tipoEdificio);

		listaEdificios[posicion_edificio] -> agregarEdificioConstruido(edificio);
		mapa -> obtenerCasillero(fila, columna) -> establecerTipo(tipoEdificio);


	}
	archivoUbicaciones.close();
}
*/
int Juego::identificarEdificio(string tipoEdficio){

	int posicionEdificio = 0;
	while (listaEdificios[posicionEdificio] -> obtenerTipo() != tipoEdficio){

		posicionEdificio++;
	}
	
	return posicionEdificio;
}

void Juego::cerrarUbicaciones(){

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

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::leerMapa(){
	
	fstream archivoMapa(PATH_MAPA, ios::in);
	Casillero* casillero;
	Mapa *mapa = new Mapa();

	int filas = '0';
	int columnas = '0';
	char caracter;
	archivoMapa >> filas;
	archivoMapa >> columnas;
	
	mapa -> inicializarMapa(filas , columnas);

	
	for(int i = 0; i < mapa -> obtenerCantidadFilas(); i++){
		for(int j = 0; j < mapa -> obtenerCantidadColumnas(); j++){

			archivoMapa >> caracter;
			casillero = mapa -> identificarCasillero (i, j, caracter);
			mapa -> agregarCasillero(casillero);
		}
	}
	
	this->mapa = mapa;
	archivoMapa.close();
}

bool Juego::verificarCoordenadas(int fila, int columna){
	
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

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::guardarYSalir(){
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void Juego::imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria){
	cout << "No hay suficiente " << material << "." << endl;
	cout << "Hay " << cantidad << " " << material << " disponibles. Se necesitan "<< cantidadNecesaria << " para construir " << nombre_edificio << endl << endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
void Juego::aumentarMaterialesDerrumbe(TipoEdificio* tipoEdificio){
	for (int i = 0; i < cantidadMateriales; i++){
		if (material[i] -> obtenerNombreMaterial() == "piedra"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerPiedra());
		}
		else if (material[i] -> obtenerNombreMaterial() == "madera"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerMadera());
		}
		else if (material[i] -> obtenerNombreMaterial() == "metal"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerMetal());
		}
	}
}
*/
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
