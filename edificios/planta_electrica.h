#ifndef PLANTA_ELECTRICA_H
#define PLANTA_ELECTRICA_H

#include "tipos_edificios.h"
#include "edificio.h"


const char CARACTER_PLANTA_ELECTRICA = 'P';

class PlantaElectrica: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo planta eléctrica
		PlantaElectrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};
#endif // PLANTA_ELECTRICA_H
