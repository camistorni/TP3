#include <iostream>
#include "utilesMenu.h"
#include "../juego/juego.h"
#include "../constantes/opciones.h"
#include "../jugadores/constantesJugador.h"
#include "../constantes/mensajes.h"
#include "../mapa/casilleros/casilleroConstruible/casilleroConstruible.h"

using namespace std;


// *************** MENU ***************

void mostrarMenuPrincipal() {

	cout << endl << endl;
	cout << TXT_ITALIC << TXT_LIGHT_AQUA_123 << "\t            ¡BIENVENIDOS A ANDYPOLIS!" << END_COLOR << endl << endl;
	cout << "                        " << TXT_UNDERLINE << "Menú de opciones" << END_COLOR << endl << endl;
	cout << "            ╔═══════════════════════════════════════╗" << endl;
	cout << "            ║ 1. Modificar edificio por nombre      ║" << endl;
	cout << "            ║ 2. Listar todos los edificios         ║" << endl;
	cout << "            ║ 3. Mostrar mapa                       ║" << endl;
	cout << "            ║ 4. Comenzar partida                   ║" << endl;
	cout << "            ║ 5. Guardar y salir                    ║" << endl;
	cout << "            ╚═══════════════════════════════════════╝" << endl << endl;
}

void procesarOpcionesMenu(Juego* juego, int opcion) {
	
    switch(opcion) {
        case MENU_MODIFICAR_EDIFICIO_POR_NOMBRE:
            //modificarEdificioPorNombre();
            break;

        case MENU_LISTAR_EDIFICIOS:
        	juego -> listarEdificios();
            break;

        case MENU_MOSTRAR_MAPA:
			juego -> obtenerMapa() -> mostrarMapa();
            break;

        case MENU_COMENZAR_PARTIDA:
			comenzarPartida(juego);
            break;

        case MENU_GUARDAR_Y_SALIR:
            break;

        /*default:
            cout << MJE_ERROR_OPCION << endl;
            break;*/
	}
}

void comenzarPartida(Juego* juego) {
	cout << "comenzarPartida" << endl;
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
	//juego -> obtenerJugador() -> establecerCoordenadas(fila, columna);
}


// *************** SUBMENU ***************

void mostrarSubmenu(Juego* juego) {
	mostrarInformacion(juego);
	cout << endl << endl;
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
        case JUGADOR_CONSTRUIR_EDIFICIO_POR_NOMBRE:
			if(energiaActual < ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE){
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE);
				// CONSTUIR EL EDIFICIO
				//construirEdificio(nombreIngresado);
			}
			break;

		case JUGADOR_LISTAR_MIS_EDIFICIOS_CONSTRUIDOS:
			//juego -> listarEdificiosConstruidos();
			break;

		case JUGADOR_DEMOLER_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA);
				// demolerEdificioPorCoordenada();
			}
			break;

		case JUGADOR_ATACAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA);
				// atacarEdificioPorCoordenada();
			}
			break;

		case JUGADOR_REPARAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA);
				// repararEdificioPorCoordenada();
			}
			break;

		case JUGADOR_COMPRAR_BOMBAS:
			if(energiaActual < ENERGIA_POR_COMPRAR_BOMBA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else if(comprarBomba(juego) == true)
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_COMPRAR_BOMBA);
			break;

		case JUGADOR_CONSULTAR_COORDENADA:
			consultarCoordenada(juego);
			break;

		case JUGADOR_MOSTRAR_INVENTARIO:
			mostrarInventario(juego);
			break;

		case JUGADOR_MOSTRAR_OBJETIVOS:
			mostrarObjetivos(juego);
			break;

		case JUGADOR_RECOLECTAR_RECURSOS_PRODUCIDOS:
			if(energiaActual < ENERGIA_POR_RECOLECTAR_RECURSOS_PRODUCIDOS) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				juego -> obtenerJugador() -> establecerEnergia(energiaActual - ENERGIA_POR_RECOLECTAR_RECURSOS_PRODUCIDOS);
				juego -> recolectarRecursos();
			}
			break;

		case JUGADOR_MOVERSE_A_UNA_COORDENADA:
            break;

		case JUGADOR_FINALIZAR_TURNO:
			juego -> obtenerJugador() -> establecerEnergia((energiaActual + ENERGIA_POR_FINALIZAR_TURNO)%101);
			cout << "Su energia ahora es: " << juego -> obtenerJugador() -> obtenerEnergia() << endl;
			juego -> establecerJugadorActivo(juego -> obtenerJugadorActivo() ? 0 : 1);
			break;

		case JUGADOR_GUARDAR_Y_SALIR:
			break;

		default:
			cout << MJE_ERROR_OPCION << endl;
			break;
    }
}

void mostrarInformacion(Juego* juego) {
	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
	int cantidadAndycoins = juego -> obtenerJugador() -> buscarMaterial("andycoins") -> obtenerCantidadMaterial();
	cout << endl << '\t' << "Es el turno del Jugador " << juego -> obtenerJugadorActivo() + 1 << endl;
	cout << '\t' << "Su energia actual es: " << energiaActual << endl;
	cout << '\t' << "Su cantidad de andycoins actual es: " << cantidadAndycoins << endl << endl;
}

void mostrarObjetivos(Juego* juego) {
	int* objetivosJugador = juego -> obtenerJugador() -> obtenerObjetivos();
	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++)
		cout << OBJETIVOS[objetivosJugador[i]] << endl;
}

void mostrarInventario(Juego* juego) {

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << '\t' << " ══════════════════════════════════ " << endl;
	cout << '\t' << " Materiales            Cantidades   " << endl;
	cout << '\t' << " ══════════════════════════════════ " << endl;

	for(int i = 0; i < juego -> obtenerCantidadMateriales(); i++) {
		cout << '\t' << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << ":\t" << 
		'\t' << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << endl;
	}
}

bool comprarBomba(Juego* juego) {
	bool accionRealizada = false;
	int cantidad = 0;
	int cantidadAndycoins = 0;
	cout << "Ingrese la cantidad de bombas que desee comprar" << endl;
	cin >> cantidad;
	cantidadAndycoins = juego -> obtenerJugador() -> buscarMaterial("andycoins") -> obtenerCantidadMaterial();
	int costoBombas = cantidad * COSTO_BOMBA;
	if(cantidadAndycoins < costoBombas) {
		cout << "No se pudieron adquirir la cantidad de bombas solicitas debido a que no le alcanzan las andycoins" << endl;
	}
	else {
		juego -> obtenerJugador() -> buscarMaterial("andycoins") -> establecerCantidad(cantidadAndycoins - costoBombas);
		int cantidadActualBombas = juego -> obtenerJugador() -> buscarMaterial("bombas") -> obtenerCantidadMaterial();
		juego -> obtenerJugador() -> buscarMaterial("bombas") -> establecerCantidad(cantidadActualBombas + cantidad);
		cout << "Ud adquirio " << cantidad << " de bombas" << endl;
		cout << "Ahora cuenta con " << cantidadAndycoins << " de andycoins" << endl;
		accionRealizada = true;
	}
	return accionRealizada;
}

void consultarCoordenada(Juego* juego) {
	int fila = -1, columna = -1;

	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	while(juego -> verificarCoordenadas(fila, columna) == false)
		juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	
	//juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> responder();
}


// *************** GENERALES ***************

void mostrarMenu(Juego* juego) {
	juego -> obtenerJugadorActivo() < 0 ?  mostrarMenuPrincipal() : mostrarSubmenu(juego);
}

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
	
	std::cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	cin >> respuesta;
	//Edificio* edificio;
	while (respuesta != 'y' && respuesta != 'n') {
		cout << "Ingrese una opción válida: ";
		cin >> respuesta;
	}
	if (respuesta == 'y') {
		cout << "El edificio ha sido construido correctamente" << endl << endl;
		static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> agregarEdifico(nombreIngresado, juego -> obtenerJugadorActivo());
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
