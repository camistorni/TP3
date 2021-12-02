#include "materiales.h"
#include "edificios/edificio.h"
#include "juego.h"
#include "edificios/tiposEdificios.h"
#include "casilleros/casillero.h"
#include "utilesMenu.h"

int main(){
	
	Juego* juego = new Juego();

	Jugador** jugadores = juego -> obtenerJugadores();
	cout << "en el main la energia del 2 es " << jugadores[1] -> obtenerEnergia() << endl;
	cout << "en el main la energia del 1 es " << jugadores[0] -> obtenerEnergia() << endl;
	cout << "en el main la energia del 1 es " << jugadores[0] -> obtenerEnergia() << endl;
	cout << "en el main la energia del 2 es " << jugadores[1] -> obtenerEnergia() << endl;
	cout << "en el main la energia del 1 es " << jugadores[0] -> obtenerEnergia() << endl;

	int opcion = 0;
	mostrarMenu(juego);
	pedirOpcion(&opcion);
	while(opcion != 14){
		cout << "pre procesarOpciones" << endl;
		
		
		procesarOpciones(juego, opcion);
		cout << "post procesarOpciones" << endl;
		mostrarMenu(juego);
		pedirOpcion(&opcion);
	}
	
	return 0;
}
