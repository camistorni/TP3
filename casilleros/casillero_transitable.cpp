#include <iostream>

#include "casillero.h"
#include "casillero_transitable.h"
#include "../materiales.h"

const std::string CARACTER_COLOR_CAMINO = "\033[1;42mC\033[0m";

Casillero_transitable::Casillero_transitable(int fila, int columna, char caracter):
Casillero(fila, columna, caracter){
    caracter_color = CARACTER_COLOR_CAMINO;
    caracter_contenido = CARACTER_COLOR_CAMINO;
    tipo = "transitable";
    
}

std::string Casillero_transitable::obtener_tipo(){
    return material.obtener_nombre_material();
}
void Casillero_transitable::establecer_tipo(std::string nombre_tipo){
    material.establecer_nombre_material(nombre_tipo);
}
int Casillero_transitable::obtener_cantidad_material(){
    return material.obtener_cantidad_material();
}
void Casillero_transitable::establecer_cantidad_material(int cantidad){
    material.establecer_cantidad(cantidad);
}

void Casillero_transitable::liberar(){
    material.establecer_cantidad (0);
    material.establecer_nombre_material ("-1");
}
void Casillero_transitable::responder(){
    if (material.obtener_nombre_material() != "-1"){
        cout << "Soy un casillero transitable y tengo " << material.obtener_cantidad_material() << " de " << material.obtener_nombre_material();
        cout << endl;
    }
    else {
        cout << "Soy un casillero transitable vacio" << endl;
    }
}
void Casillero_transitable::establecer_caracter_contenido(std::string caracter){
    caracter_contenido = caracter;
}
std::string Casillero_transitable::obtener_caracter_contenido(){
    return caracter_contenido;
}
