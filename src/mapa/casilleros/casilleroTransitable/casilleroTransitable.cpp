#include <iostream>

#include "../../../materiales/materiales.h"
#include "../../../constantes/constantes.h"
#include "../constantesCasilleros.h"
#include "casilleroTransitable.h"


CasilleroTransitable::~CasilleroTransitable() {
    delete material;
}

CasilleroCamino::CasilleroCamino(){
    setearTipo(CAMINO);
    setearColor(COLOR_CAMINO);
    setearEnergia(ENERGIA_TERRENO);
}
CasilleroBetun::CasilleroBetun(){
    setearTipo(BETUN);
    setearColor(COLOR_BETUN);
    setearEnergia(ENERGIA_BETUN);
}
CasilleroMuelle::CasilleroMuelle(){
    setearTipo(MUELLE);
    setearColor(COLOR_MUELLE);
}

bool CasilleroTransitable::hayMaterialDepositado(){
    return hayMaterial;
}

Material* CasilleroTransitable::recolectarMaterial(){
    setearCaracter(CARACTER_VACIO);
    hayMaterial = false;
    return material;
}

void CasilleroTransitable::depositarMaterial(Material* material) {
    std::string nombre = material -> obtenerNombreMaterial();
    if(nombre == MADERA) setearCaracter(CARACTER_MADERA);
    if(nombre == PIEDRA) setearCaracter(CARACTER_PIEDRA);
    if(nombre == METAL) setearCaracter(CARACTER_METAL);
    if(nombre == ANDYCOINS) setearCaracter(CARACTER_ANDYCOINS);
    hayMaterial = true;
    this -> material = material;
}

int CasilleroMuelle::obtenerEnergia(int jugadorActivo){
    return jugadorActivo ? ENERGIA_MUELLE_JUGADOR_2 : ENERGIA_MUELLE_JUGADOR_1;
}

void CasilleroTransitable::responder() { 
    if(hayMaterial)
        cout << "Soy un casillero transitable y tengo " << material -> obtenerNombreMaterial() << endl;
    else 
        cout << "Soy un casillero transitable y estoy vacio" << endl;
}