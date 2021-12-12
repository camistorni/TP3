#ifndef casilleroConstruible_H
#define casilleroConstruible_H

#include "../casillero.h"
#include "../../../edificios/edificio.h"
#include "../../../materiales/materiales.h"

class CasilleroConstruible: public Casillero {

	private:
		bool construido;
		Edificio* edificio;
		Material* material; // Solo para cuando se destrye un edificio
		int estadoEdificio; // 0 no hay nada, 1 dañado, 2 construido
		int propietarioEdificio = -1; // dice de quien es el edificio
	public:
		CasilleroConstruible();
		~CasilleroConstruible();
		std::string obtenerEdificio();
		void agregarEdifico(std::string nombre, int jugador);
		void responder();
		int obtenerPropietarioEdificio();
		bool recolectar(std::string* materialProducido, int* cantidadProducida, int jugador);
		bool atacarEdificio();
		bool repararEdificio();
		void demolerEdificio();
		void depositarMaterial(Material* material);
		
};


#endif // casilleroConstruible_H
