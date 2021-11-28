#include "jugador.h"

Jugardor::Jugardor() {
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

void Jugardor::asignarMateriales(Material** materialesAsignados) {
    materiales = materialesAsignados;
}

Material* Jugardor::buscarMaterial(string nombreMaterial) {
    Material* material = nullptr;
    int i = 0;
    while (i < 5 || material == nullptr) {
        if (materiales[i] -> obtener_nombre_material() == nombreMaterial)
            material = materiales[i];
    }
    return material;
}

bool Jugardor::comprarAndypolis() {
    return comprarAndypolisCumplido || (comprarAndypolisCumplido = (andycoinsRecolectadas >= 100000));
}
bool Jugardor::edadDePiedra() {
    return edadDePiedraCumplido || (edadDePiedraCumplido = (buscarMaterial("piedra") -> obtener_cantidad_material() >= 50000));
}
bool Jugardor::bombardero() {
    return bombarderoCumplido || (bombarderoCumplido = (bombasUsadas >= 5));
}
bool Jugardor::energetico() {
    return energeticoCumplido || (energeticoCumplido = (energia == 100));
}
bool Jugardor::minero() {
    return mineroCumplido || (mineroCumplido = (minaConstruida && minaOroConstruida));
}
bool Jugardor::cansado() {
    return cansadoCumplido || (cansadoCumplido = (energia == 0));
}
bool Jugardor::constructor() {
    return constructorCumplido || 
        (constructorCumplido = (minaConstruida && aserraderoConstruido && fabricaConstruida && escuelaConstruida && plantaElectricaConstruida && minaOroConstruida));
}
bool Jugardor::armado() {
    return armadoCumplido || (armadoCumplido = (buscarMaterial("bomba") -> obtener_cantidad_material() >= 10));
}
bool Jugardor::extremista() {
    return extremistaCumplido || (extremistaCumplido = (bombasCompradas >= 500));
}