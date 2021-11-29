#include <iostream>
#include "utiles_menu.h"
#include "juego.h"

void mostrarMenu() {

	cout << endl << endl;
	cout << TXT_ITALIC << TXT_LIGHT_AQUA_123 << "\t            ¡BIENVENIDOS A ANDYPOLIS!" << END_COLOR << endl << endl;
	cout << "                        " << TXT_UNDERLINE << "Menú de opciones" << END_COLOR << endl << endl;
	cout << "            ╔═══════════════════════════════════════╗" << endl;
	cout << "            ║ 1. Construir edificio por nombre      ║" << endl;
	cout << "            ║ 2. Listar los edificios construidos   ║" << endl;
	cout << "            ║ 3. Listar todos los edificios         ║" << endl;
	cout << "            ║ 4. Demoler un edificio por coordenada ║" << endl;
	cout << "            ║ 5. Mostrar mapa                       ║" << endl;
	cout << "            ║ 6. Consultar coordenada               ║" << endl;
	cout << "            ║ 7. Mostrar inventario                 ║" << endl;
	cout << "            ║ 8. Recolectar recursos producidos     ║" << endl;
	cout << "            ║ 9. LLuvia de recursos                 ║" << endl;
	cout << "            ║ 10. Guardar y salir                   ║" << endl;
	cout << "            ╚═══════════════════════════════════════╝" << endl << endl;
}

void mostrarInventario(Juego* juego){

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << '\t' << " ═══════════════════════════════ " << endl;
	cout << '\t' << " Materiales        Cantidades   " << endl;
	cout << '\t' << " ═══════════════════════════════ " << endl;

	for(int i = 0; i < juego -> obtenerCantidadMateriales(); i++) {
		cout << '\t' << juego -> obtenerJugadorActivo() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << ":\t" << 
		'\t' << juego -> obtenerJugadorActivo() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << endl;
	}
}

bool construirEdificio(Juego* juego, string nombreIngresado){
	int piedraNecesaria = 0, maderaNecesaria = 0, metalNecesario = 0, construidos = 0, cantidadMax = 0;
	
	//Verifica que el edificio ingresado exista
	if(!verificarEdificio(nombreIngresado, &piedraNecesaria, &maderaNecesaria, &metalNecesario, &construidos, &cantidadMax)){
		return false;
	}
	
	//Verifica que se tengan todos los materiales
	if(!verificarMateriales(nombreIngresado, piedraNecesaria, maderaNecesaria, metalNecesario, construidos, cantidadMax))
		return false;
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombreIngresado << "? Ingrese la primer coordenada: " << endl;
	cin >> fila;
	cout << "Ingrese la segunda coordenada: " << endl;
	cin >> columna;
	
	if(!verificarCoordenadas(fila, columna))
		return false;
	
	char respuesta;
	bool done = false;
	
	std::cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	do{
		cin >> respuesta;
		Edificio* edificio;
		int posicionEdificio;
		switch(respuesta){
			case 'y':
				cout << "El edificio ha sido construido correctamente" << endl << endl;
				edificio  = new Edificio (fila , columna);
				posicionEdificio = identificarEdificio(nombreIngresado);
				listaEdificios[posicionEdificio] -> agregarEdificioConstruido(edificio);

				mapa -> obtenerCasillero(fila, columna) -> establecerTipo(nombreIngresado);
				for(int i = 0; i < cantidadMateriales; i++){
					if(material[i]->obtenerNombreMaterial() == "piedra")
						material[i]->modificarCantidad(piedraNecesaria);
					if(material[i]->obtenerNombreMaterial() == "madera")
						material[i]->modificarCantidad(maderaNecesaria);
					if(material[i]->obtenerNombreMaterial() == "metal")
						material[i]->modificarCantidad(metalNecesario);
				}

				done = true;
				break;
				
			case 'n':
				done = true;
				break;
				
			default:
				cout << "Ingrese una opción válida: ";
				break;
		}
	}while(!done);

	return true;

}

int pedirOpcion(){
	
	int opcionElegida = 0;
	cout << "Ingrese el número de la opción elegida: ";
	cin >> opcionElegida;
	
	while(opcionElegida < 1 || opcionElegida > 10){
		cout << "La opción elegida no es válida" << endl << "Ingrese una opción válida: ";
		cin >> opcionElegida;
	}
	
	return opcionElegida;
}

void procesarOpciones(Juego* juego, int opcion){
	
	string nombreIngresado;
	
	switch(opcion){
        case MODIFICAR_EDIFICIO_POR_NOMBRE:
            modificarEdificioPorNombre();
            break;
        case LISTAR_EDIFICIOS:
            listarEdificios();
            break;
        case MOSTRAR_MAPA:
            mostrarMapa();
            break;
        case COMENZAR_PARTIDA:
            comenzarPartida();
            break;
        case GUARDAR_Y_SALIR:
            opcion = SALIR;
            break;
        default:
            cout << "ERROR" << endl;
            break;

/*
		case 1:
			cout << "Ingrese el nombre del edificio que desea construir: ";
			cin >> nombreIngresado;
			construirEdificio(nombreIngresado);
			break;
			
		case 2:
			listarEdificiosConstruidos();
			break;
		
		case 3:
			listarEdificios();
			break;
		
		case 4:
			demolerEdificioCoordenada();
			break;
		
		case 5:
			mostrarMapa();
			break;
		
		case 6:
			consultarCoordenada();
			break;
			
		case 7:
			mostrarInventario();
			break;
		
		case 8:
			recolectarRecursos();
			break;
		
		case 9:
			lluviaElementos();
			break;
		
		case 10:
			guardarYSalir();
			break;
            */
	}
}

void demolerEdificioCoordenada(Juego* juego){
	int fila, columna;
	mapa -> pedirCoordenada(fila, columna);
	int posicion;
	if (mapa -> sePuedeDemoler(fila, columna)){

		posicion = identificarEdificio(mapa -> obtenerCasillero(fila, columna) -> obtenerTipo());

		mapa -> obtenerCasillero(fila, columna) -> liberar ();
		aumentarMaterialesDerrumbe(listaEdificios[posicion]);

	}
}

void consultarCoordenada(Juego* juego){
	int fila,columna;
	mapa -> pedirCoordenada(fila,columna);
	mapa -> obtenerCasillero(fila, columna) -> responder();
}




