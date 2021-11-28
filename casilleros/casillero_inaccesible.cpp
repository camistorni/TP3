#include <iostream>

#include "casillero.h"
#include "casillero_inaccesible.h"

const std::string CARACTER_COLOR_LAGO = "\033[1;44mI\033[0m";

CasilleroInaccesible::CasilleroInaccesible(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracterColor = CARACTER_COLOR_LAGO;
    tipo = "inaccesible";
    caracterContenido = CARACTER_COLOR_LAGO;
}

std::string CasilleroInaccesible::obtenerTipo(){
    return "-1";
}

void CasilleroInaccesible::responder(){
    std::cout << "Soy un casillero inaccesible vacio" << std::endl;
}
int CasilleroInaccesible::obtenerCantidadMaterial(){
    return -1;
}

std::string CasilleroInaccesible::obtenerCaracterContenido(){
    return caracterContenido;
}

void CasilleroInaccesible::establecerTipo(std::string nombreTipo){
}
void CasilleroInaccesible::liberar(){

}
void CasilleroInaccesible::establecerCaracterContenido(std::string caracter){
}
void CasilleroInaccesible::establecerCantidadMaterial(int cantidad){
}

