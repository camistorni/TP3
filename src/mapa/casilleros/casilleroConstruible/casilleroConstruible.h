#ifndef casilleroConstruible_H
#define casilleroConstruible_H

#include "../casillero.h"
#include "../../../edificios/edificio.h"

class CasilleroConstruible: public Casillero{

	private:
		bool construido;
		Edificio* edificio;
		int estadoEdifio;
		int propietarioEdificio;
	public:
		CasilleroConstruible();
		~CasilleroConstruible();
		std::string obtenerEdificio();
		void agregarEdifico(std::string nombre, int jugador);
		void responder();
		int obtenerPropietario();
};


#endif // casilleroConstruible_H
