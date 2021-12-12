#ifndef NODO_H
#define NODO_H

#include <string>
#include "receta/receta.h"

using namespace std;

typedef string tipo;

class NodoAbb{
	private:
		tipo clave; //nombre edificio
		Receta* receta; //receta edificio
		NodoAbb *der;
		NodoAbb *izq;
		NodoAbb *padre;
		
	public:
	
		//Constructor
		NodoAbb(tipo clave, Receta* receta);
		
		//PRE: -
		//POS: Devuelve la clave del nodo
		tipo obtenerClave();
		
		//PRE: -
		//POS: Devuelve un arreglo de datos del nodo
		Receta *obtenerDatos();
		
		//PRE: -
		//POS: Devuelve el hijo derecho del nodo
		NodoAbb *obtenerDer();
		
		//PRE: -
		//POS: Devuelve el hijo izquierdo del nodo
		NodoAbb *obtenerIzq();
		
		//PRE: -
		//POS: Devuelve el padre del nodo
		NodoAbb *obtenerPadre();
		
		//PRE: -
		//POS: Modifica la clave del nodo
		void setClave(tipo clave);
		
		//PRE: -
		//POS: Modifica los datos del nodo
		void setDatos(Receta *receta);
		
		//PRE: -
		//POS: Modifica el hijo derecho del nodo y a su padre
		void setDer(NodoAbb *der, NodoAbb *padre);
		
		//PRE: -
		//POS: Modifica el hijo izquierdo del nodo y a su padre
		void setIzq(NodoAbb *izq, NodoAbb* padre);
		
		//PRE: -
		//POS: Modifica el hijo derecho del nodo
		void setDer(NodoAbb *der);
		
		//PRE: -
		//POS: Modifica el hijo izquierdo del nodo
		void setIzq(NodoAbb *izq);
		
		//PRE: -
		//POS: Modifica al padre del nodo
		void setPadre(NodoAbb *padre);
		
		//PRE: -
		//POS: Devuelve true si el nodo es una hoja
		bool esHoja();
		
		//PRE: -
		//POS: Devuelve true si el nodo tiene un hijo derecho
		bool hijoDerecho();
		
		//PRE: -
		//POS: Devuelve true si el nodo tiene un hijo izquierdo
		bool hijoIzquierdo();
		
		
};

#endif


