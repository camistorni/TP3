#ifndef MINAORO_H
#define MINAORO_H

#include <iostream>
#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class MinaOro: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo mina
		MinaOro (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};

#endif // MINAORO_H
