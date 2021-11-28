#include "materiales.h"
#include "edificios/edificio.h"
#include "procesamiento.h"
#include "edificios/tipos_edificios.h"
#include "casilleros/casillero.h"

int main(){
	
	Proceso proceso;
	int opcion = 0;
	
	proceso.leerArchivos();

	
	proceso.mostrarMenu();
	opcion = proceso.pedirOpcion();
	
	while(opcion != 10){
		proceso.procesarOpciones(opcion);
		
		proceso.mostrarMenu();
		opcion = proceso.pedirOpcion();
	}
		
	proceso.guardarYSalir();
	
	

	cout << "todo ok" << endl;
	

	
	return 0;
}
