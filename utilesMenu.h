#ifndef utilesMenu_H
#define utilesMenu_H

void mostrarMenu();

void mostrarInventario(Juego* juego);

void construirEdificio(Juego* juego, string nombreIngresado);

int pedirOpcion();

void procesarOpciones(Juego* juego, int opcion);

void demolerEdificioCoordenada(Juego* juego);

void consultarCoordenada(Juego* juego);

#endif