#ifndef OBELISCO_H
#define OBELISCO_H

#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class Obelisco: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo obelisco
		Obelisco (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};

#endif // OBELISCO_H
