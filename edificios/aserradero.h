#ifndef ASERRADERO_H
#define ASERRADERO_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_ASERRADERO = 'A';

class Aserradero: public TipoEdificio{

	public:
		
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo aserradero
		Aserradero (int piedra, int madera, int metal, int cantMaxconstruido, std::string tipoEdificio);
};

#endif // ASERRADERO_H
