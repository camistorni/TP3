#include <string>
#include <iostream>
#include "ABB.h"
#include "nodo.h"
#include "../mapa/mapa.h"

using namespace std;


ABB::ABB(){
	this->raiz = NULL;
	this->cantidadNodos = 0;
}

NodoAbb* ABB::insertarNodo(NodoAbb *nodo, tipo clave, int* datos){

	if(nodo == NULL)
		nodo = new NodoAbb(clave, datos);
		
	else if(clave < nodo->obtenerClave())
		nodo->setIzq(insertarNodo(nodo->obtenerIzq(), clave, datos), nodo);
	
	else
		nodo->setDer(insertarNodo(nodo->obtenerDer(), clave, datos), nodo);
	
	return nodo;
}


void ABB::insertarNodo(tipo clave, int* datos){
	this->raiz = insertarNodo(this->raiz, clave, datos);
	cantidadNodos++;
}


void ABB::imprimirOrdenado(NodoAbb *nodo){
	
	if(nodo != NULL){
		imprimirOrdenado(nodo->obtenerIzq());
		cout << nodo->obtenerClave() << ": ";
		
		for(int i = 0; i < 3; i++)
			cout << nodo->obtenerDatos()[i] << ' ';
		cout << endl;
		imprimirOrdenado(nodo->obtenerDer());
	}
}

void ABB::imprimirOrdenado(){
	imprimirOrdenado(this->raiz);
}

void ABB::imprimirTablaOrdenada(NodoAbb *nodo){
	if(nodo != NULL){

		imprimirTablaOrdenada(nodo->obtenerIzq());

		long espacio =  obtenerMayorLongitud() - nodo -> obtenerClave().length();

		cout << nodo -> obtenerClave()  << setw(13 + (int)espacio);;

		
		for(int i = 0; i < 3; i++)
			cout << nodo -> obtenerDatos()[i];
		cout << endl;

		imprimirTablaOrdenada(nodo->obtenerDer());
	}
}

void ABB::imprimirTablaOrdenada(){
	imprimirTablaOrdenada(this->raiz);
}

NodoAbb* ABB::buscar(NodoAbb *nodo, tipo clave){
	
	if(nodo == NULL || nodo->obtenerClave() == clave)
		return nodo;
	
	if(clave > nodo->obtenerClave())
		return buscar(nodo->obtenerDer(), clave);
	
	return buscar(nodo->obtenerIzq(), clave);
}


NodoAbb* ABB::buscar(tipo clave){
	NodoAbb *buscado = buscar(this->raiz, clave);
	return buscado;
}

tipo ABB::encontrarMin(NodoAbb *nodo){
	
	if(nodo == NULL)
		return NULL;
	
	else if(nodo->obtenerIzq() == NULL)
		return nodo->obtenerClave();
	
	else
		return encontrarMin(nodo->obtenerIzq());
		
}

tipo ABB::encontrarMin(){
	return encontrarMin(this->raiz);
}


tipo ABB::encontrarMax(NodoAbb *nodo){
	
	if(nodo == NULL)
		return NULL;
	
	else if(nodo->obtenerDer() == NULL)
		return nodo->obtenerClave();
	
	else
		return encontrarMax(nodo->obtenerDer());

}


tipo ABB::encontrarMax(){
	return encontrarMax(this->raiz);
}


tipo ABB::sucesor(NodoAbb *nodo){
	if(nodo->obtenerDer() != NULL)
		return encontrarMin(nodo->obtenerDer());
	
	NodoAbb *sucesor = NULL;
	NodoAbb *ancestro = this->raiz;
	
	while(ancestro != nodo){
		if(nodo->obtenerClave() < ancestro->obtenerClave()){
			sucesor = ancestro;
			ancestro = ancestro->obtenerIzq();
		}
		else
			ancestro = ancestro->obtenerDer();
	}
	
	return sucesor->obtenerClave();
}

tipo ABB::sucesor(tipo clave){
	NodoAbb *nodo = this->buscar(this->raiz, clave);
	
	if(nodo == NULL)
		return NULL;
	else return sucesor(nodo);
}


tipo ABB::predecesor(NodoAbb *nodo){
	if(nodo->obtenerIzq() != NULL)
		return encontrarMax(nodo->obtenerIzq());
	
	NodoAbb *sucesor = NULL;
	NodoAbb *ancestro = this->raiz;
	
	while(ancestro != nodo){
		if(nodo->obtenerClave() < ancestro->obtenerClave()){
			sucesor = ancestro;
			ancestro = ancestro->obtenerDer();
		}
		else
			ancestro = ancestro->obtenerIzq();
	}
	
	return sucesor->obtenerClave();

}

tipo ABB::predecesor(tipo clave){
	NodoAbb *nodo = this->buscar(this->raiz, clave);
	
	if(nodo == NULL)
		return NULL;
	else return predecesor(nodo);
}


NodoAbb* ABB::eliminarNodo(NodoAbb *nodo, tipo clave){
	
	if(nodo == NULL)
		return NULL;
	
	if(nodo->obtenerClave() == clave){
		if(nodo->esHoja()){
			delete nodo;
			nodo = nullptr;
		}else if(nodo->hijoDerecho()){
			nodo->obtenerDer()->setPadre(nodo->obtenerPadre());
			
			NodoAbb *aux = nodo;
			nodo = aux->obtenerDer();
			delete aux;
		}
		
		else if(nodo->hijoIzquierdo()){
			nodo->obtenerIzq()->setPadre(nodo->obtenerPadre());
			
			NodoAbb *aux = nodo;
			nodo = aux->obtenerIzq();
			delete aux;
		}
		
		else{
			tipo clave_sucesor = this->sucesor(clave);
			nodo->setClave(clave_sucesor);
			nodo->setDer(eliminarNodo(nodo->obtenerDer(), clave_sucesor));
		}
	}
		
	else if(nodo->obtenerClave() < clave)
		nodo->setDer(eliminarNodo(nodo->obtenerDer(), clave));
		
	else
		nodo->setIzq(eliminarNodo(nodo->obtenerIzq(), clave));
		
	return nodo;
}


void ABB::eliminarNodo(tipo clave){
	this->raiz = eliminarNodo(this->raiz, clave);
	cantidadNodos--;
}

void ABB::cerrarDiccionario(NodoAbb *nodo){
	if(nodo != NULL){
		this->cerrarDiccionario(nodo->obtenerIzq());
		this->cerrarDiccionario(nodo->obtenerDer());
		delete nodo;
	}
}

void ABB::cerrarDiccionario(){
	this->cerrarDiccionario(this->raiz);
}

void ABB::obtenerMayorLongitud(NodoAbb* nodo, long unsigned int &largo){
	if(nodo != NULL){
		obtenerMayorLongitud(nodo->obtenerIzq(), largo);


		if (nodo -> obtenerClave().length() > largo)
			largo = nodo -> obtenerClave().length();
		obtenerMayorLongitud(nodo->obtenerDer(), largo);
	}
	
}

long unsigned int ABB::obtenerMayorLongitud(){

	long unsigned int mayorLongitud = 0;
		
	obtenerMayorLongitud(raiz, mayorLongitud);

	return mayorLongitud;
}

