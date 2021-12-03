#include "materiales.h"
#include <iostream>

Material::Material(){
}

Material::Material(string nombreMaterial, int cantidadMaterial){
	this -> nombreMaterial = nombreMaterial;
	this -> cantidadMaterial = cantidadMaterial;
}
string Material::obtenerNombreMaterial(){
	return this -> nombreMaterial;
}

int Material::obtenerCantidadMaterial(){
	return this -> cantidadMaterial;
}

void Material::establecerNombreMaterial(std::string nombre){
	this -> nombreMaterial = nombre;
}
void Material::establecerCantidad(int cantidad){
	this -> cantidadMaterial = cantidad;
}

void Material::modificarCantidad(int cantidadUsada){
	this -> cantidadMaterial -= cantidadUsada;
}

void Material::agregarCantidad(int recursoAgregado){
	this -> cantidadMaterial += recursoAgregado;
}
