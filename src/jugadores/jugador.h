#ifndef JUGADOR_H
#define JUGADOR_H

#include "../materiales/materiales.h"

class Jugador {

	protected:
        std::string nombre;
        Material** materiales;
        std::string* edificiosContruidos; // para el objetivo, no para el juego en si
        int energia;
		int* ubicacion; // capaz no hace falta
        int* objetivos;

        int andycoinsRecolectadas;

        int cantidadEscuelasConstruidas;

        int bombasCompradas;
        int bombasUsadas;

        bool minaConstruida;
        bool aserraderoConstruido;
        bool fabricaConstruida;
        bool escuelaConstruida;
        bool plantaElectricaConstruida;
        bool minaOroConstruida;
        bool obeliscoConstruido;

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
        int* obtenerUbicacion();
        Material** obtenerMateriales();    

    // Setters
        void establecerEnergia(int cantidadEnergia);
        void establecerCoordenadas(int fila, int columna);
        void modificarEnergia(int energiaAgregada);
        void restarEnergia(int energiaGastada);
        void seleccionarObjetivos();
        void aumentarBombasCompradas(int cantidad);
        void aumentarBombasUsadas(int cantidad);
        void modificarCantidadEscuelasConstruidas(int cantidad);
        
        
    // Generales
        // Pre: Se tiene que haber leído bien el archivo de materiales
		// Post: Agrega el material leído a la lista de materiales disponibles
        void agregarMaterial(Material* nuevoMaterial, int cantidadMateriales);
        
        // Pre: Recibir un nombre valido
        // Post: Devuelve el material con el nombre indicado
        Material* buscarMaterial(string nombreMaterial);
        // Pre: 
        // Post:


    // Objetivos
        // Pre: -
        // Post: Setea el atributo con el valor indicado como parametro

        void agregarEdificioConstruido(string edificio);
        void construirMina(bool construido);
        void construirAserradero(bool construido);
        void construirFabrica(bool construido);
        void construirEscuela(bool construido);
        void construirPlantaElectrica(bool construido);
        void construirMinaOro(bool construido);
        void construirObelisco(bool construido);
        
        // Pre: -
        // Post: Devuelve true si el edificio esta construido, y false en caso contrario
        bool hayMinaConstruida();
        bool hayAserraderoconstruido();
        bool hayFabricaConstruida();
        bool hayEscuelaConstruida();
        bool hayPlantaElectricaConstruida();
        bool hayMinaOroConstruida();
        
        // Pre: -
        // Post: Devuelve true si se cumplio el objetivo y false en caso contrario
        bool masAltoQueLasNubes();
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
