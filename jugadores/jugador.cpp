#include "jugador.h"
#include "constantesJugador.h"

using namespace std;

Jugador::Jugador(std::string nombreJugador) {
    nombre = nombreJugador;
    edificiosContruidos; new std::string * [0];
    energia = 50;
    andycoinsRecolectadas = bombasCompradas = bombasUsadas = 0;

    int objetivosAux[10]={0,1,2,3,4,5,6,7,8,9};
  

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
};


Jugador::~Jugador() {}

int Jugador::obtenerEnergia() {
    return energia;
}

int* Jugador::obtenerObjetivos() {
    return objetivos;
}

Material** Jugador::obtenerMateriales() {
    return materiales;
}

void Jugador::establecerEnergia(int cantidadEnergia) {
    energia = cantidadEnergia;
}

void Jugador::establecerCoordenadas(int fila, int columna) {
    this->ubicacion[0] = fila;
    this->ubicacion[1] = columna;
}

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
    }
    return material;
}

bool Jugador::comprarAndypolis() {
    return comprarAndypolisCumplido || (comprarAndypolisCumplido = (andycoinsRecolectadas >= 100000));
}

bool Jugador::edadDePiedra() {
    return edadDePiedraCumplido || (edadDePiedraCumplido = (buscarMaterial("piedra") -> obtenerCantidadMaterial() >= 50000));
}

bool Jugador::bombardero() {
    return bombarderoCumplido || (bombarderoCumplido = (bombasUsadas >= 5));
}

bool Jugador::energetico() {
    return energeticoCumplido || (energeticoCumplido = (energia == 100));
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
    return armadoCumplido || (armadoCumplido = (buscarMaterial("bomba") -> obtenerCantidadMaterial() >= 10));
}

bool Jugador::extremista() {
    return extremistaCumplido || (extremistaCumplido = (bombasCompradas >= 500));
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

    for(int i = 0; i < CANTIDAD_OBJETIVOS; i++)
        objetivos[i] = objetivosNuevos[i];
}

