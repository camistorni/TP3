#include "materiales/materiales.h"
#include "edificios/edificio.h"
#include "juego/juego.h"
#include "menu/utilesMenu.h"
#include "juego/grafo/Grafo.h"

int main(){
	Juego* juego = new Juego();
	int opcion = 0;
	mostrarMenu(juego);
	pedirOpcion(&opcion);
	while(opcion != 13){		
		procesarOpciones(juego, opcion);
		mostrarMenu(juego);
		pedirOpcion(&opcion);
	}
	juego->guardarYSalir();
	/*
	juego->crearCaminos();
	juego->mostrarCaminoMinimo("0,0", "0,1");*/
	return 0;
}
