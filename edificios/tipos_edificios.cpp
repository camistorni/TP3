#include <iostream>

#include "tipos_edificios.h"
#include "edificio.h"

using namespace std;

TipoEdificio::TipoEdificio(){
}

TipoEdificio::~TipoEdificio(){
}

//Constructor
TipoEdificio::TipoEdificio (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio){
    this -> tipoEdificio = tipoEdificio;
    cantPiedra = piedra;
    cantMadera = madera;
    cantMetal = metal;
    this -> cantMaxConstruido = cantMaxConstruido;
    cantidadConstruidos = 0;

}



int TipoEdificio::obtenerPiedra(){
    return cantPiedra;
}

int TipoEdificio::obtenerMadera(){
    return cantMadera;
}

int TipoEdificio::obtenerMetal(){
    return cantMetal;
}

int TipoEdificio::obtenerCantMaxConstruido(){
    return cantMaxConstruido;
}

std::string TipoEdificio::obtenerTipo(){
    return tipoEdificio;
}

int TipoEdificio::obtenerCantConstruidos(){
    return cantidadConstruidos;
}

bool TipoEdificio::brindaMaterial(){
	return brindaMateriales;
}
Edificio* TipoEdificio::obetenerEdificiosConstruidos(int posisicionEdificio){
    return edificiosConstruidos[posisicionEdificio];
}


void TipoEdificio::liberarEdificosConstruidos(){
    if (cantidadConstruidos > 0){
        for (int i = 0; i < cantidadConstruidos; i++){
            delete edificiosConstruidos[i];
        }
        delete [] edificiosConstruidos;
    }
}

void TipoEdificio::agregarEdificioConstruido(Edificio* edificio){

    Edificio** nuevoEdificiosConstruidos = new Edificio* [cantidadConstruidos + 1];

    for (int i = 0; i < cantidadConstruidos; i++){
        nuevoEdificiosConstruidos[i] = edificiosConstruidos[i];
    }

    nuevoEdificiosConstruidos[cantidadConstruidos] = edificio;

    if (cantidadConstruidos != 0){
        delete [] edificiosConstruidos;
    }

    this -> edificiosConstruidos = nuevoEdificiosConstruidos;
    this -> cantidadConstruidos++;
}

void TipoEdificio::derribarEdificioConstruido(int fila, int columna){
    if (cantidadConstruidos > 1){
        Edificio** nuevoEdificiosConstruidos = new Edificio* [cantidadConstruidos - 1];

        int posicion = 0;
        while (fila != edificiosConstruidos[posicion] -> obtenerFila() && columna != edificiosConstruidos[posicion] -> obtenerColumna()){
            posicion++;
        }
        
        Edificio* aux = edificiosConstruidos[posicion];
        edificiosConstruidos[posicion] = edificiosConstruidos[cantidadConstruidos];
        edificiosConstruidos[cantidadConstruidos] = aux;

        for (int i = 0; i < (cantidadConstruidos - 1); i++){
            nuevoEdificiosConstruidos[i] = edificiosConstruidos [i];
        }
        delete edificiosConstruidos [cantidadConstruidos - 1];
        delete [] edificiosConstruidos;

        edificiosConstruidos = nuevoEdificiosConstruidos;
    }
    else {
        delete edificiosConstruidos [cantidadConstruidos - 1];
        delete [] edificiosConstruidos;
    
    }
    cantidadConstruidos--;


}
