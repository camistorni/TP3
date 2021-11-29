#include <iostream>
#include "utilesMenu.h"
#include "juego.h"
#include "opciones.h"

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

void mostrarInventario(Juego* juego) {

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << '\t' << " ═══════════════════════════════ " << endl;
	cout << '\t' << " Materiales        Cantidades   " << endl;
	cout << '\t' << " ═══════════════════════════════ " << endl;

	for(int i = 0; i < juego -> obtenerCantidadMateriales(); i++) {
		cout << '\t' << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << ":\t" << 
		'\t' << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << endl;
	}
}

void construirEdificio(Juego* juego, string nombreIngresado) {
	int piedraNecesaria, maderaNecesaria, metalNecesario, construidos, cantidadMax;
	//Verifica que el edificio ingresado exista
	if(!juego -> verificarEdificio(nombreIngresado, &piedraNecesaria, &maderaNecesaria, &metalNecesario, &construidos, &cantidadMax)){
		std::cout << "El edificio '" << nombreIngresado << "' no existe" << endl << endl;
		return;
	}
	
	//Verifica que se tengan todos los materiales
	if(!juego -> verificarMateriales(nombreIngresado, piedraNecesaria, maderaNecesaria, metalNecesario, construidos, cantidadMax))
		return;
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombreIngresado << "? Ingrese la primer coordenada: " << endl;
	cin >> fila;
	cout << "Ingrese la segunda coordenada: " << endl;
	cin >> columna;
	
	if(juego -> verificarCoordenadas(fila, columna))
		return;
	
	char respuesta;
	bool done = false;
	
	std::cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	cin >> respuesta;
	Edificio* edificio;
	int posicionEdificio;
	while (respuesta != 'y' && respuesta != 'n') {
		cout << "Ingrese una opción válida: ";
		cin >> respuesta;
	}
	if (respuesta == 'y') {
		cout << "El edificio ha sido construido correctamente" << endl << endl;
		edificio  = new Edificio (fila , columna);
		juego -> obtenerEdificio(nombreIngresado) -> agregarEdificioConstruido(); // hay que hacer una lista de edificios construdidos para cada jugador
		//mapa -> obtenerCasillero(fila, columna) -> establecerTipo(nombreIngresado); //agregar metodo de devolver mapa
		juego -> obtenerJugador() -> buscarMaterial("piedra") -> modificarCantidad(piedraNecesaria);
		juego -> obtenerJugador() -> buscarMaterial("madera") -> modificarCantidad(piedraNecesaria);
		juego -> obtenerJugador() -> buscarMaterial("metal") -> modificarCantidad(piedraNecesaria);
	}
}

int pedirOpcion() {
	
	int opcionElegida = 0;
	cout << "Ingrese el número de la opción elegida: ";
	cin >> opcionElegida;
	
	while(opcionElegida < 1 || opcionElegida > 10){
		cout << "La opción elegida no es válida" << endl << "Ingrese una opción válida: ";
		cin >> opcionElegida;
	}
	
	return opcionElegida;
}

void procesarOpcionesMenu(Juego* juego, int opcion) {
    switch(opcion) {
        case MODIFICAR_EDIFICIO_POR_NOMBRE:
            //modificarEdificioPorNombre();
            break;

        case LISTAR_EDIFICIOS:
        	juego -> listarEdificios();
            break;

        case MOSTRAR_MAPA:
            //mostrarMapa();
            break;

        case COMENZAR_PARTIDA:
			int fila = -1, columna = -1;
			// Se hace dos veces, una para cada jugador, hay que ver como indicar de quien es cada posicion
			// Tambien hay que chequear si las coordenadas son validas o volver a pedirlas
			juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
			juego -> verificarCoordenadas(fila, columna);
			juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
			juego -> verificarCoordenadas(fila, columna);

            comenzarPartida(juego);
            break;

        case GUARDAR_Y_SALIR:
            opcion = SALIR;
            break;

        default:
            cout << "ERROR" << endl;
            break;
	}
}

void comenzarPartida(Juego* juego) {
	juego -> establecerJugadorActivo(rand() % 2);
}

void procesarOpcionesSubmenu(Juego* juego, int opcion) {
    switch(opcion) {
        case CONSTRUIR_EDIFICIO_POR_NOMBRE:
			//string nombreIngresado;
			cout << "Ingrese el nombre del edificio que desea construir" << endl;
			//cin >> nombreIngresado;
			//construirEdificio(nombreIngresado);
			break;

		case LISTAR_EDIFICIOS_CONSTRUIDOS:
			juego -> listarEdificiosConstruidos();
			break;

		case DEMOLER_EDIFICIO_POR_COORDENADA:
			//listarEdificios();
			break;

		case ATACAR_EDIFICIO_POR_COORDENADA:
			//demolerEdificioCoordenada();
			break;

		case REPARAR_EDIFICIO_POR_COORDENADA:
			//mostrarMapa();
			break;

		case COMPRAR_BOMBAS:
			//comprarBombas();
			break;

		case CONSULTAR_COORDENADA:
            //consultarCoordenada();
			break;

		case MOSTRAR_INVENTARIO:
			mostrarInventario(juego);
			break;

		case MOSTRAR_OBJETIVOS:
			break;

		case RECOLECTAR_RECURSOS_PRODUCIDOS:
			juego -> recolectarRecursos();
			break;

		case MOVERSE_A_UNA_COORDENADA:
            break;

		case FINALIZAR_TURNO:
			int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
			juego -> obtenerJugador() -> establecerEnergia(energiaActual + ENERGIA_POR_FINALIZAR_TURNO);
			if(juego -> obtenerJugadorActivo() == 0)
				juego -> establecerJugadorActivo(1);
			else
				juego -> establecerJugadorActivo(0);
			break;

		case GUARDAR_Y_SALIR:
			opcion = SALIR;
			break;

		case SALIR:
			break;

		default:
			cout << "ERROR" << endl;
			break;
    }
}       
        
void procesarOpciones(Juego* juego, int opcion) {
	
	string nombreIngresado;
	
    if(juego -> obtenerJugadorActivo() < 0) 
        procesarOpcionesMenu(juego, opcion);
    else
        procesarOpcionesSubmenu(juego, opcion);
}

/*
void demolerEdificioCoordenada(Juego* juego) {
	int fila, columna;
	mapa -> pedirCoordenada(fila, columna);
	int posicion;
	if (mapa -> sePuedeDemoler(fila, columna)){

		posicion = identificarEdificio(mapa -> obtenerCasillero(fila, columna) -> obtenerTipo());

		mapa -> obtenerCasillero(fila, columna) -> liberar ();
		aumentarMaterialesDerrumbe(listaEdificios[posicion]);

	}
}
*/
/*
void consultarCoordenada(Juego* juego) {
	int fila,columna;
	mapa -> pedirCoordenada(fila,columna);
	mapa -> obtenerCasillero(fila, columna) -> responder();
}
*/

