#include "materiales/materiales.h"
#include "edificios/edificio.h"
#include "juego/juego.h"
#include "menu/utilesMenu.h"

int main(){
	Juego* juego = new Juego();
	int opcion = 0;
	mostrarMenu(juego);
	pedirOpcion(&opcion);
	while(opcion != 14){		
		procesarOpciones(juego, opcion);
		mostrarMenu(juego);
		pedirOpcion(&opcion);
	}
	return 0;
}
