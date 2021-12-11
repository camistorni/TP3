#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "constantesEdificios.h"
#include "../constantes/constantes.h"

class Edificio {
	protected:
		std::string nombreEdifico;
		char caracter;
		std::string materialProducido;
		int cantidadProducida;

	public:
		Edificio();
		~Edificio();

		//Precondiciones: -
		//Postcondicions: Devuelve el nombre del edificio
		std::string obtenerTipo();
		void setearNombreEdificio(std::string nombreEdificio);
		void setearMaterialProducido(std::string materialProducido);
		void setearCantidadProducida(int cantidadProducida);
		
		//Precondiciones: -
		//Postcondicions: Espeifica si el edificio brinda materiales o no
		bool recolectarMateriales(std::string* materialProducido, int* cantidadProducida);
};

class PlantaElectrica: public Edificio {
	using Edificio::Edificio;
	public:
		PlantaElectrica();
};
class Obelico: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = OBELISCO;
};
class MinaOro: public Edificio {
	using Edificio::Edificio;
	public:
		MinaOro();
};
class Mina: public Edificio {
	using Edificio::Edificio;
	public:
		Mina();
};
class Fabrica: public Edificio {
	using Edificio::Edificio;
	public:
		Fabrica();
};
class Escuela: public Edificio {
	using Edificio::Edificio;
	public:
		Escuela();
};
class Aserradero: public Edificio {
	using Edificio::Edificio;
	public:
		Aserradero();
};

#endif //tiposEdificios_H
