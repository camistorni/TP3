#include <iostream>

#include "casillero.h"
#include "casilleroConstruible.h"
#include "constantesCasilleros.h"


CasilleroConstruible::CasilleroConstruible(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracterColor = COLOR_TERRENO;
    tipo = "construible";
    this -> tipoEdificio = "-1";
    caracterContenido = CARACTER_COLOR_TERRENO;
}
std::string CasilleroConstruible::obtenerTipo(){
    return tipoEdificio;
}
void CasilleroConstruible::establecerTipo(std::string nombre_tipo){
    tipoEdificio = nombre_tipo;
}
int CasilleroConstruible::obtenerCantidadMaterial(){
    return -1;
}
void CasilleroConstruible::liberar(){
    tipoEdificio = "-1";
}
void CasilleroConstruible::responder(){
    if (tipoEdificio != "-1"){
        std::cout << "Soy un casillero construible y tengo construido un " << tipoEdificio;
        std::cout << std::endl;
    }
    else {
        std::cout << "Soy un casillero construible vacio" << std::endl;
    }
}
void CasilleroConstruible::establecerCaracterContenido(std::string caracter){
    caracterContenido = caracter;
}
std::string CasilleroConstruible::obtenerCaracterContenido(){
    return caracterContenido;
}
void CasilleroConstruible::establecerCantidadMaterial(int cantidad){
}
