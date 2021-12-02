#include <string>
#include <iostream>
#include "ABB.h"
#include "nodo.h"

using namespace std;


ABB::ABB(){
	this->raiz = NULL;
}


Nodo* ABB::insertarNodo(Nodo *nodo, tipo clave){

	if(nodo == NULL)
		nodo = new Nodo(clave);
		
	else if(clave < nodo->obtenerClave())
		nodo->setIzq(insertarNodo(nodo->obtenerIzq(), clave), nodo);
	
	else
		nodo->setDer(insertarNodo(nodo->obtenerDer(), clave), nodo);

	return nodo;
}


void ABB::insertarNodo(tipo clave){
	this->raiz = insertarNodo(this->raiz, clave);
}


void ABB::imprimirOrdenado(Nodo *nodo){
	
	if(nodo != NULL){
		imprimirOrdenado(nodo->obtenerIzq());
		cout << nodo->obtenerClave() << ' ';
		imprimirOrdenado(nodo->obtenerDer());
	}
}

void ABB::imprimirOrdenado(){
	imprimirOrdenado(this->raiz);
}


Nodo* ABB::buscar(Nodo *nodo, tipo clave){
	
	if(nodo == NULL || nodo->obtenerClave() == clave)
		return nodo;
	
	if(clave > nodo->obtenerClave())
		return buscar(nodo->obtenerDer(), clave);
	
	return buscar(nodo->obtenerIzq(), clave);
}


bool ABB::buscar(tipo clave){
	Nodo *buscado = buscar(this->raiz, clave);
	return buscado != NULL;
}

tipo ABB::encontrarMin(Nodo *nodo){
	
	if(nodo == NULL)
		return -1;
	
	else if(nodo->obtenerIzq() == NULL)
		return nodo->obtenerClave();
	
	else
		return encontrarMin(nodo->obtenerIzq());
		
}

tipo ABB::encontrarMin(){
	return encontrarMin(this->raiz);
}


tipo ABB::encontrarMax(Nodo *nodo){
	
	if(nodo == NULL)
		return -1;
	
	else if(nodo->obtenerDer() == NULL)
		return nodo->obtenerClave();
	
	else
		return encontrarMax(nodo->obtenerDer());

}


tipo ABB::encontrarMax(){
	return encontrarMax(this->raiz);
}


tipo ABB::sucesor(Nodo *nodo){
	if(nodo->obtenerDer() != NULL)
		return encontrarMin(nodo->obtenerDer());
	
	Nodo *sucesor = NULL;
	Nodo *ancestro = this->raiz;
	
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
	Nodo *nodo = this->buscar(this->raiz, clave);
	
	if(nodo == NULL)
		return -1;
	else return sucesor(nodo);
}


tipo ABB::predecesor(Nodo *nodo){
	if(nodo->obtenerIzq() != NULL)
		return encontrarMax(nodo->obtenerIzq());
	
	Nodo *sucesor = NULL;
	Nodo *ancestro = this->raiz;
	
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
	Nodo *nodo = this->buscar(this->raiz, clave);
	
	if(nodo == NULL)
		return -1;
	else return predecesor(nodo);
}


Nodo* ABB::eliminarNodo(Nodo *nodo, tipo clave){
	
	if(nodo == NULL)
		return NULL;
	
	if(nodo->obtenerClave() == clave){
		if(nodo->esHoja()){
			delete nodo;
		
		}else if(nodo->hijoDerecho()){
			nodo->obtenerDer()->setPadre(nodo->obtenerPadre());
			
			Nodo *aux = nodo;
			nodo = aux->obtenerDer();
			delete aux;
		}
		
		else if(nodo->hijoIzquierdo()){
			nodo->obtenerIzq()->setPadre(nodo->obtenerPadre());
			
			Nodo *aux = nodo;
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
}

void ABB::cerrarDiccionario(Nodo *nodo){
	if(nodo != NULL){
		this->cerrarDiccionario(nodo->obtenerIzq());
		this->cerrarDiccionario(nodo->obtenerDer());
		delete nodo;
	}
}

void ABB::cerrarDiccionario(){
	this->cerrarDiccionario(this->raiz);
}



