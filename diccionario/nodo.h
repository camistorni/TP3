#ifndef NODO_H
#define NODO_H

#include <string>

using namespace std;

typedef string tipo;

class Nodo{
	private:
		tipo clave; //nombre edificio
		string datos; //receta edificio
		Nodo *der;
		Nodo *izq;
		Nodo *padre;
		
	public:
		Nodo(tipo clave, string datos);
		tipo obtenerClave();
		string obtenerDatos();
		Nodo *obtenerDer();
		Nodo *obtenerIzq();
		Nodo *obtenerPadre();
		void setClave(tipo clave);
		void setDatos(string datos);
		void setDer(Nodo *der, Nodo *padre);
		void setIzq(Nodo *izq, Nodo* padre);
		void setDer(Nodo *der);
		void setIzq(Nodo *izq);
		void setPadre(Nodo *padre);
		bool esHoja();
		bool hijoDerecho();
		bool hijoIzquierdo();
		
		
};

#endif

