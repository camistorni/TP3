#include <iostream>
#include "jugador.h"
#include "constantesJugador.h"
#include "../constantes/constantes.h"
#include "../edificios/constantesEdificios.h"

using namespace std;

// Constructor
Jugador::Jugador(std::string nombreJugador) {
    nombre = nombreJugador;
    energia = 50;
    andycoinsRecolectadas = bombasCompradas = bombasUsadas = escuelaConstruida = 0;
    minaConstruida =
    aserraderoConstruido =
    fabricaConstruida =
    plantaElectricaConstruida =
    minaOroConstruida =
    obeliscoConstruido =
    masAltoQueLasNubesCumplido =
    comprarAndypolisCumplido = 
    edadDePiedraCumplido = 
    bombarderoCumplido = 
    energeticoCumplido = 
    letradoCumplido = 
    mineroCumplido =
    cansadoCumplido = 
    constructorCumplido = 
    armadoCumplido = 
    extremistaCumplido = false;
    objetivos = new int[3]();
    seleccionarObjetivos();
};

// Destructor
Jugador::~Jugador() {
    delete[] objetivos;
}


// Getters

int Jugador::obtenerEnergia() {
    return energia;
}

int Jugador::obtenerCantidadEscuelasConstruidas() {
    return cantidadEscuelasConstruidas;
}

int Jugador::obtenerCantidadBombasCompradas() {
    return bombasCompradas;
}

int Jugador::obtenerCantidadBombasUsadas() {
    return bombasUsadas;
}

int Jugador::obtenerAndycoinsRecolectadas() {
    return andycoinsRecolectadas;
}
int* Jugador::obtenerObjetivos() {
    return objetivos;
}

Material** Jugador::obtenerMateriales() {
    return materiales;
}


// Setters

void Jugador::establecerEnergia(int cantidadEnergia) {
    energia = cantidadEnergia;
}

void Jugador::modificarEnergia(int energiaAgregada) {
    energia = (energia + energiaAgregada)%(CANTIDAD_MAXIMA_ENERGIA + 1);
}

void Jugador::restarEnergia(int energiaGastada){
	energia -= energiaGastada;
}

void Jugador::seleccionarObjetivos() {
    int objetivosNuevos[3];
    objetivosNuevos[0] = rand() % 10;
    objetivosNuevos[1] = rand() % 10;
    while(objetivosNuevos[1] == objetivosNuevos[0])
        objetivosNuevos[1] = rand() % 10;
    objetivosNuevos[2] = rand() % 10;
    while(objetivosNuevos[2] == objetivosNuevos[0] || objetivosNuevos[2] == objetivosNuevos[1])
        objetivosNuevos[2] = rand() % 10;
    for(int i = 0; i < CANTIDAD_OBJETIVOS; i++) {
        objetivos[i] = objetivosNuevos[i];
    }
}

void Jugador::aumentarBombasCompradas(int cantidad) {
    bombasCompradas += cantidad;
}

void Jugador::aumentarBombasUsadas(int cantidad) {
    bombasUsadas += cantidad;
}


// Generales

void Jugador::agregarMaterial(Material* nuevoMaterial, int cantidadMateriales) {
    Material **vectorMateriales = new Material*[cantidadMateriales + 1];
    copy(materiales, materiales + cantidadMateriales, vectorMateriales);
	vectorMateriales[cantidadMateriales] = nuevoMaterial;
	if(cantidadMateriales != 0){
		delete[] materiales;
	}
    materiales = vectorMateriales;
}

Material* Jugador::buscarMaterial(string nombreMaterial) {
    Material* material = nullptr;
    int i = 0;
    while (i < 5 || material == nullptr) {
        if (materiales[i] -> obtenerNombreMaterial() == nombreMaterial)
            material = materiales[i];
        i++;
    }
    return material;
}


// Objetivos

void Jugador::agregarEdificioConstruido(string edificio){
    if(nombre == MINA) minaConstruida = true;
	if(nombre == ASERRADERO) aserraderoConstruido = true;
	if(nombre == FABRICA) fabricaConstruida = true;
	if(nombre == ESCUELA) escuelaConstruida = true;
	if(nombre == PLANTA_ELECTRICA) plantaElectricaConstruida = true;
    if(nombre == MINA_ORO) minaOroConstruida = true;
}

int Jugador::minasConstruidas(){
    return minaConstruida + minaOroConstruida;
}

int Jugador::edificiosContruidos(){
  return minaConstruida +
        aserraderoConstruido +     
        fabricaConstruida +
        plantaElectricaConstruida +
        minaOroConstruida +
        obeliscoConstruido +
        (escuelaConstruida > 0);
}


bool Jugador::masAltoQueLasNubes() {
    return masAltoQueLasNubesCumplido || (obeliscoConstruido == true);
}

bool Jugador::comprarAndypolis() {
    return comprarAndypolisCumplido || (comprarAndypolisCumplido = (andycoinsRecolectadas >= 100000));
}

bool Jugador::edadDePiedra() {
    return edadDePiedraCumplido || (edadDePiedraCumplido = (buscarMaterial(PIEDRA) -> obtenerCantidadMaterial() >= 50000));
}

bool Jugador::bombardero() {
    return bombarderoCumplido || (bombarderoCumplido = (bombasUsadas >= 5));
}

bool Jugador::energetico() {
    return energeticoCumplido || (energeticoCumplido = (energia == 100));
}

bool Jugador::letrado() {
    return letradoCumplido;
}

void Jugador::letrado(bool cumplido){
    letradoCumplido = cumplido;
}

bool Jugador::minero() {
    return mineroCumplido || (mineroCumplido = (minaConstruida && minaOroConstruida));
}

bool Jugador::cansado() {
    return cansadoCumplido || (cansadoCumplido = (energia == 0));
}

bool Jugador::constructor() {
    return constructorCumplido || 
        (constructorCumplido = (minaConstruida && aserraderoConstruido && fabricaConstruida && escuelaConstruida && plantaElectricaConstruida && minaOroConstruida));
}

bool Jugador::armado() {
    return armadoCumplido || (armadoCumplido = (buscarMaterial(BOMBAS) -> obtenerCantidadMaterial() >= 10));
}

bool Jugador::extremista() {
    return extremistaCumplido || (extremistaCumplido = (bombasCompradas >= 500));
}






