#ifndef MATERIALES_H
#define MATERIALES_H

#include <string>

using namespace std;

class Material{
	
	private:
		string nombreMaterial;
		int cantidadMaterial;
	
	public:		
		
		//Precondiciones: -
		//Postcondicions: Construye la memoria para un objeto material
		Material();
		
		//Precondiciones: -
		//Postcondicions: Construye un objeto material
		Material(string nombreMaterial, int cantidadMaterial);
		
		//Precondiciones: -
		//Postcondicions: Devuelve el nombre del material
		string obtenerNombreMaterial();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad disponible del material
		int obtenerCantidadMaterial();
		
		//Precondiciones: -
		//Postcondicions: Disminuye la cantidad de materiales
		void modificarCantidad(int cantidadUsada);

		void establecerCantidad (int cantidad);

};

#endif
