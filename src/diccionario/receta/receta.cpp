#include "receta.h"
#include "../../constantes/constantes.h"
#include <iostream>

Receta::Receta(){}
Receta::Receta(int piedra, int madera, int metal, int maximoContruibles){
    piedraReceta = piedra;
    maderaReceta = madera; 
    metalReceta = metal;
    maximoContruiblesReceta = maximoContruibles;
    produccionReceta = "No produce";
}

int Receta::obtenerMaterial(std::string material){
    return material == PIEDRA ? piedraReceta : 
           material == MADERA ? maderaReceta : 
           material == METAL ? metalReceta : 
           material == MAXIMO_CONSTRUIBLES ? maximoContruiblesReceta : -1;
           

}   

void Receta::modificarMaterial(std::string material, int nuevaCantidad){
    material == PIEDRA ? piedraReceta = nuevaCantidad : 
    material == MADERA ? maderaReceta = nuevaCantidad : 
    material == METAL ? metalReceta  = nuevaCantidad : 
    material == MAXIMO_CONSTRUIBLES ? maximoContruiblesReceta = nuevaCantidad : -1;
}

std::string Receta::obtenerProduccion(){
    return produccionReceta;
}

void Receta::setearProduccion(std::string produccion){
    produccionReceta = produccion;
}
