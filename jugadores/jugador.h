#ifndef JUGADOR_H
#define JUGADOR_H

#include "./../materiales.h"

class Jugador {

	protected:
        std::string nombre;
        Material** materiales;
        std::string* edificiosContruidos; // para el objetivo, no para el juego en si
        int energia;
		int* ubicacion; // capaz no hace falta
        int* objetivos;

        int andycoinsRecolectadas;

        int bombasCompradas;
        int bombasUsadas;

        bool minaConstruida;
        bool aserraderoConstruido;
        bool fabricaConstruida;
        bool escuelaConstruida;
        bool plantaElectricaConstruida;
        bool minaOroConstruida;

        bool comprarAndypolisCumplido;
        bool edadDePiedraCumplido;
        bool bombarderoCumplido;
        bool energeticoCumplido;
        bool letradoCumplido;
        bool mineroCumplido;
        bool cansadoCumplido;
        bool constructorCumplido;
        bool armadoCumplido;
        bool extremistaCumplido;
		
	public:
		Jugador(std::string nombreJugador);
        ~Jugador();

        int obtenerEnergia();
        void establecerEnergia(int cantidadEnergia);

        int obtenerCantidadMateriales();
        Material** obtenerMateriales();
        Material obtenerMaterial(int material);

        void establecerMaterial(Material* vectorMateriales);
        void establecerCantidadMateriales(int cantidadMateriales);

        //Precondiciones: Se tiene que haber leído bien el archivo de materiales
		//Postcondiciones: Agrega el material leído a la lista de materiales disponibles
        void agregarMaterial(Material* nuevoMaterial, int cantidadMateriales);
        
        Material* buscarMaterial(string nombreMaterial);

        // Objetivos
        bool comprarAndypolis();
        bool edadDePiedra();
        bool bombardero();
        bool energetico();
        bool letrero();
        bool minero();
        bool cansado();
        bool constructor();
        bool armado();
        bool extremista();
};



#endif
