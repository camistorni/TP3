#include "materiales/materiales.h"
#include "edificios/edificio.h"
#include "juego/juego.h"
#include "menu/Menu.hpp"
#include "juego/grafo/Grafo.h"
#include "constantes/opciones.h"


#ifdef __linux__
#define CLR_SCREEN "clear"
#endif

#ifdef __MINGW32__
#define CLR_SCREEN "CLS"
#endif

int main() {
	Menu menu;

	menu.iniciarJuego();
/*	int opcion = MENU_ERROR;

	mostrarMenu(juego);
	pedirOpcion(&opcion);
	
	while((opcion != JUGADOR_GUARDAR_Y_SALIR) || ((juego -> obtenerJugadorActivo() < 0) && (opcion != MENU_GUARDAR_Y_SALIR))) {
		procesarOpciones(juego, opcion);
		mostrarMenu(juego);
		pedirOpcion(&opcion);
	}


	while((opcion != JUGADOR_GUARDAR_Y_SALIR) || ((juego -> obtenerJugadorActivo() < 0) && (opcion != MENU_GUARDAR_Y_SALIR))) {
		mostrarMenu(juego);
		pedirOpcion(&opcion);
		validarOpcionSeleccionada(opcion);
		//system(CLR_SCREEN);
		procesarOpciones(juego, opcion);
	}
*/

	/*juego->crearCaminos();
	juego->mostrarCaminoMinimo("0,0", "2, 3");
	//juego->guardarYSalir();
	delete juego;*/
	//juego -> guardarYSalir();
	//delete juego;
	
	return 0;
}
