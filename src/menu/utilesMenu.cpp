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

void procesarOpcionesMenu(Juego* juego, int& opcion) {
	
    switch(opcion) {
        case MENU_MODIFICAR_EDIFICIO_POR_NOMBRE:
            modificarEdificioPorNombre(juego);
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

void modificarEdificioPorNombre(Juego* juego){
	// Validar que se ingresen datos correctos
	string edificio, material;
	int valor;
	cout << "¿Que edificio desea modificar?" << endl;
	cin >> edificio;
	cout << "¿Que material de esta la receta de este desea modificar?" << endl;
	cin >> material;
	cout << "¿Qué valor quiere asignarle?" << endl;
	cin >> valor;
	juego -> modificarEdificio(edificio, material, valor);

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
	//juego -> obtenerJugador() -> establecerCoordenadas(fila, columna);
}


// *************** SUBMENU ***************

void mostrarSubmenu(Juego* juego) {
	mostrarInformacion(juego);
	juego -> obtenerMapa() -> mostrarMapa();
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

void procesarOpcionesSubmenu(Juego* juego, int& opcion) {

	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
    switch(opcion) {
        case JUGADOR_CONSTRUIR_EDIFICIO_POR_NOMBRE:
			if(energiaActual < ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE){
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				construirEdificioPorCoordenada(juego);
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
			if(energiaActual < ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA)
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			else 
				atacarEdificioPorCoordenada(juego);
			break;

		case JUGADOR_REPARAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA)
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			else
				// Hay que terminarla
				// repararEdificioPorCoordenada; 
			break;

		case JUGADOR_COMPRAR_BOMBAS:
			if(energiaActual < ENERGIA_POR_COMPRAR_BOMBA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else
				comprarBomba(juego);
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
			moverseAUnaCoordenada(juego);
            break;

		case JUGADOR_FINALIZAR_TURNO:
			finalizarTurno(juego);
			break;
		case JUGADOR_GUARDAR_Y_SALIR:
			break;
			
		default:
			cout << MJE_ERROR_OPCION << endl;
			break;
    }
}

void finalizarTurno(Juego* juego) {
	juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_FINALIZAR_TURNO);
	cout << "Su energia ahora es: " << juego -> obtenerJugador() -> obtenerEnergia() << endl;
	if(juego -> obtenerJugadorActivo() == 1)
		juego -> lluviaElementos();
	juego -> establecerJugadorActivo(juego -> obtenerJugadorActivo() ? 0 : 1);
}

void moverseAUnaCoordenada(Juego* juego) {
	string coordenada;
	int xCoord = 0, yCoord = 0;
	juego -> crearCaminos();
	cout << "Ingrese la coordenada a la que desea moverse (ej: 0,1): ";
	cin >> coordenada;
	string posicionActual = juego -> obtenerMapa() -> obtenerPosicionJugador(juego -> obtenerJugadorActivo());
	cout << "Posicion Actual: " << posicionActual << endl;
	juego -> mostrarCaminoMinimo(posicionActual, coordenada);
	xCoord = stoi(&coordenada[0]);
	yCoord = stoi(&coordenada[2]);
	juego -> obtenerJugador() -> establecerCoordenadas(xCoord, yCoord);
	juego -> obtenerMapa() -> obtenerCasillero(stoi(&posicionActual[0]), stoi(&posicionActual[2])) -> removerJugador(juego -> obtenerJugadorActivo());
	juego -> obtenerMapa() -> obtenerCasillero(xCoord, yCoord) -> setearJugador(juego -> obtenerJugadorActivo());
}

void mostrarInformacion(Juego* juego) {
	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
	int cantidadAndycoins = juego -> obtenerJugador() -> buscarMaterial("andycoins") -> obtenerCantidadMaterial();
	cout << endl << '\t' << "Es el turno del Jugador " << juego -> obtenerJugadorActivo() + 1 << endl;
	cout << '\t' << "Su energia actual es: " << energiaActual << endl;
	cout << '\t' << "Su cantidad de andycoins actual es: " << cantidadAndycoins << endl << endl;
}

void mostrarProgresoObjetivos(Juego* juego, int i) {
	int* objetivosJugador = juego -> obtenerJugador() -> obtenerObjetivos();
	switch(objetivosJugador[i]) {
		case COMPRAR_ANDYPOLIS: 
			cout << juego -> obtenerJugador() -> buscarMaterial(ANDYCOINS) -> obtenerCantidadMaterial() 
			<< " / " << CANTIDAD_ANDYCOINS_COMPRAR_ANDYPOLIS << endl;
			break;
		
		case EDAD_DE_PIEDRA:
			cout << juego -> obtenerJugador() -> buscarMaterial(PIEDRA) -> obtenerCantidadMaterial() 
			<< " / " << CANTIDAD_EDAD_DE_PIEDRA << endl;
			break;

		case BOMBARDERO:
			// Este no se puede hacer todavia, hay que ir sumando la cantidad de piedras que se usan cuando atacas
			break;

		case ENERGETICO:
			cout << juego -> obtenerJugador() -> obtenerEnergia() << " / " << CANTIDAD_MAXIMA_ENERGIA << endl;
			break;

		case LETRADO:
			// Hay que ver como ver esto
			break;

		case MINERO:
			// Hay que ver como ver esto
			break;

		case CANSADO:
			cout << juego -> obtenerJugador() -> obtenerEnergia() << " / " << CANTIDAD_MINIMA_ENERGIA << endl;
			break;
		
		case CONSTRUCTOR:
			// hay que ver esto
			break;

		case ARMADO:
			cout << juego -> obtenerJugador() -> buscarMaterial(BOMBAS) -> obtenerCantidadMaterial() 
			<< " / " << CANTIDAD_ARMADO << endl;
			break;

		case EXTREMISTA:
			cout << juego -> obtenerJugador() -> obtenerCantidadBombasCompradas() << " / " << CANTIDAD_EXTREMISTA << endl;
			break;
	}
}

void mostrarObjetivos(Juego* juego) {
	int* objetivosJugador = juego -> obtenerJugador() -> obtenerObjetivos();
	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++) {
		cout << OBJETIVOS[objetivosJugador[i]] << ": " ;
		mostrarProgresoObjetivos(juego, i);
	}
}

void mostrarInventario(Juego* juego) {

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << '\t' << " ══════════════════════════════════ " << endl;
	cout << '\t' << " Materiales            Cantidades   " << endl;
	cout << '\t' << " ══════════════════════════════════ " << endl;

	for(int i = 0; i < juego -> obtenerCantidadMateriales(); i++) {
		cout << "\t  " << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerNombreMaterial() << ":\t" << 
		'\t' << juego -> obtenerJugador() -> obtenerMateriales()[i] -> obtenerCantidadMaterial() << endl;
	}
}

void comprarBomba(Juego* juego) {
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
		juego -> obtenerJugador() -> aumentarBombasCompradas(cantidad);
		cout << "Ud adquirio " << cantidad << " de bombas" << endl;
		cout << "Ahora cuenta con " << cantidadAndycoins << " de andycoins" << endl;
		juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_COMPRAR_BOMBA);
	}
}


/// HACER
void consultarCoordenada(Juego* juego) {
	int fila = -1, columna = -1;

	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	while(juego -> verificarCoordenadas(fila, columna) == false)
		juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	
	//juego -> obtenerMapa() -> obtenerCasillero(fila, columna) -> responder();
}

void atacarEdificioPorCoordenada(Juego* juego){
	if(juego -> obtenerJugador() -> buscarMaterial(BOMBAS) -> obtenerCantidadMaterial() < 1){
		cout << "No posee bombas en el inventario. No puede atacar edificios" << endl;
		return;
	}

	int fila, columna;
	cout << "¿Qué edificio desea atacar? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;

	Casillero* casillero;
	int propietario;

	if (
		(casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> obtenerTipo() == TERRENO &&
		(propietario = static_cast<CasilleroConstruible *>(casillero) -> obtenerPropietarioEdificio()) > -1
		) {
		if(propietario == juego -> obtenerJugadorActivo())
			cout << "No puedes atacar tu propio edifico" << endl;
		else {
			string edificio = static_cast<CasilleroConstruible *>(casillero) -> obtenerEdificio();
			cout << "Se ha " << ((static_cast<CasilleroConstruible *>(casillero) -> atacarEdificio()) ? "atacado" : "destruido") << " el edificio " << edificio << endl; 
			juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA);
			juego -> obtenerJugador() -> buscarMaterial(BOMBAS) -> modificarCantidad(-1);
		}
	} 
	else
		cout << "No hay un edificio en ese casillero" << endl;

	return;
}

void repararEdificioPorCoordenada(Juego* juego) {
	
	// Chequear si tengo los materiales necesarios. Es el 25% de lo que se necesita para constuir uno nuevo

	int fila, columna;
	cout << "¿Qué edificio desea reparar? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;

	Casillero* casillero;
	int propietario;

	if (
		(casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> obtenerTipo() == TERRENO &&
		(propietario = static_cast<CasilleroConstruible *>(casillero) -> obtenerPropietarioEdificio()) > -1
		) {
		if(propietario != juego -> obtenerJugadorActivo())
			cout << "No puedes reparar un edificio que no te pertenece" << endl;
		else {
			string edificio = static_cast<CasilleroConstruible *>(casillero) -> obtenerEdificio();
			cout << "Se ha reparado el edificio " << edificio << endl; 
			juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA);
			// modificar la cantidad de materiales
		}
	} 
	else
		cout << "No hay un edificio en ese casillero" << endl;

	return;
}

// *************** GENERALES ***************

void mostrarMenu(Juego* juego) {
	(juego -> obtenerJugadorActivo() < 0 && juego -> esPartidaNueva() == true)	?  mostrarMenuPrincipal() : mostrarSubmenu(juego);
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
    else {
        procesarOpcionesSubmenu(juego, opcion);
	}
}

void construirEdificioPorCoordenada(Juego* juego) {
	string nombreIngresado = "";
	int piedraNecesaria, maderaNecesaria, metalNecesario;
	cout << "Ingrese el nombre del edifico que desea construir." << endl;
	cin >> nombreIngresado;
	//Verifica que el edificio ingresado exista
	if(juego -> verificarEdificio(nombreIngresado, &piedraNecesaria, &maderaNecesaria, &metalNecesario))
		return;	
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombreIngresado << "? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;
	
	if(juego -> verificarCoordenadas(fila, columna))
		return;
	
	char respuesta = confirmacionConstruccion(nombreIngresado);
	
	if (respuesta == 'y') 
		construirEdificio(juego, fila, columna, nombreIngresado, piedraNecesaria, maderaNecesaria, metalNecesario);
}

void construirEdificio(Juego* juego, int fila, int columna, string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario) {
	cout << "El edificio ha sido construido correctamente" << endl << endl;
	static_cast<CasilleroConstruible*>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> agregarEdifico(nombreIngresado, juego -> obtenerJugadorActivo());
	juego -> obtenerJugador() -> buscarMaterial(PIEDRA) -> modificarCantidad(-piedraNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(MADERA) -> modificarCantidad(-maderaNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(METAL) -> modificarCantidad(-metalNecesario);
	juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE);
};

char confirmacionConstruccion(string nombreIngresado) {
	char respuesta;
	
	std::cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	cin >> respuesta;
	while (respuesta != 'y' && respuesta != 'n') {
		cout << "Ingrese una opción válida: [y/n]";
		cin >> respuesta;
	}

	return respuesta;
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
