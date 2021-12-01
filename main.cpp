#include "materiales.h"
#include "edificios/edificio.h"
#include "juego.h"
#include "edificios/tiposEdificios.h"
#include "casilleros/casillero.h"
#include "utilesMenu.h"

int main(){
	
	Juego* juego = new Juego();
	int opcion = 0;
	
	mostrarMenu();
	pedirOpcion(&opcion);
	
	while(opcion != 10){
		procesarOpciones(juego, opcion);
		mostrarMenu();
		pedirOpcion(&opcion);
	}
	
	return 0;
}
