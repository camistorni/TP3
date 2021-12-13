#include <string>
#include "nodo.h"

using namespace std;

NodoAbb::NodoAbb(tipo clave, Receta* receta){
	this -> clave = clave;
	this -> receta = receta;
	der = NULL;
	izq = NULL;
	padre = NULL;
}

NodoAbb::~NodoAbb() {
	delete receta;
}

tipo NodoAbb::obtenerClave(){
	return clave;
}

Receta* NodoAbb::obtenerDatos(){
	return receta;
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
	this -> clave = clave;
}

void NodoAbb::setDatos(Receta* receta){
	this -> receta = receta;
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


