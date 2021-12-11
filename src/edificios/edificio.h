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
		
		//Precondiciones: -
		//Postcondicions: Espeifica si el edificio brinda materiales o no
		bool recolectarMateriales(std::string* materialProducido, int* cantidadProducida);
};

class PlantaElectrica: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = PLANTA_ELECTRICA;
		std::string materialProducido = ENERGIA;
		int cantidadProducida = PRODUCCION_PLANTA_ELECTRICA;
};
class Obelico: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = OBELISCO;
};
class MinaOro: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = MINA_ORO;
		std::string materialProducido = ANDYCOINS;
		int cantidadProducida = PRODUCCION_MINA_ORO;
};
class Mina: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = MINA;
		std::string materialProducido = PIEDRA;
		int cantidadProducida = PRODUCCION_MINA;
};
class Fabrica: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = FABRICA;
		std::string materialProducido = METAL;
		int cantidadProducida = PRODUCCION_FABRICA;
};
class Escuela: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = ESCUELA;
		std::string materialProducido = ANDYCOINS;
		int cantidadProducida = PRODUCCION_ESCUELA;
};
class Aserradero: public Edificio {
	using Edificio::Edificio;
	public:
		std::string nombreEdifico = ASERRADERO;
		std::string materialProducido = MADERA;
		int cantidadProducida = PRODUCCION_ASERRADERO;
};

#endif //tiposEdificios_H
