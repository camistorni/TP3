#ifndef FABRICA_H
#define FABRICA_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_FABRICA = 'F';

class Fabrica: public Tipo_edificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo fábrica
		Fabrica (int piedra, int madera, int metal, int cant_max_construido, std::string tipo_edificio);
};

#endif // FABRICA_H
