#ifndef plantaElectrica_H
#define plantaElectrica_H

#include "tiposEdificios.h"
#include "edificio.h"
#include "constantesEdificios.h"

class PlantaElectrica: public TipoEdificio {

	public:
	
		//Precondiciones: -
		//Postcondiciones: Construye un edificio de tipo planta eléctrica
		PlantaElectrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio);
};
#endif // plantaElectrica_H
