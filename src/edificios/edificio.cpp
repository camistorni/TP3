#include <iostream>

#include "edificio.h"

using namespace std;

//Constructor
Edificio::Edificio(){
   
};

Edificio::~Edificio(){}

std::string Edificio::obtenerTipo(){
    return nombreEdifico;
}

bool Edificio::recolectarMateriales(std::string* materialProducido, int* cantidadProducida){
    *materialProducido = this -> materialProducido;
    *cantidadProducida = this -> cantidadProducida;
    return this -> cantidadProducida > 0;
}

void Edificio::setearNombreEdificio(std::string nombreEdifico){
    this -> nombreEdifico = nombreEdifico;
}

void Edificio::setearMaterialProducido(std::string materialProducido){
    this -> materialProducido = materialProducido;
}

void Edificio::setearCantidadProducida(int cantidadProducida){
    this -> cantidadProducida = cantidadProducida;
}

PlantaElectrica::PlantaElectrica(){
    setearNombreEdificio(PLANTA_ELECTRICA);
    setearMaterialProducido(ENERGIA);
    setearCantidadProducida(PRODUCCION_PLANTA_ELECTRICA);
}

MinaOro::MinaOro(){
    setearNombreEdificio(MINA_ORO);
    setearMaterialProducido(ANDYCOINS);
    setearCantidadProducida(PRODUCCION_MINA_ORO);
}

Mina::Mina(){
    setearNombreEdificio(MINA);
    setearMaterialProducido(PIEDRA);
    setearCantidadProducida(PRODUCCION_MINA);
}

Fabrica::Fabrica(){
    setearNombreEdificio(FABRICA);
    setearMaterialProducido(METAL);
    setearCantidadProducida(PRODUCCION_FABRICA);
}

Escuela::Escuela(){
    setearNombreEdificio(ESCUELA);
    setearMaterialProducido(ANDYCOINS);
    setearCantidadProducida(PRODUCCION_ESCUELA);
}

Aserradero::Aserradero(){
    setearNombreEdificio(ASERRADERO);
    setearMaterialProducido(MADERA);
    setearCantidadProducida(PRODUCCION_ASERRADERO);
}