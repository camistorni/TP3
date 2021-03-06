#include <iostream>

#include "casilleroConstruible.h"
#include "../constantesCasilleros.h"
#include "../../../constantes/constantes.h"
using namespace std;

CasilleroConstruible::CasilleroConstruible() {
    setearTipo(TERRENO);
    setearColor(COLOR_TERRENO);
    setearEnergia(ENERGIA_TERRENO);
}

CasilleroConstruible::~CasilleroConstruible() {
    if(propietarioEdificio > -1)
        delete edificio;
    if(material != NULL)
        delete material;
}

std::string CasilleroConstruible::obtenerEdificio(){
    return edificio -> obtenerTipo();
}

bool CasilleroConstruible::recolectar(std::string* materialProducido, int* cantidadProducida, int jugador){
    return propietarioEdificio != jugador ? false : edificio -> recolectarMateriales(materialProducido, cantidadProducida);
}

void CasilleroConstruible::responder(){
    if (estadoEdificio){
        cout << "Soy un casillero construible y tengo construido un/a " << obtenerEdificio() << endl;
    }
    else {
        cout << "Soy un casillero construible vacio" << endl;
    }
}

void CasilleroConstruible::depositarMaterial(Material* material) {
    std::string nombre = material -> obtenerNombreMaterial();
    if(nombre == MADERA) setearCaracter(CARACTER_MADERA);
    if(nombre == PIEDRA) setearCaracter(CARACTER_PIEDRA);
    if(nombre == METAL) setearCaracter(CARACTER_METAL);
    this -> material = material;
}

int CasilleroConstruible::obtenerPropietarioEdificio() {
    return propietarioEdificio;
}

void CasilleroConstruible::agregarEdifico(std::string nombre, Juego* juego){
    estadoEdificio = 2;
    propietarioEdificio = juego -> obtenerJugadorActivo();
    if (nombre == ASERRADERO) {
        edificio = new Aserradero();
        setearCaracter(CARACTER_ASERRADERO);
    } else if (nombre == ESCUELA) {
        edificio = new Escuela();
        setearCaracter(CARACTER_ESCUELA);
    } else if (nombre == FABRICA) {
        edificio = new Fabrica();
        setearCaracter(CARACTER_FABRICA);
    } else if (nombre == MINA) {
        edificio = new Mina();
        setearCaracter(CARACTER_MINA);
    } else if (nombre == MINA_ORO) {
        edificio = new MinaOro();
        setearCaracter(CARACTER_MINA_ORO);
    } else if (nombre == OBELISCO) {
        edificio = new Obelico();
        setearCaracter(CARACTER_OBELISCO);
    } else if (nombre == PLANTA_ELECTRICA) {
        edificio = new PlantaElectrica();
        setearCaracter(CARACTER_PLANTA_ELECTRICA);
    }
}

bool CasilleroConstruible::atacarEdificio() {
    string tipo = edificio -> obtenerTipo();
    estadoEdificio -= ((tipo == MINA || tipo == FABRICA) ? 1 : 2);
    if(estadoEdificio == 0) {
        setearCaracter(CARACTER_VACIO);
        delete edificio;
    }
    return estadoEdificio > 0;
}

bool CasilleroConstruible::repararEdificio() {
    string tipo = edificio -> obtenerTipo();
    estadoEdificio -= ((tipo == MINA || tipo == FABRICA) ? 1 : 2);
    if(estadoEdificio == 1)
        estadoEdificio = 2;

    return estadoEdificio;
}

void CasilleroConstruible::demolerEdificio() {
    propietarioEdificio = -1;
    setearCaracter(CARACTER_RECURSOS);
    delete edificio;
}