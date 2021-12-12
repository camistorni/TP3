#ifndef ABB_H
#define ABB_H

#include <string>
#include <iostream>
#include <iomanip>
#include "nodo.h"

using namespace std;

//typedef int tipo;

class ABB{
	private:
		NodoAbb* raiz;
		int cantidadNodos;
		
		//Métodos
		NodoAbb *insertarNodo(NodoAbb *NodoAbb, tipo clave, int *datos);
		void imprimirOrdenado(NodoAbb *NodoAbb);
		void imprimirTablaOrdenada(NodoAbb *nodo);
		NodoAbb *buscar(NodoAbb *NodoAbb, tipo clave);
		tipo sucesor(NodoAbb *NodoAbb);
		tipo predecesor(NodoAbb *NodoAbb);
		tipo encontrarMin(NodoAbb *NodoAbb);
		tipo encontrarMax(NodoAbb *NodoAbb);
		NodoAbb *eliminarNodo(NodoAbb *NodoAbb, tipo clave);
		void cerrarDiccionario(NodoAbb *NodoAbb);
		void obtenerMayorLongitud(NodoAbb* nodo, long unsigned int &largo);

		
	public:
		
		//Constructor
		ABB();
		
		//PRE: Tiene que haberse leído bien el mapa
		//POS: Agrega un nuevo nodo al arbol. Si el arbolo está vacío crea una raiz
		void insertarNodo(tipo clave, int* datos);
		
		//PRE: -
		//POS: Imprime todos los nodos y sus datos en orden alfabético
		void imprimirOrdenado();
		
		//PRE: -
		//POS: Imprime todos los nodos y sus datos en orden alfabético en formato de tabla
		void imprimirTablaOrdenada();
		
		//PRE: -
		//POS: Busca un nodo a partir de la clave ingresada
		NodoAbb* buscar(tipo clave);
		
		//PRE: -
		//POS: Busca el sucesor de un nodo
		tipo sucesor(tipo clave);
		
		//PRE: -
		//POS: Busca el predecesor de un nodo
		tipo predecesor(tipo clave);
		
		//PRE: -
		//POS: Busca el valor mínimo entre los nodos
		tipo encontrarMin();
		
		//PRE: -
		//POS: Busca el valor máximo entre los nodos
		tipo encontrarMax();
		
		//PRE: -
		//POS: Elimina un nodo a partir de la clave ingresada
		void eliminarNodo(tipo clave);
		
		//PRE: -
		//POS: Elimina todos los nodos y libera la memoria
		void cerrarDiccionario();

		//PRE: -
		//POS: Devuelve un long con el mayor del tamaño de las claves
		long unsigned int obtenerMayorLongitud();
 
};

#endif
