#ifndef casilleroConstruible_H
#define casilleroConstruible_H

#include "casillero.h"

class CasilleroConstruible: public Casillero{

	private:
		bool construido;
		std::string tipoEdificio;
	public:
		CasilleroConstruible(int fila, int columna, char caracter);
		std::string obtenerTipo();
		void establecerTipo(std::string tipo);
		int obtenerCantidadMaterial();
		void establecerCantidadMaterial(int material);
		void establecerRecursos();
		void responder();
		void establecerCaracterContenido(std::string caracter);
		std::string obtenerCaracterContenido();
		void liberar();


};


#endif // casilleroConstruible_H
