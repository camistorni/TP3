#include "materiales.h"
#include "edificios/edificio.h"
#include "juego.h"
#include "edificios/tiposEdificios.h"
#include "casilleros/casillero.h"
#include "utilesMenu.h"

int main(){
	
	Juego* juego = new Juego();
	cout << "a" << endl;
	int opcion = 0;
	cout << "b" << endl;
	mostrarMenu(juego);
	cout << "c" << endl;
	pedirOpcion(&opcion);
	cout << "d" << endl;
	while(opcion != 14){
		cout << "e" << endl;
		procesarOpciones(juego, opcion);
		cout << "f" << endl;
		mostrarMenu(juego);
		cout << "g" << endl;
		pedirOpcion(&opcion);
		cout << "h" << endl;
	}
	cout << "i" << endl;
	
	return 0;
}
