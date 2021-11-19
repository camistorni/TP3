#include <iostream>

#include "casillero.h"
#include "casillero_construible.h"


const std::string CARACTER_COLOR_TERRENO = "\033[1;41mT\033[0m";

Casillero_construible::Casillero_construible(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracter_color = CARACTER_COLOR_TERRENO;
    tipo = "construible";
    this -> tipo_edificio = "-1";
    caracter_contenido = CARACTER_COLOR_TERRENO;
}
std::string Casillero_construible::obtener_tipo(){
    return tipo_edificio;
}
void Casillero_construible::establecer_tipo(std::string nombre_tipo){
    tipo_edificio = nombre_tipo;
}
int Casillero_construible::obtener_cantidad_material(){
    return -1;
}
void Casillero_construible::liberar(){
    tipo_edificio = "-1";
}
void Casillero_construible::responder(){
    if (tipo_edificio != "-1"){
        std::cout << "Soy un casillero construible y tengo construido un " << tipo_edificio;
        std::cout << std::endl;
    }
    else {
        std::cout << "Soy un casillero construible vacio" << std::endl;
    }
}
void Casillero_construible::establecer_caracter_contenido(std::string caracter){
    caracter_contenido = caracter;
}
std::string Casillero_construible::obtener_caracter_contenido(){
    return caracter_contenido;
}
void Casillero_construible::establecer_cantidad_material(int cantidad){
}
