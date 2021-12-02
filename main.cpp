#include "materiales.h"
#include "edificios/edificio.h"
#include "juego.h"
#include "edificios/tiposEdificios.h"
#include "casilleros/casillero.h"
#include "utilesMenu.h"

int main(){
	
	Juego* juego = new Juego();

//	Jugador** jugadores = juego -> obtenerJugadores();
	int opcion = 0;
	mostrarMenu(juego);
	pedirOpcion(&opcion);
	while(opcion != 14) {
		
		procesarOpciones(juego, opcion);
		mostrarMenu(juego);
		pedirOpcion(&opcion);
	}
	
	return 0;
}
