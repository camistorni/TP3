#include <iostream>

#include "casillero.h"
#include "casillero_transitable.h"
#include "../materiales.h"

const std::string CARACTER_COLOR_CAMINO = "\033[1;42mC\033[0m";

CasilleroTransitable::CasilleroTransitable(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracterColor = CARACTER_COLOR_CAMINO;
    caracterContenido = CARACTER_COLOR_CAMINO;
    tipo = "transitable";
    
}

std::string CasilleroTransitable::obtenerTipo(){
    return material.obtenerNombreMaterial();
}
void CasilleroTransitable::establecerTipo(std::string nombreTipo){
    material.establecerNombreMaterial(nombreTipo);
}
int CasilleroTransitable::obtenerCantidadMaterial(){
    return material.obtenerCantidadMaterial();
}
void CasilleroTransitable::establecerCantidadMaterial(int cantidad){
    material.establecerCantidad(cantidad);
}

void CasilleroTransitable::liberar(){
    material.establecerCantidad (0);
    material.establecerNombreMaterial ("-1");
}
void CasilleroTransitable::responder(){
    if (material.obtenerNombreMaterial() != "-1"){
        cout << "Soy un casillero transitable y tengo " << material.obtenerCantidadMaterial() << " de " << material.obtenerNombreMaterial();
        cout << endl;
    }
    else {
        cout << "Soy un casillero transitable vacio" << endl;
    }
}
void CasilleroTransitable::establecerCaracterContenido(std::string caracter){
    caracterContenido = caracter;
}
std::string CasilleroTransitable::obtenerCaracterContenido(){
    return caracterContenido;
}
