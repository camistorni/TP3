#ifndef FABRICA_H
#define FABRICA_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_FABRICA = 'F';

class Fabrica: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo fábrica
		Fabrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};

#endif // FABRICA_H
