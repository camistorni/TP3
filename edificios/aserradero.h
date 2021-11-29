#ifndef ASERRADERO_H
#define ASERRADERO_H

#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class Aserradero: public TipoEdificio{

	public:
		
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo aserradero
		Aserradero (int piedra, int madera, int metal, int cantMaxconstruido, std::string tipoEdificio);
};

#endif // ASERRADERO_H
