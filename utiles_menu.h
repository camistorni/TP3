#ifndef UTILES_MENU_H
#define UTILES_MENU_H

void mostrarMenu();

void mostrarInventario(Juego* juego);

bool construirEdificio(Juego* juego, string nombreIngresado);

int pedirOpcion();

void procesarOpciones(Juego* juego, int opcion);

void demolerEdificioCoordenada(Juego* juego);

void consultarCoordenada(Juego* juego);

#endif