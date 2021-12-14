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

void leerCoordenadas(ifstream& archivoUbicaciones, int* fila, int* columna, string residuo) {
	char aux;
	if(residuo != "") {
		*fila = residuo[1] - '0';
	} else {
		archivoUbicaciones >> aux;
		archivoUbicaciones >> *fila;
		archivoUbicaciones >> aux;
	}
    
    archivoUbicaciones >> *columna;
    archivoUbicaciones >> aux;
}

void guardarCoordenadas(ofstream &archivoUbicaciones, int fila, int columna){
    archivoUbicaciones << " (";
    archivoUbicaciones << fila;
    archivoUbicaciones << ", ";
    archivoUbicaciones << columna;
    archivoUbicaciones << ')';
    archivoUbicaciones << endl;
}

void guardarMateriales(ofstream &archivoUbicaciones, Juego *juego, int fila, int columna){

	if(juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> obtenerCaracter() == CARACTER_MADERA){
		archivoUbicaciones << MADERA;
		guardarCoordenadas(archivoUbicaciones, fila, columna);
	}
	if(juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> obtenerCaracter() == CARACTER_PIEDRA){
		archivoUbicaciones << PIEDRA;
		guardarCoordenadas(archivoUbicaciones, fila, columna);
	}
	if(juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> obtenerCaracter() == CARACTER_METAL){
		archivoUbicaciones << METAL;
		guardarCoordenadas(archivoUbicaciones, fila, columna);
	}
	if(juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> obtenerCaracter() == CARACTER_ANDYCOINS){
		archivoUbicaciones << ANDYCOINS;
		guardarCoordenadas(archivoUbicaciones, fila, columna);
	}
}

void colocarMateriales (ifstream& archivoUbicaciones, Mapa* mapa) {
	cout << "Materiales:" << endl;
	int fila, columna;
	std::string nombre;
	while(archivoUbicaciones >> nombre && nombre != "1"){
    	leerCoordenadas(archivoUbicaciones, &fila, &columna, "");
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
    leerCoordenadas(archivoUbicaciones, &fila, &columna, "");
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
	std::string nombre = "", aux = "";
	while(archivoUbicaciones >> aux && aux != "2") {
		while(aux[0] != '(') {
			nombre = ((nombre == "") ? (aux) : (nombre + " " + aux));
			archivoUbicaciones >> aux;
		}
    	leerCoordenadas(archivoUbicaciones, &fila, &columna, ((aux[0]) != '(' ? NULL : aux));
		Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
		char tipo = casillero -> obtenerTipo();
		if (tipo != TERRENO){
			cout << "No se puede colocar " << nombre << " en el terreno de la posición (" << fila << ", " << columna << ")" << endl;
		} else {
			if (casillero -> obtenerCaracter() != CARACTER_VACIO){
				cout << "No se puede colocar " << nombre << " en la posición (" << fila << ", " << columna << "), esta ya está ocupada "<< endl;
			} else {
				static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> agregarEdifico(nombre, juego);
				cout << "Se agregó " << nombre << " en la posición (" << fila << ", " << columna << ") para el Jugador " << jugador + 1 << endl;
				juego -> obtenerJugador() -> agregarEdificioConstruido(nombre);
			}
		}
		nombre = "", aux = "";
    }
}

void guardarEdificios(ofstream &archivoUbicaciones, Juego *juego, int fila, int columna, int jugador){
	char caracter = juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> obtenerCaracter();
	cout << "propietario: " << static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> obtenerPropietarioEdificio() << endl;
	if(static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> obtenerPropietarioEdificio() == jugador){
		if(caracter == CARACTER_MINA){
			archivoUbicaciones << MINA;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_MINA_ORO){
			archivoUbicaciones << MINA_ORO;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_ASERRADERO){
			archivoUbicaciones << ASERRADERO;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_FABRICA){
			archivoUbicaciones << FABRICA;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_ESCUELA){
			archivoUbicaciones << ESCUELA;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_OBELISCO){
			archivoUbicaciones << OBELISCO;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
		if(caracter == CARACTER_PLANTA_ELECTRICA){
			archivoUbicaciones << PLANTA_ELECTRICA;
			guardarCoordenadas(archivoUbicaciones, fila, columna);
		}
	}	
}

bool isEmpty(ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void escribirNuevoArchivoMateriales() {
	fstream archivoMateriales(PATH_MATERIALES, ios::out);
	archivoMateriales << " " << MADERA << CANTIDAD_CERO << " " << CANTIDAD_CERO << endl;
	archivoMateriales << " " << PIEDRA << CANTIDAD_CERO << " " << CANTIDAD_CERO << endl;
	archivoMateriales << " " << METAL << CANTIDAD_CERO << " " << CANTIDAD_CERO << endl;
	archivoMateriales << " " << ANDYCOINS << CANTIDAD_CERO << " " << CANTIDAD_CERO << endl;
	archivoMateriales << " " << BOMBAS << CANTIDAD_CERO << " " << CANTIDAD_CERO << endl;
}