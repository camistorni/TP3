#ifndef MENU_HPP
#define MENU_HPP

#include "../juego/juego.h"
#include "../mapa/casilleros/casilleroConstruible/casilleroConstruible.h"
#include "../mapa/casilleros/casilleroInaccesible/casilleroInaccesible.h"
#include "../jugadores/constantesJugador.h"
#include "../constantes/mensajes.h"


class Menu {
    private:
        Juego* juego;

    public:

        Menu();
        ~Menu();
        void iniciarJuego();
        // *************** MENU ***************

        // Pre: -
        // Post: Muestra el menu principal con sus opciones
        void mostrarMenuPrincipal();

        // Pre: Recibir la opcion seleccionada
        // Post: Procesa la opcion recibida y realiza la accion correspondiente
        void procesarOpcionesMenu(int& opcion);

        // Pre: -
        // Post: Modifica los materiales necesarios para construir un edificio
        void modificarEdificioPorNombre();

        // Pre: -
        // Post: Se encarga de realizar todas las acciones correspondientes a comenzar la partida
        void comenzarPartida();

        // Pre:- 
        // Post: Selecciona un jugador aleatorio entre Jugador 1 y Jugador 2
        void elegirJugador();

        // Pre: -
        // Post: Permite que el usuario seleccione si quiere ser el Jugador 1 o el Jugador 2
        void seleccionarJugador();

        // Pre: -
        // Post: Solicita al usuario que ingrese una coordenada hasta que la misma sea valida
        void solicitarCoordenadas();

        // *************** SUBMENU ***************

        // Pre: -
        // Post: Muestra el menu secundario con sus opciones
        void mostrarSubmenu();

        // Pre: Recibir la opcion seleccionada
        // Post: Procesa la opcion recibida y realiza la accion correspondiente
        void procesarOpcionesSubmenu(int& opcion);

        // Pre: -
        // Post: Muestra que jugador esta jugando, su energia y la cantidad de andycoins que posee
        void mostrarInformacion();
        
        // Pre: -
        // Post: Contiene la logica para construir el edificio indicado
        void construirEdificioPorNombre();

        // Pre: -
        // Post: Resta los materiales necesarios para la construccion
        void construirEdificio(int fila, int columna, string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario);

        // Pre: -
        // Post: Solicita la confirmacion del jugador para constuir el edificio
        char confirmacionConstruccion(string nombreIngresado);

        // Pre: -
        // Post: Modifica los valores del jugador para ver si se cumplio un objetivo
        void setearEdificios(string nombreIngresado, bool construido);

        // Pre: -
        // Post: 
        void listarEdificiosConstruidos();

        // Pre: -
        // Post: Contiene la lógica para la demolición del edificio
        void demolerEdificioPorCoordenada();

        // Pre: -
        // Post: Deposita los materiales que quedaron luego de demoler un edificio
        void depositarMateriales(string edificio, Casillero* casillero);

        // Pre: -
        // Post: Contiene la logica para atacar un edificio
        void atacarEdificioPorCoordenada();

        // Pre: -
        // Post: Contiene la logica para demoler un edificio
        void repararEdificioPorCoordenada();

        // Pre: -
        // Post: Contiene la logica para demoler un edificio
        void repararEdificio(Casillero* casillero);

        // Pre: -
        // Post: Si fue posible realizar la accion, se realizan las modificaciones necesarias al jugador
        void comprarBomba();

        // Pre: -
        // Post: Solicita la coordenada que se quiere consultar, e imprime su informacion
        void consultarCoordenada();

        // Pre: -
        // Post: Muestra los materiales con sus respectivas cantidades
        void mostrarInventario();

        // Pre: -
        // Post: Muestra por pantalla los objetivos activos del jugador actual
        void mostrarObjetivos();

        // Pre: -
        // Post: Muestra el progreso de los objetivos actuales del jugador
        void mostrarProgresoObjetivos(int i);

        // Pre:
        // Post: Cuenta la cantidad de edificios construidos que tiene el jugador
        int contarEdificiosConstruidos();

        // Pre: -
        // Post: Devuelve la cantidad de minas construidas
        int contarMinasConstruidas();

        // Pre: -
        // Post: Se solicita al jugador ingresar la coordenada a la que se quiere mover y se lo pasa a esa posicion del mapa
        void moverseAUnaCoordenada(Juego *juego);

        // Pre: -
        // Post: Se encarga de todo lo que este relacionado con realizar el cambio del jugador
        void finalizarTurno();

        // Pre: -
        // Post: Se fija si se cumplieron los objetivos para que el jugador gane el juego
        bool chequearObjetivos();

        // *************** GENERALES ***************

        // Pre: -
        // Post: Decide que menu mostrar dependiendo del momento de la partida en que se encuentre
        void mostrarMenu(); 

        // Pre: -
        // Post: Solicita al usuario que ingrese una opcion
        void pedirOpcion(int* opcion);

        // Pre: Recibir la opcion seleccionada
        // Post: Vuelve a pedir la opcion hasta que la misma sea una opcion valida
        void validarOpcionSeleccionada(int& opcionSeleccionada);

        // Pre: -
        // Post: Se encarga de procesar la opcion ingresada ya sea del menu principal como del secundario
        void procesarOpciones(int opcion); 

        // Pre: -
        // Post: -
        void partidaGanada(int* opcion);
};

#endif
