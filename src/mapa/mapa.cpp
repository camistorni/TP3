#include <iostream>

#include "mapa.h"
#include "casilleros/casillero.h"
#include "casilleros/casilleroConstruible/casilleroConstruible.h"
#include "casilleros/casilleroInaccesible/casilleroInaccesible.h"
#include "casilleros/casilleroTransitable/casilleroTransitable.h"
#include "../constantes/constantes.h"
#include "casilleros/constantesCasilleros.h"

using namespace std;

// Costructor
Mapa::Mapa(int cantFilas, int cantColumnas){
	
	this -> cantidadFilas = cantFilas;
    this -> cantidadColumnas = cantColumnas;
	casilleros = new Casillero**[cantidadFilas];
	for(int i = 0; i < cantidadFilas; i++){
        casilleros[i] = new Casillero* [cantidadColumnas];
    }
}

// Destructor
Mapa::~Mapa(){
	Casillero* casillero;
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if((casillero = casilleros[i][j]) -> obtenerTipo() == TERRENO)
				delete static_cast<CasilleroConstruible*>(casillero);
			else if(casillero -> obtenerTipo() != LAGO)
				delete static_cast<CasilleroTransitable*>(casillero);
			else 
				delete casillero;
			
		}
		
		delete[] casilleros[i];
	}
	delete [] casilleros;
};


// Getters
int Mapa::obtenerCantidadFilas(){
    return cantidadFilas;
}

int Mapa::obtenerCantidadColumnas(){
    return cantidadColumnas;
}

string Mapa::obtenerPosicionJugador(int jugador) {
	string aux;
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if(casilleros[i][j] -> obtenerJugador() == jugador)
				aux = to_string(i) + "," + to_string(j);
		}
	}
	return aux;
}

void Mapa::obtenerPosicionJugador(int *fila, int *columna, int jugador) {
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if(casilleros[i][j] -> obtenerJugador() == jugador){
				*fila = i;
				*columna = j;
			}
		}
	}
}

char Mapa::tipoCasillero(int fila, int columna){
	return casilleros[fila][columna] -> obtenerTipo();
}

Casillero* Mapa::obtenerCasillero(int fila, int columna){
	return casilleros[fila][columna];
}

int Mapa::casillerosTransitablesVacios(CasilleroTransitable*** casillerosDisponibles){
	int disponibles = 0;
	Casillero* casillero;
	char tipo;
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if(((tipo = (casillero = casilleros[i][j]) -> obtenerTipo()) != TERRENO) &&
				(tipo != LAGO) &&
				(casillero -> obtenerJugador() < 0) &&
				!(static_cast<CasilleroTransitable*>(casillero) -> hayMaterialDepositado())
			){
				CasilleroTransitable** nuevosCasillerosDisponibles = new CasilleroTransitable *[disponibles +1];
  				copy(*casillerosDisponibles, *casillerosDisponibles + disponibles , nuevosCasillerosDisponibles);
  				nuevosCasillerosDisponibles[disponibles] = static_cast<CasilleroTransitable*>(casillero);
  				*casillerosDisponibles = nuevosCasillerosDisponibles;
				disponibles++;
			}
		}
	}
	return disponibles;
}

int Mapa::edificiosContruidos(string nombre, int jugador){
	int construidos = 0;
	Casillero* casillero;
	char tipo;
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if(((tipo = (casillero = casilleros[i][j]) -> obtenerTipo()) == TERRENO) &&
				(static_cast<CasilleroConstruible*>(casillero) -> obtenerPropietarioEdificio() == jugador) &&
				(static_cast<CasilleroConstruible*>(casillero) -> obtenerEdificio() == nombre)
			){
				cout << "Aldu: propietario en edificiosConstruidos: " << static_cast<CasilleroConstruible*>(casillero) -> obtenerPropietarioEdificio() << endl;
				construidos ++;
			}
		}
	}
	return construidos;
}


// Setters
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
			cout << "No leyó bien el caracter" << endl;
	}
}

// Generales
void Mapa::imprimirMapa(int fila, int columna, int index) {
	char caracter = casilleros[fila][columna] -> obtenerCaracter();
	string caracterColor;
	string stringVacio(1, CARACTER_VACIO);
	int jugador = casilleros[fila][columna] -> obtenerJugador();
	int propietario = -1;
	if(static_cast<CasilleroConstruible*>(casilleros[fila][columna]) -> obtenerTipo() == TERRENO)
		propietario = static_cast<CasilleroConstruible*>(casilleros[fila][columna]) -> obtenerPropietarioEdificio();
	char tipoCasillero = casilleros[fila][columna] -> obtenerTipo();

	if(jugador != -1)
		caracterColor = COLOR_NEUTRAL + caracter;
	else if(jugador == 0)
		caracterColor = COLOR_JUGADOR_1 + TXT_BOLD + caracter;
	else if(jugador == 1)
		caracterColor = COLOR_JUGADOR_2 + TXT_BOLD + caracter;
	else if(tipoCasillero == TERRENO && propietario == 0)
		caracterColor = COLOR_JUGADOR_1 + TXT_BOLD + caracter;
	else if(tipoCasillero == TERRENO && propietario == 1)
		caracterColor = COLOR_JUGADOR_2 + TXT_BOLD + caracter;
	else 
		caracterColor = COLOR_NEUTRAL + caracter;

	cout << casilleros[fila][columna] -> obtenerColor() << "   " << ((index == 1) ? caracterColor : stringVacio) <<  "   " << END_COLOR;
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

void Mapa::AlduChequeo() {
	for(int i = 0; i < cantidadFilas; i++) {
		for(int j = 0; j < cantidadColumnas; j++) {
			if(casilleros[i][j] -> obtenerTipo() == TERRENO) {
				int propietario = static_cast<CasilleroConstruible*>(casilleros[i][j]) -> obtenerPropietarioEdificio();
				cout << "Aldu en alduchqueo: i " << i << " j: " << j << " propietario: " << propietario << endl;
			}
		}
	}
}