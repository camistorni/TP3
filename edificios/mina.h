#ifndef MINA_H
#define MINA_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_MINA = 'M';

class Mina: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo mina
		Mina (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};

#endif // MINA_H
