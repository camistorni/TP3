#include <iostream>

#include "mapa.h"
#include "casilleros/casillero.h"
#include "casilleros/casilleroConstruible/casilleroConstruible.h"
#include "casilleros/casilleroInaccesible/casilleroInaccesible.h"
#include "casilleros/casilleroTransitable/casilleroTransitable.h"
#include "../constantes/constantes.h"
using namespace std;

Mapa::Mapa(int cantFilas, int cantColumnas){
	
	this -> cantidadFilas = cantFilas;
    this -> cantidadColumnas = cantColumnas;
	casilleros = new Casillero**[cantidadFilas];
	for(int i = 0; i < cantidadFilas; i++){
        casilleros[i] = new Casillero* [cantidadColumnas];
    }
}

Mapa::~Mapa(){
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			delete casilleros[i][j];
		}
		delete[] casilleros[i];
	}
	delete [] casilleros;
};

int Mapa::obtenerCantidadFilas(){
    return cantidadFilas;
}

int Mapa::obtenerCantidadColumnas(){
    return cantidadColumnas;
}

char Mapa::tipoCasillero(int fila, int columna){
	return casilleros[fila][columna] -> obtenerTipo();
}

void Mapa::agregarCasillero(int fila, int columna, char caracter){
	if (caracter == LAGO){
		casilleros[fila][columna] = new CasilleroInaccesible();
	}
	else if (caracter == TERRENO){
		casilleros[fila][columna] = new CasilleroConstruible();
	}
	else if (caracter == BETUN){
		casilleros[fila][columna] = new CasilleroBetun();
	}
	else if (caracter == MUELLE){
		casilleros[fila][columna] = new CasilleroMuelle();
	}
	else {
		casilleros[fila][columna] = new CasilleroCamino();
		if (caracter != CAMINO)
			cout << "No leyo bien el caracter" << endl;
	}
}


void Mapa::imprimirMapa(int fila, int columna, int index) {
	cout << casilleros[fila][columna] -> obtenerColor() << "   " << ((index == 1) ? (casilleros[fila][columna] -> obtenerCaracter()) : CARACTER_VACIO) << "   " << END_COLOR;
}

void Mapa::mostrarMapa() {
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < cantidadColumnas; k++) {
				imprimirMapa(i, k, j);
			}
			cout << endl;
		}
	}
}



Casillero* Mapa::obtenerCasillero(int fila, int columna){
	return casilleros[fila][columna];
}


///////////////////////////////////// Revisar cuando vea los edificios ///////////////////////////////////////////////////
/* 
bool Mapa::sePuedeDemoler(int fila, int columna){
	bool esDemolible = false;
	if ( ! casilleros[fila][columna] -> esConstruible() ){
		cout << "NO se puede construir en este casillero pq es un casillero " << casilleros[fila][columna]->obtenerTipo();
		cout << endl;
	}
	else if (  casilleros[fila][columna] -> obtenerTipo() == "-1" ){

		cout << "NO se puede construir en este casillero no hay ningun edificio construido";
	}
	else {
		cout << "El edificio " << casilleros[fila][columna] -> obtenerTipo() << " se derribo con exito";
		esDemolible = true;
	}
	return esDemolible;
}
*/

void Mapa::pedirCoordenada(int &fila, int &columna){
	cout << "Ingrese la fila: ";
	cin >> fila;
	cout << endl;
	cout << "Ingrese la columna: ";
	cin >> columna;
	cout  << endl;
	while (fila > cantidadFilas || fila < 0 || columna > cantidadColumnas || columna < 0){
		cout << "Coordenada incorrecta" << endl;
		cout << "Ingrese la coordenada nuevamente -> fil ( 0 - " << cantidadFilas << ")" << endl;
		cout << "                                 -> col ( 0 - " << cantidadColumnas << ")" << endl;
		cout << "fila ->  ";
		cin >> fila;
		cout << "columna ->  ";
		cin >> columna;
	}

}


