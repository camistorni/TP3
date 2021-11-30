#include <iostream>
#include "utilesMenu.h"
#include "juego.h"
#include "opciones.h"
#include "constantesJugador.h"
#include "mensajes.h"


// *************** MENU ***************

void mostrarMenu() {

	cout << endl << endl;
	cout << TXT_ITALIC << TXT_LIGHT_AQUA_123 << "\t            ¡BIENVENIDOS A ANDYPOLIS!" << END_COLOR << endl << endl;
	cout << "                        " << TXT_UNDERLINE << "Menú de opciones" << END_COLOR << endl << endl;
	cout << "            ╔═══════════════════════════════════════╗" << endl;
	cout << "            ║ 1. Modificar edificio por nombre      ║" << endl;
	cout << "            ║ 2. Listar todos los edificios         ║" << endl;
	cout << "            ║ 3. Mostrat mapa                       ║" << endl;
	cout << "            ║ 4. Comenzar partida                   ║" << endl;
	cout << "            ║ 5. Guardar y salir                    ║" << endl;
	cout << "            ╚═══════════════════════════════════════╝" << endl << endl;
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
			juego -> obtenerMapa() -> mostrarMapa();
            break;

        case COMENZAR_PARTIDA:
			comenzarPartida(juego);
            break;

        case GUARDAR_Y_SALIR:
            opcion = SALIR;
            break;

        default:
            cout << MJE_ERROR_OPCION << endl;
            break;
	}
}

void comenzarPartida(Juego* juego) {

	seleccionarJugador(juego);
	solicitarCoordenadas(juego);

	if(juego -> obtenerJugadorActivo() == 0)
		juego -> establecerJugadorActivo(1);
	else 
		juego -> establecerJugadorActivo(0);

	solicitarCoordenadas(juego);

	elegirJugador(juego);
}

void elegirJugador(Juego* juego) {
	juego -> establecerJugadorActivo(rand() % 2);
}

void seleccionarJugador(Juego* juego) {
	int opcion;
	cout << "¿Que jugador desea ser? Seleccione 1 o 2" << endl;
	cin >> opcion;
	while(opcion != 1 && opcion != 2) {
		cout << "La opcion ingresada es incorrecta, por favor ingrese nuevamente." << endl;
		cin >> opcion;
	}
	juego -> establecerJugadorActivo(opcion - 1);
}

void solicitarCoordenadas(Juego* juego) {
	int fila = -1, columna = -1;

	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	while(juego -> verificarCoordenadas(fila, columna) == false)
		juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	
	juego -> obtenerJugador() -> establecerCoordenadas(fila, columna);
}


// *************** SUBMENU ***************

void mostrarSubmenu() {
	cout << endl << endl;
	cout << TXT_ITALIC << TXT_LIGHT_AQUA_123 << "\t            ¡BIENVENIDOS A ANDYPOLIS!" << END_COLOR << endl << endl;
	cout << "                        " << TXT_UNDERLINE << "Menú de opciones" << END_COLOR << endl << endl;
	cout << "            ╔═══════════════════════════════════════╗" << endl;
	cout << "            ║ 1. Construir edificio por nombre      ║" << endl;
	cout << "            ║ 2. Listar mis edificios construidos   ║" << endl;
	cout << "            ║ 3. Demoler un edificio por coordenada ║" << endl;
	cout << "            ║ 4. Atacar un edificio por coordenada  ║" << endl;
	cout << "            ║ 5. Reparar un edificio por coordenada ║" << endl;
	cout << "            ║ 6. Comprar bombas                     ║" << endl;
	cout << "            ║ 7. Consultar coordenada               ║" << endl;
	cout << "            ║ 8. Mostrar inventario                 ║" << endl;
	cout << "            ║ 9. Mostrar objetivos                  ║" << endl;
	cout << "            ║ 10. Recolectar recursos producidos    ║" << endl;
	cout << "            ║ 11. Moverse a una coordenada          ║" << endl;
	cout << "            ║ 12. Finalizar turno                   ║" << endl;
	cout << "            ║ 13. Guardar y salir                   ║" << endl;
	cout << "            ╚═══════════════════════════════════════╝" << endl << endl;
}

void procesarOpcionesSubmenu(Juego* juego, int opcion) {
	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
    switch(opcion) {
        case CONSTRUIR_EDIFICIO_POR_NOMBRE:
			if(energiaActual < ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE){
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE);
				// CONSTUIR EL EDIFICIO
				//construirEdificio(nombreIngresado);
			}
			break;

		case LISTAR_MIS_EDIFICIOS_CONSTRUIDOS:
			//juego -> listarEdificiosConstruidos();
			break;

		case DEMOLER_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA);
				// demolerEdificioPorCoordenada();
			}
			break;

		case ATACAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA);
				// atacarEdificioPorCoordenada();
			}
			break;

		case REPARAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA);
				// repararEdificioPorCoordenada();
			}
			break;

		case COMPRAR_BOMBAS:
			if(energiaActual < ENERGIA_POR_COMPRAR_BOMBA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_COMPRAR_BOMBA);
				// comprarBomba();
			}
			break;

		case CONSULTAR_COORDENADA:
			consultarCoordenada(juego);
			break;

		case MOSTRAR_INVENTARIO:
			mostrarInventario(juego);
			break;

		case MOSTRAR_OBJETIVOS:
			mostrarObjetivos(juego);
			break;

		case RECOLECTAR_RECURSOS_PRODUCIDOS:
			if(energiaActual < ENERGIA_POR_RECOLECTAR_RECURSOS_PRODUCIDOS) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
				opcion = FINALIZAR_TURNO;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_RECOLECTAR_RECURSOS_PRODUCIDOS);
				juego -> recolectarRecursos();
			}
			break;

		case MOVERSE_A_UNA_COORDENADA:
            break;

		case FINALIZAR_TURNO:
			juego -> obtenerJugador() -> establecerEnergia(energiaActual + ENERGIA_POR_FINALIZAR_TURNO);
			cout << "Su energia ahora es: " << juego -> obtenerJugador() -> obtenerEnergia() << endl;
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
			cout << MJE_ERROR_OPCION << endl;
			break;
    }
}       

void mostrarObjetivos(Juego* juego) {
	int* objetivos;
	objetivos = juego -> obtenerJugador() -> obtenerObjetivos();

	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++)
		imprimirObjetivos(i);
}

void imprimirObjetivos(int objetivo) {
	static string objetivoActual[] = {
		MJE_COMPRAR_ANDYPOLIS,
		MJE_EDAD_DE_PIEDRA,
		MJE_BOMBARDERO,
		MJE_ENERGETICO,
		MJE_LETRADO,
		MJE_MINERO,
		MJE_CANSADO,
		MJE_CONSTRUCTOR,
		MJE_ARMADO,
		MJE_EXTREMISTA
	}
	cout << objetivoActual[objetivo] << endl;
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

void consultarCoordenada(Juego* juego) {
	int fila = -1, columna = -1;

	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	while(juego -> verificarCoordenadas(fila, columna) == false)
		juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	
	juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> responder();
}


// *************** GENERALES ***************

void pedirOpcion(int* opcion) {
	cout << "Ingrese el numero de la accion que desea realizar." << endl;
	cin >> *opcion;
}

void validarOpcionSeleccionada(int& opcionSeleccionada) {
	bool opcionValida = false;
	while(opcionValida == false) {
		if(cin.fail()) {
			cin.clear();
			cin.ignore(sizeof(int), '\n');
			cout << "La opcion elegida no es una opcion valida, por favor seleccione otra opcion" << endl;
			pedirOpcion(&opcionSeleccionada);
		}
		else if(opcionSeleccionada <= 0 || opcionSeleccionada > 13) {
			cout << "La opcion elegida no es una opcion valida, por favor seleccione otra opcion" << endl;
			pedirOpcion(&opcionSeleccionada);
		}
		else 
			opcionValida = true;
	}
	
}

void procesarOpciones(Juego* juego, int opcion) {
	
	string nombreIngresado;
	
    if(juego -> obtenerJugadorActivo() < 0) 
        procesarOpcionesMenu(juego, opcion);
    else
        procesarOpcionesSubmenu(juego, opcion);
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


