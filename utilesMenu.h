#ifndef utilesMenu_H
#define utilesMenu_H

void mostrarMenu();

void mostrarInventario(Juego* juego);

void construirEdificio(Juego* juego, string nombreIngresado);

int pedirOpcion();

void procesarOpcionesMenu(Juego* juego, int opcion);

// Pre: -
// Post: Establece el jugador activo entre 0 y 1 para ver quien tiene el primer turno
void comenzarPartida(Juego* juego);

void procesarOpcionesSubmenu(Juego* juego, int opcion);

void procesarOpciones(Juego* juego, int opcion);

void demolerEdificioCoordenada(Juego* juego);

void consultarCoordenada(Juego* juego);

#endif