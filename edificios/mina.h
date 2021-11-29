#ifndef MINA_H
#define MINA_H

#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class Mina: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo mina
		Mina (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};

#endif // MINA_H
