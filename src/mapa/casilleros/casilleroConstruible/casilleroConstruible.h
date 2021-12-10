#ifndef casilleroConstruible_H
#define casilleroConstruible_H

#include "../casillero.h"
#include "../../../edificios/edificio.h"

class CasilleroConstruible: public Casillero{

	private:
		bool construido;
		Edificio* edificio;
		int estadoEdifio; // 0 no hay nada, 1 dañado, 2 construido
		int propietarioEdificio; // dice de quien es el edificio
	public:
		CasilleroConstruible();
		~CasilleroConstruible();
		std::string obtenerEdificio();
		void agregarEdifico(std::string nombre, int jugador);
		void responder();
		int obtenerPropietarioEdificio();
};


#endif // casilleroConstruible_H
