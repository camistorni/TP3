#include <fstream>
#include "utils.h"
#include "../../mapa/casilleros/casilleroConstruible/casilleroConstruible.h"


void shuffleString(string* vector, int largo){
	for (int i = 0; i < largo; i++)
		swap(vector[i], vector[rand()%largo]);
}

void shuffleInt(int* vector, int largo){
	for (int i = 0; i < largo; i++)
		swap(vector[i], vector[rand()%largo]);
}

int valoresLluvia(string material){
	int valor;
	if(material == PIEDRA){
		valor = 100;
	} else if(material == MADERA){
		valor = 50;
	} else if(material == METAL){
		valor = 50;
	} else if(material == ANDYCOINS){
		valor = 250;
	}
	return valor;
}

void imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria){
	cout << "No hay suficiente " << material << "." << endl;
	cout << "Hay " << cantidad << " " << material << " disponibles. Se necesitan "<< cantidadNecesaria << " para construir " << nombre_edificio << endl << endl;
};

void leerCoordenadas(ifstream& archivoUbicaciones, int* fila, int* columna) {
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

bool isEmpty(ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}