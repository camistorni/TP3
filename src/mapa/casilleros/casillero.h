#ifndef CASILLERO_H
#define CASILLERO_H
#include "../../constantes/constantes.h"

class Casillero {

	protected:
		char tipo;
		char caracter = CARACTER_VACIO;
		std::string color;
		int energia;
		int jugador = -1;
	public:
		//Precondiciones: -
		//Postcondicions: Construye un objeto tipo casillero
		Casillero();
		~Casillero();
		//Precondiciones: -
		//Postcondicions: Devuelve el caracter del casillero
		void setearTipo(char tipo);
		char obtenerTipo();
		void setearCaracter(char caracter);
		char obtenerCaracter();
		void setearColor(std::string color);
		std::string obtenerColor();
		void setearEnergia(int energia);
		int obtenerEnergia(int jugadorActivo);
		void setearJugador(int jugador);
		int obtenerJugador();
		void removerJugador(int jugador);
		void responder();
};



#endif //CASILLERO_H
