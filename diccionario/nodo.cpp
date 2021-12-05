#include <string>
#include "nodo.h"

using namespace std;

Nodo::Nodo(tipo clave, string datos){
	this->clave = clave;
	this->datos = datos;
	this->der = NULL;
	this->izq = NULL;
	this->padre = NULL;
}


tipo Nodo::obtenerClave(){
	return clave;
}

string Nodo::obtenerDatos(){
	return datos;
}
Nodo* Nodo::obtenerDer(){
	return der;
}

Nodo* Nodo::obtenerIzq(){
	return izq;
}

Nodo* Nodo::obtenerPadre(){
	return padre;
}

void Nodo::setClave(tipo clave){
	this->clave = clave;
}

void Nodo::setDatos(string datos){
	this->datos = datos;
}

void Nodo::setDer(Nodo *der, Nodo *padre){
	this->der = der;
	this->padre = padre;
}

void Nodo::setDer(Nodo *der){
	this->der = der;
}

void Nodo::setIzq(Nodo *izq, Nodo *padre){
	this->izq = izq;
	this->padre = padre;
}

void Nodo::setIzq(Nodo *izq){
	this->izq = izq;
}

void Nodo::setPadre(Nodo *padre){
	this->padre = padre;
}


bool Nodo::esHoja(){
	return (this->obtenerDer() == NULL && this->obtenerIzq() == NULL);
}

bool Nodo::hijoDerecho(){
	return (this->obtenerDer() != NULL && this->obtenerIzq() == NULL);
}

bool Nodo::hijoIzquierdo(){
	return (this->obtenerDer() == NULL && this->obtenerIzq() != NULL);
}


