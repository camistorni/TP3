#include <string>
#include "nodo.h"

using namespace std;

NodoAbb::NodoAbb(tipo clave, int* datos){
	this->clave = clave;
	this->datos = datos;
	this->der = NULL;
	this->izq = NULL;
	this->padre = NULL;
}


tipo NodoAbb::obtenerClave(){
	return clave;
}

int* NodoAbb::obtenerDatos(){
	return datos;
}
NodoAbb* NodoAbb::obtenerDer(){
	return der;
}

NodoAbb* NodoAbb::obtenerIzq(){
	return izq;
}

NodoAbb* NodoAbb::obtenerPadre(){
	return padre;
}

void NodoAbb::setClave(tipo clave){
	this->clave = clave;
}

void NodoAbb::setDatos(int* datos){
	this->datos = datos;
}

void NodoAbb::setDer(NodoAbb *der, NodoAbb *padre){
	this->der = der;
	this->padre = padre;
}

void NodoAbb::setDer(NodoAbb *der){
	this->der = der;
}

void NodoAbb::setIzq(NodoAbb *izq, NodoAbb *padre){
	this->izq = izq;
	this->padre = padre;
}

void NodoAbb::setIzq(NodoAbb *izq){
	this->izq = izq;
}

void NodoAbb::setPadre(NodoAbb *padre){
	this->padre = padre;
}


bool NodoAbb::esHoja(){
	return (this->obtenerDer() == NULL && this->obtenerIzq() == NULL);
}

bool NodoAbb::hijoDerecho(){
	return (this->obtenerDer() != NULL && this->obtenerIzq() == NULL);
}

bool NodoAbb::hijoIzquierdo(){
	return (this->obtenerDer() == NULL && this->obtenerIzq() != NULL);
}

int NodoAbb::obtenerDato (int posicion){
	return datos[posicion];
}



