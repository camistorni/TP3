#include "materiales.h"
#include "edificios/edificio.h"
#include "juego.h"
#include "edificios/tiposEdificios.h"
#include "casilleros/casillero.h"

int main(){
	
	Juego juego;
	int opcion = 0;
	
	juego.mostrarMenu();
	opcion = juego.pedirOpcion();
	
	while(opcion != 10){
		juego.procesarOpciones(opcion);
		
		juego.mostrarMenu();
		opcion = juego.pedirOpcion();
	}
		
	juego.guardarYSalir();
	
	

	cout << "todo ok" << endl;
	

	
	return 0;
}
