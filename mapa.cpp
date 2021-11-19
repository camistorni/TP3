#include <iostream>

#include "mapa.h"
#include "casilleros/casillero.h"
#include "casilleros/casillero_construible.h"
#include "casilleros/casillero_inaccesible.h"
#include "casilleros/casillero_transitable.h"

using namespace std;

const char TERRENO = 'T';
const char LAGO = 'L';
const char CAMINO = 'C';

Mapa::Mapa(){
	cantidad_filas = 0;
	cantidad_columnas = 0;
}

void Mapa::inicializar_mapa(int cant_filas, int cant_columnas){
	
	this -> cantidad_filas = cant_filas;
    this -> cantidad_columnas = cant_columnas;
	
	casilleros = new Casillero**[cantidad_filas];

	
	for(int i = 0; i < cantidad_filas; i++){
        casilleros[i] = new Casillero* [cantidad_columnas];
    }
    		
}

int Mapa::obtener_cantidad_filas(){
    return cantidad_filas;
}
int Mapa::obtener_cantidad_columnas(){
    return cantidad_columnas;
}

Casillero* Mapa::tipo_casillero(int fila, int columna){
	return casilleros[fila][columna];
}

Casillero* Mapa::identificar_casillero(int fila, int columna, char caracter){
	Casillero* casillero;
	if (caracter == 'L'){
		casillero = new Casillero_inaccesible(fila, columna, caracter);
	}
	else if (caracter == 'T'){
		casillero = new Casillero_construible(fila, columna, caracter);
	}
	else if (caracter == 'C'){
		casillero = new Casillero_transitable(fila, columna, caracter);
	}
	else {
		cout << "NO leyo bien el caracter" << endl;
	}
	return casillero;
}

void Mapa::agregar_casillero(Casillero* casillero){
    casilleros[casillero -> obtener_fila()][casillero -> obtener_columna()] = casillero;
}


void Mapa::identificar_contenido (Casillero* casillero){
	if (casillero -> es_construible()){
		if (casillero -> obtener_tipo() == "aserradero"){
			casillero -> establecer_caracter_contenido("\033[1;41mA\033[0m");
		}
		else if (casillero -> obtener_tipo() == "mina"){
			casillero -> establecer_caracter_contenido("\033[1;41mM\033[0m");
		}
		else if (casillero -> obtener_tipo() == "fabrica"){
			casillero -> establecer_caracter_contenido("\033[1;41mF\033[0m");
		}
		else if (casillero -> obtener_tipo() == "escuela"){
			casillero -> establecer_caracter_contenido("\033[1;41mE\033[0m");
		}

		else if (casillero -> obtener_tipo() == "obelisco"){
			casillero -> establecer_caracter_contenido("\033[1;41mO\033[0m");
		}
		else if (casillero -> obtener_tipo() == "planta_electrica"){
			casillero -> establecer_caracter_contenido("\033[1;41mP\033[0m");
		}
	
	}
	else if (casillero -> es_transitable()){
		if (casillero -> obtener_tipo() == "madera"){
			casillero -> establecer_caracter_contenido("\033[1;41mW\033[0m");
		}
		else if (casillero -> obtener_tipo() == "piedra"){
			casillero -> establecer_caracter_contenido("\033[1;41mS\033[0m");
		}
		else if (casillero -> obtener_tipo() == "metal"){
			casillero -> establecer_caracter_contenido("\033[1;41mI\033[0m");
		}
	}
}



void Mapa::mostrar_mapa(){

	for(int i = 0; i < cantidad_filas; i++){
		for(int j = 0; j < cantidad_columnas; j++){
            identificar_contenido(casilleros[i][j]);
			cout << casilleros[i][j] -> obtener_caracter_contenido();
		}
		cout << endl;
	}
	cout << endl;

}

Casillero* Mapa::obtener_casillero(int fila, int columna){
	return casilleros[fila][columna];
}

bool Mapa::se_puede_demoler(int fila, int columna){
	bool es_demolible = false;

	if ( ! casilleros[fila][columna] -> es_construible() ){

		cout << "NO se puede construir en este casillero pq es un casillero " << casilleros[fila][columna]->obtener_tipo();
		cout << endl;
	}
	else if (  casilleros[fila][columna] -> obtener_tipo() == "-1" ){

		cout << "NO se puede construir en este casillero no hay ningun edificio construido";
	}
	else {
		cout << "El edificio " << casilleros[fila][columna] -> obtener_tipo() << " se derribo con exito";
		es_demolible = true;
	}
	return es_demolible;
}


void Mapa::pedir_coordenada(int &fila, int &columna){
	std::cout << "Ingrese la fila: ";
	std::cin >> fila;
	std::cout << std::endl;
	std::cout << "Ingrese la columna: ";
	std::cin >> columna;
	std::cout  << std::endl;
	while (fila > cantidad_filas || fila < 0 || columna > cantidad_columnas || columna < 0){
		cout << "Coordenada incorrecta" << endl;
		cout << "Ingrese la coordenada nuevamente -> fil (" << cantidad_filas << " - 0)" << endl;
		cout << "                                 -> col (" << cantidad_columnas << " - 0)" << endl;
		cout << "fila ->  ";
		cin >> fila;
		cout << "columna ->  ";
		cin >> columna;
	}

}


void Mapa::liberar_casilleros(){

    for (int i = 0; i < cantidad_filas; i ++){
        for (int j = 0; j < cantidad_columnas; j ++){
            delete casilleros[i][j];
        }
        delete [] casilleros [i];
    }
    delete [] casilleros;
}
