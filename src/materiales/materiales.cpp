#include "materiales.h"
#include <iostream>

Material::Material(){
}

Material::Material(string nombreMaterial, int cantidadMaterial){
	this -> nombreMaterial = nombreMaterial;
	this -> cantidadMaterial = cantidadMaterial;
}
string Material::obtenerNombreMaterial() {
	return this -> nombreMaterial;
}

int Material::obtenerCantidadMaterial(){
	return this -> cantidadMaterial;
}

void Material::establecerCantidad(int cantidad){
	this -> cantidadMaterial = cantidad;
}

void Material::modificarCantidad(int cantidadAgregada){
	this -> cantidadMaterial += cantidadAgregada;
}
