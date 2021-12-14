#ifndef JUGADOR_H
#define JUGADOR_H

#include "../materiales/materiales.h"

class Jugador {

	protected:
        std::string nombre;
        Material** materiales;
        int energia;
        int* objetivos;

        int andycoinsRecolectadas;

        int cantidadEscuelasConstruidas;

        int bombasCompradas;
        int bombasUsadas;

        bool minaConstruida;
        bool aserraderoConstruido;
        bool fabricaConstruida;
        bool plantaElectricaConstruida;
        bool minaOroConstruida;
        bool obeliscoConstruido;
        int escuelaConstruida;

        bool masAltoQueLasNubesCumplido;
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
    // Constructor
		Jugador(std::string nombreJugador);
    // Destructor
        ~Jugador();

    // Getters
        int obtenerEnergia();
        int obtenerCantidadEscuelasConstruidas();
        int obtenerCantidadBombasCompradas();
        int obtenerCantidadBombasUsadas();
        int obtenerAndycoinsRecolectadas();
        int* obtenerObjetivos();
        Material** obtenerMateriales();    

    // Setters
        void establecerEnergia(int cantidadEnergia);
        void modificarEnergia(int energiaAgregada);
        void restarEnergia(int energiaGastada);
        void seleccionarObjetivos();
        void aumentarBombasCompradas(int cantidad);
        void aumentarBombasUsadas(int cantidad);
        
        
    // Generales
        // Pre: Se tiene que haber leído bien el archivo de materiales
		// Post: Agrega el material leído a la lista de materiales disponibles
        void agregarMaterial(Material* nuevoMaterial, int cantidadMateriales);
        
        // Pre: Recibir un nombre valido
        // Post: Devuelve el material con el nombre indicado
        Material* buscarMaterial(string nombreMaterial);



    // Objetivos
        // Pre: -
        // Post: Setea el atributo con el valor indicado como parametro
        void agregarEdificioConstruido(string edificio);

        // Pre: -
        // Post: Devuelve la cantidad de minas construidas
        int minasConstruidas();
        // Pre: -
        // Post: Devuelve la cantidad de edificios construidos
        int edificiosContruidos();
        
        // Pre: -
        // Post: Devuelve true si se cumplio el objetivo y false en caso contrario
        bool masAltoQueLasNubes();
        bool comprarAndypolis();
        bool edadDePiedra();
        bool bombardero();
        bool energetico();
        bool letrado();
        void letrado(bool cumplido);
        bool minero();
        bool cansado();
        bool constructor();
        bool armado();
        bool extremista();
};



#endif
