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

void Edificio::recolectarMateriales(std::string* materialProducido, int* cantidadProducida){
    *materialProducido = this -> materialProducido;
    *cantidadProducida = this -> cantidadProducida;
}
