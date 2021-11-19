#ifndef ESCUELA_H
#define ESCUELA_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_ESCUELA = 'E';

class Escuela: public Tipo_edificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo escuela
		Escuela (int piedra, int madera, int metal, int cant_max_construido, std::string tipo_edificio);

};

#endif // ESCUELA_H
