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
    cout << nombreEdifico << endl;
    
    *materialProducido = this -> materialProducido;
    *cantidadProducida = this -> cantidadProducida;
    cout << "cantidadProducida: " << this -> cantidadProducida << endl;
    return this -> cantidadProducida > 0;
}
