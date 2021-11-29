#ifndef ESCUELA_H
#define ESCUELA_H

#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class Escuela: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo escuela
		Escuela (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);

};

#endif // ESCUELA_H
