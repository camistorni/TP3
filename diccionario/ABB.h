#ifndef ABB_H
#define ABB_H

#include <string>
#include <iostream>
#include "nodo.h"

using namespace std;

//typedef int tipo;

class ABB{
	private:
		Nodo* raiz;
		
		Nodo *insertarNodo(Nodo *nodo, tipo clave, string datos);
		void imprimirOrdenado(Nodo *nodo);
		Nodo *buscar(Nodo *nodo, tipo clave);
		tipo sucesor(Nodo *nodo);
		tipo predecesor(Nodo *nodo);
		tipo encontrarMin(Nodo *nodo);
		tipo encontrarMax(Nodo *nodo);
		Nodo *eliminarNodo(Nodo *nodo, tipo clave);
		void cerrarDiccionario(Nodo *nodo);
		
	public:
		ABB();
		void insertarNodo(tipo clave, string datos);
		void imprimirOrdenado();
		bool buscar(tipo clave);
		tipo sucesor(tipo clave);
		tipo predecesor(tipo clave);
		tipo encontrarMin();
		tipo encontrarMax();
		void eliminarNodo(tipo clave);
		void cerrarDiccionario();
};

#endif