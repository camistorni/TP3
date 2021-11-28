#ifndef TIPOS_EDIFICIOS_H
#define TIPOS_EDIFICIOS_H

#include "edificio.h"


const std::string PATH_ENTRADA_EDIFICIOS = "edificios.txt";

class TipoEdificio {

	protected:
		std::string tipoEdificio;
		int cantPiedra;
		int cantMadera;
		int cantMetal;
		int cantMaxConstruido;
		char caracter;

		int cantidadConstruidos;
		bool brindaMateriales;
		Edificio** edificiosConstruidos;

	public:
		~TipoEdificio();
		TipoEdificio();
		
		//Precondiciones: -
		//Postcondicions: Construye un objeto tipo edificio
		TipoEdificio (int piedra, int madera, int metal, int cantMaxConstruido, std::string TipoEdificio);
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de piedra que requiere el edificio
		int obtenerPiedra();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de madera que requiere el edificio
		int obtenerMadera();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de metal que requiere el edificio
		int obtenerMetal();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad máxima de edificios que pueden construirse
		int obtenerCantMaxConstruido();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el nombre del edificio
		std::string obtenerTipo();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de edificios construidos
		int obtenerCantConstruidos();
		
		//Precondiciones: -
		//Postcondicions: Espeifica si el edificio brinda materiales o no
		bool brindaMaterial();
		
		
		//Precondiciones: -
		//Postcondicions: Devuelve los edificios construidos
		Edificio* obetenerEdificiosConstruidos(int posisicionEdificio);
		

		//Precondiciones: -
		//Postcondiciones: Agrega el edificio leído a la lista de edificios construidos
		void agregarEdificioConstruido(Edificio* edificio);

		//Precondiciones: el edificio tiene que existir
		//Postcondiciones: destruye un edificio
		void derribarEdificioConstruido(int fila, int columna);
		
		//Precondiciones: -
		//Postcondiciones: Libera la memoria utilizada por los edificios construidos
		void liberarEdificosConstruidos();
		
		
		void mostrar();
};


#endif //TIPOS_EDIFICIOS_H
