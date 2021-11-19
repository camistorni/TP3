#include "materiales.h"
#include "edificios/edificio.h"
#include "procesamiento.h"
#include "edificios/tipos_edificios.h"
#include "casilleros/casillero.h"

int main(){
	
	Proceso proceso;
	int opcion = 0;
	
	proceso.leer_archivos();

	
	proceso.mostrar_menu();
	opcion = proceso.pedir_opcion();
	
	while(opcion != 10){
		proceso.procesar_opciones(opcion);
		
		proceso.mostrar_menu();
		opcion = proceso.pedir_opcion();
	}
		
	proceso.guardar_y_salir();
	
	

	cout << "todo ok" << endl;
	

	
	return 0;
}
