#include <iostream>

#include "mapa.h"
#include "casilleros/casillero.h"
#include "casilleros/casilleroConstruible.h"
#include "casilleros/casilleroInaccesible.h"
#include "casilleros/casilleroTransitable.h"
#include "constantes.h"
using namespace std;

Mapa::Mapa(){
	cantidadFilas = 0;
	cantidadColumnas = 0;
}

void Mapa::inicializarMapa(int cantFilas, int cantColumnas){
	
	this -> cantidadFilas = cantFilas;
    this -> cantidadColumnas = cantColumnas;
	
	casilleros = new Casillero**[cantidadFilas];

	
	for(int i = 0; i < cantidadFilas; i++){
        casilleros[i] = new Casillero* [cantidadColumnas];
    }
    		
}

int Mapa::obtenerCantidadFilas(){
    return cantidadFilas;
}

int Mapa::obtenerCantidadColumnas(){
    return cantidadColumnas;
}

Casillero* Mapa::tipoCasillero(int fila, int columna){
	return casilleros[fila][columna];
}

Casillero* Mapa::identificarCasillero(int fila, int columna, char caracter){
	Casillero* casillero;
	if (caracter == 'L'){
		casillero = new CasilleroInaccesible(fila, columna, caracter);
	}
	else if (caracter == 'T'){
		casillero = new CasilleroConstruible(fila, columna, caracter);
	}
	else if (caracter == 'C'){
		casillero = new CasilleroTransitable(fila, columna, caracter);
	}
	else {
		cout << "NO leyo bien el caracter" << endl;
	}
	return casillero;
}

void Mapa::agregarCasillero(Casillero* casillero){
    casilleros[casillero -> obtenerFila()][casillero -> obtenerColumna()] = casillero;
}


void Mapa::identificarContenido (Casillero* casillero){
	if (casillero -> esConstruible()){
		if (casillero -> obtenerTipo() == "aserradero"){
			casillero -> establecerCaracterContenido("\033[1;41mA\033[0m");
		}
		else if (casillero -> obtenerTipo() == "mina"){
			casillero -> establecerCaracterContenido("\033[1;41mM\033[0m");
		}
		else if (casillero -> obtenerTipo() == "fabrica"){
			casillero -> establecerCaracterContenido("\033[1;41mF\033[0m");
		}
		else if (casillero -> obtenerTipo() == "escuela"){
			casillero -> establecerCaracterContenido("\033[1;41mE\033[0m");
		}

		else if (casillero -> obtenerTipo() == "obelisco"){
			casillero -> establecerCaracterContenido("\033[1;41mO\033[0m");
		}
		else if (casillero -> obtenerTipo() == "plantaElectrica"){
			casillero -> establecerCaracterContenido("\033[1;41mP\033[0m");
		}
	
	}
	else if (casillero -> esTransitable()){
		if (casillero -> obtenerTipo() == "madera"){
			casillero -> establecerCaracterContenido("\033[1;41mW\033[0m");
		}
		else if (casillero -> obtenerTipo() == "piedra"){
			casillero -> establecerCaracterContenido("\033[1;41mS\033[0m");
		}
		else if (casillero -> obtenerTipo() == "metal"){
			casillero -> establecerCaracterContenido("\033[1;41mI\033[0m");
		}
	}
}



void Mapa::mostrarMapa(){

	for(int i = 0; i < cantidadFilas; i++){
		for(int j = 0; j < cantidadColumnas; j++){
            identificarContenido(casilleros[i][j]);
			cout << casilleros[i][j] -> obtenerCaracterContenido();
		}
		cout << endl;
	}
	cout << endl;

}

Casillero* Mapa::obtenerCasillero(int fila, int columna){
	return casilleros[fila][columna];
}

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


void Mapa::pedirCoordenada(int &fila, int &columna){
	cout << "Ingrese la fila: ";
	cin >> fila;
	cout << endl;
	cout << "Ingrese la columna: ";
	cin >> columna;
	cout  << endl;
	while (fila > cantidadFilas || fila < 0 || columna > cantidadColumnas || columna < 0){
		cout << "Coordenada incorrecta" << endl;
		cout << "Ingrese la coordenada nuevamente -> fil (" << cantidadFilas << " - 0)" << endl;
		cout << "                                 -> col (" << cantidadColumnas << " - 0)" << endl;
		cout << "fila ->  ";
		cin >> fila;
		cout << "columna ->  ";
		cin >> columna;
	}

}


Mapa::~Mapa(){

    for (int i = 0; i < cantidadFilas; i ++){
        for (int j = 0; j < cantidadColumnas; j ++){
            delete casilleros[i][j];
        }
        delete [] casilleros [i];
    }
    delete [] casilleros;
}
