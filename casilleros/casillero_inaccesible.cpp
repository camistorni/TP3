#include <iostream>

#include "casillero.h"
#include "casillero_inaccesible.h"

const std::string CARACTER_COLOR_LAGO = "\033[1;44mI\033[0m";

Casillero_inaccesible::Casillero_inaccesible(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracter_color = CARACTER_COLOR_LAGO;
    tipo = "inaccesible";
    caracter_contenido = CARACTER_COLOR_LAGO;
}

std::string Casillero_inaccesible::obtener_tipo(){
    return "-1";
}

void Casillero_inaccesible::responder(){
    std::cout << "Soy un casillero inaccesible vacio" << std::endl;
}
int Casillero_inaccesible::obtener_cantidad_material(){
    return -1;
}

std::string Casillero_inaccesible::obtener_caracter_contenido(){
    return caracter_contenido;
}

void Casillero_inaccesible::establecer_tipo(std::string nombre_tipo){
}
void Casillero_inaccesible::liberar(){

}
void Casillero_inaccesible::establecer_caracter_contenido(std::string caracter){
}
void Casillero_inaccesible::establecer_cantidad_material(int cantidad){
}

