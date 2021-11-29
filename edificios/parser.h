#ifndef PARSER_H
#define PARSER_H

#include "tiposEdificios.h"
#include "edificio.h"



class Parser {
	private:
		std::string *lecturaArchivo;

	public:
		
		
		//Precondiciones: -
		//Postcondicions: Devuelve una línea del archivo "edificios" y la guarda en lectura_archivos[]
		Parser(std::string* lectura);
		
		//Precondiciones: -
		//Postcondicions: Procesa y crea tipos de edificios
		TipoEdificio* procesarEntrada ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el nombre del edificio
		std::string tipoEdificio ();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de piedra que requiere el edificio
		int piedra();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de madera que requiere el edificio
		int madera();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad de metal que requiere el edificio
		int metal();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la cantidad máxima de edificios que pueden construirse
		int cantMaxConstruido();
};

#endif // PARSER_H
