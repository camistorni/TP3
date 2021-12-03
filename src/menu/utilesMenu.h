#ifndef utilesMenu_H
#define utilesMenu_H
#include "../juego/juego.h"

// *************** MENU ***************

// Pre: -
// Post: Muestra el menu principal con sus opciones
void mostrarMenu(Juego* Juego);
void mostrarMenuPrincipal();

// Pre: Recibir la opcion seleccionada
// Post: Procesa la opcion recibida y realiza la accion correspondiente
void procesarOpcionesMenu(Juego* juego, int opcion);

// Pre: -
// Post: Se encarga de realizar todas las acciones correspondientes a comenzar la partida
void comenzarPartida(Juego* juego);

// Pre:- 
// Post: Selecciona un jugador aleatorio entre Jugador 1 y Jugador 2
void elegirJugador(Juego* juego);

// Pre: -
// Post: Permite que el usuario seleccione si quiere ser el Jugador 1 o el Jugador 2
void seleccionarJugador(Juego* juego);

// Pre: -
// Post: Solicita al usuario que ingrese una coordenada hasta que la misma sea valida
void solicitarCoordenadas(Juego* juego);

// *************** SUBMENU ***************

// Pre: -
// Post: Muestra el menu secundario con sus opciones
void mostrarSubmenu(Juego* juego);

void mostrarInformacion(Juego* juego);

// Pre: Recibir la opcion seleccionada
// Post: Procesa la opcion recibida y realiza la accion correspondiente
void procesarOpcionesSubmenu(Juego* juego, int opcion);

// Pre: -
// Post: Muestra por pantalla los objetivos activos del jugador actual
void mostrarObjetivos(Juego* juego);

// Pre: -
// Post: Imprime por pantalla los objetivos activos del jugador actual
void imprimirObjetivos(int objetivo);

// Pre: -
// Post: Muestra los materiales con sus respectivas cantidades
void mostrarInventario(Juego* juego);

// Pre: -
// Post: Devuelve true si se pudo realizar la accion y false en caso contrario. 
// Si fue posible realizar la accion, se realizan las modificaciones necesarias al jugador
bool comprarBomba(Juego* juego);

// Pre: -
// Post: Solicita la coordenada que se quiere consultar, e imprime su informacion
void consultarCoordenada(Juego* juego);

// *************** GENERALES ***************

// Pre: -
// Post: Solicita al usuario que ingrese una opcion
void pedirOpcion(int* opcion);

// Pre: Recibir la opcion seleccionada
// Post: Vuelve a pedir la opcion hasta que la misma sea una opcion valida
void validarOpcionSeleccionada(int& opcionSeleccionada);

// Pre: -
// Post: Se encarga de procesar la opcion ingresada ya sea del menu principal como del secundario
void procesarOpciones(Juego* juego, int opcion);

// Pre: -
// Post: -
void construirEdificio(Juego* juego, string nombreIngresado);


#endif