#include <iostream>
#include "Menu.hpp"
#include "../constantes/opciones.h"

using namespace std;

// Constructor
Menu::Menu() {
    juego = new Juego;
	partidaGanada = false;
}

// Destructor
Menu::~Menu() {
	delete juego;
}

// Iniciar juego
void Menu::iniciarJuego() {
    int opcion = MENU_ERROR;

	while(((juego -> obtenerJugadorActivo() > -1) ? (opcion != JUGADOR_GUARDAR_Y_SALIR) : (opcion != MENU_GUARDAR_Y_SALIR))) {
		mostrarMenu();
		pedirOpcion(&opcion);
		validarOpcionSeleccionada(opcion);
		//system(CLR_SCREEN);
		procesarOpciones(opcion);
		if(partidaGanada)
			ganarPartida(&opcion);
	}
}

// *************** MENU ***************

void Menu::mostrarMenuPrincipal() {

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

void Menu::procesarOpcionesMenu(int& opcion) {
	
    switch(opcion) {
        case MENU_MODIFICAR_EDIFICIO_POR_NOMBRE:
            modificarEdificioPorNombre();
            break;

        case MENU_LISTAR_EDIFICIOS:
        	juego -> listarEdificios();
            break;

        case MENU_MOSTRAR_MAPA:
			juego -> obtenerMapa() -> mostrarMapa();
            break;

        case MENU_COMENZAR_PARTIDA:
			comenzarPartida();
            break;

        case MENU_GUARDAR_Y_SALIR:
            break;
	}
}

void Menu::modificarEdificioPorNombre() {
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

void Menu::comenzarPartida() {
	seleccionarJugador();
	solicitarCoordenadas();

	if(juego -> obtenerJugadorActivo() == 0)
		juego -> establecerJugadorActivo(1);
	else 
		juego -> establecerJugadorActivo(0);

	solicitarCoordenadas();

	elegirJugador();
}

void Menu::elegirJugador() {
	juego -> establecerJugadorActivo(rand() % 2);
}

void Menu::seleccionarJugador() {
	int opcion;
	cout << "¿Que jugador desea ser? Seleccione 1 o 2" << endl;
	cin >> opcion;
	while(opcion != 1 && opcion != 2) {
		cout << "La opcion ingresada es incorrecta, por favor ingrese nuevamente." << endl;
		cin >> opcion;
	}
	juego -> establecerJugadorActivo(opcion - 1);
}

void Menu::solicitarCoordenadas() {
	int fila = -1, columna = -1;
	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
	while(juego -> verificarCoordenadas(fila, columna) == false)
		juego -> obtenerMapa() -> pedirCoordenada(fila, columna);
}

void Menu::mostrarSubmenu() {
	juego -> obtenerMapa() -> mostrarMapa();
	mostrarInformacion();
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

void Menu::procesarOpcionesSubmenu(int& opcion) {

	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
    switch(opcion) {
        case JUGADOR_CONSTRUIR_EDIFICIO_POR_NOMBRE:
			if(energiaActual < ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE){
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else {
				construirEdificioPorNombre();
			}
			break;

		case JUGADOR_LISTAR_MIS_EDIFICIOS_CONSTRUIDOS:
			listarEdificiosConstruidos();
			break;

		case JUGADOR_DEMOLER_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else 
				demolerEdificioPorCoordenada();
			break;

		case JUGADOR_ATACAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA)
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			else 
				atacarEdificioPorCoordenada();
			break;

		case JUGADOR_REPARAR_EDIFICIO_POR_COORDENADA:
			if(energiaActual < ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA)
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			else
				repararEdificioPorCoordenada(); 
			break;

		case JUGADOR_COMPRAR_BOMBAS:
			if(energiaActual < ENERGIA_POR_COMPRAR_BOMBA) {
				cout << "Su energia actual es de: " << energiaActual << "no le alcanza para realizar esta accion." << endl;
			}
			else
				comprarBomba();
			break;

		case JUGADOR_CONSULTAR_COORDENADA:
			consultarCoordenada();
			break;

		case JUGADOR_MOSTRAR_INVENTARIO:
			mostrarInventario();
			break;

		case JUGADOR_MOSTRAR_OBJETIVOS:
			mostrarObjetivos();
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
			finalizarTurno();
			break;

		case JUGADOR_GUARDAR_Y_SALIR:
			break;
    }
}

void Menu::mostrarInformacion() {
	int energiaActual = juego -> obtenerJugador() -> obtenerEnergia();
	int cantidadAndycoins = juego -> obtenerJugador() -> buscarMaterial("andycoins") -> obtenerCantidadMaterial();
	cout << endl << '\t' << "Es el turno del Jugador " << juego -> obtenerJugadorActivo() + 1 << endl;
	cout << '\t' << "Su energia actual es: " << energiaActual << endl;
	cout << '\t' << "Su cantidad de andycoins actual es: " << cantidadAndycoins << endl << endl;
}

void Menu::construirEdificioPorNombre() {
	string nombreIngresado;
	int piedraNecesaria, maderaNecesaria, metalNecesario;
	cout << "Ingrese el nombre del edifico que desea construir." << endl;
	cin.ignore();
	getline(cin, nombreIngresado);

	if(juego -> verificarEdificio(nombreIngresado, &piedraNecesaria, &maderaNecesaria, &metalNecesario))
		return;	
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombreIngresado << "? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;
	
	cout << "1" << endl;
	if(juego -> verificarCoordenadas(fila, columna))
		return;
	cout << "2" << endl;
	
	char respuesta = confirmacionConstruccion(nombreIngresado);
	cout << "3" << endl;
	
	if (respuesta == 'y') {
		if(nombreIngresado == OBELISCO){
		cout << "1" << endl;

			partidaGanada = true;
		} else
			construirEdificio(fila, columna, nombreIngresado, piedraNecesaria, maderaNecesaria, metalNecesario);
	}
}

void Menu::construirEdificio(int fila, int columna, string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario) {
	cout << "El edificio ha sido construido correctamente" << endl << endl;
	static_cast<CasilleroConstruible *>(juego -> obtenerMapa() -> obtenerCasillero(fila, columna)) -> agregarEdifico(nombreIngresado, juego);
	juego -> obtenerJugador() -> buscarMaterial(PIEDRA) -> modificarCantidad(-piedraNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(MADERA) -> modificarCantidad(-maderaNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(METAL) -> modificarCantidad(-metalNecesario);
	juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE);
	juego -> obtenerJugador() -> agregarEdificioConstruido(nombreIngresado);
	if(nombreIngresado == ESCUELA)
		juego -> obtenerJugador() -> letrado(
			juego -> obtenerMapa() -> edificiosContruidos(ESCUELA, juego -> obtenerJugadorActivo()) >=
			juego -> obtenerAbb() -> buscar(ESCUELA) -> obtenerMaximoConstruible()
		);
	if(nombreIngresado == OBELISCO)
		partidaGanada = true;
};

char Menu::confirmacionConstruccion(string nombreIngresado) {
	char respuesta;
	
	std::cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	cin >> respuesta;
	while (respuesta != 'y' && respuesta != 'n') {
		cout << "Ingrese una opción válida: [y/n]";
		cin >> respuesta;
	}

	return respuesta;
}
 
void Menu::listarEdificiosConstruidos() {
	Casillero* casillero;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════" << endl;
	cout << "             Nombre\t\tUbicacion              " << endl;
	cout << "            ══════════════════════════════════" << endl;
	
	for(int fila = 0; fila < juego -> obtenerMapa() -> obtenerCantidadFilas(); fila++) {
		for(int columna = 0; columna < juego -> obtenerMapa() -> obtenerCantidadColumnas(); columna++) {
			casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
			if((casillero -> obtenerTipo() == TERRENO) && (casillero -> obtenerCaracter() != CARACTER_VACIO)
			&& static_cast<CasilleroConstruible *>(casillero) -> obtenerPropietarioEdificio() == juego -> obtenerJugadorActivo()) {
				cout << "             " << static_cast<CasilleroConstruible *>(casillero) -> obtenerEdificio() << " \t\t (" << fila << ", " << columna << ")" << endl;
			}
		}
	}
	cout << endl;
}

void Menu::demolerEdificioPorCoordenada() {
	int fila, columna;
	cout << "¿Qué edificio desea demoler? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;

	Casillero* casillero;
	int propietario;


	casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
	if((casillero -> obtenerTipo() == TERRENO) && 
		(propietario = static_cast<CasilleroConstruible *>(casillero) -> obtenerPropietarioEdificio() > -1)) {
		string edificio = (static_cast<CasilleroConstruible*>(casillero) -> obtenerEdificio());
		cout << "Se ha demolido el edificio " << edificio << endl; 
		juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA);
		
		juego -> obtenerJugador() -> buscarMaterial(PIEDRA) -> modificarCantidad(juego -> obtenerAbb() -> buscar(edificio) -> obtenerMaterial(PIEDRA) / 2);
		juego -> obtenerJugador() -> buscarMaterial(MADERA) -> modificarCantidad(juego -> obtenerAbb() -> buscar(MADERA) -> obtenerMaterial(PIEDRA) / 2);
		juego -> obtenerJugador() -> buscarMaterial(METAL) -> modificarCantidad(juego -> obtenerAbb() -> buscar(edificio) -> obtenerMaterial(METAL) / 2);

	} 
	else
		cout << "No hay un edificio en ese casillero" << endl;
	
	return;
}

void Menu::atacarEdificioPorCoordenada() {
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
		(propietario = static_cast<CasilleroConstruible*>(casillero) -> obtenerPropietarioEdificio()) > -1
		) {
		if(propietario == juego -> obtenerJugadorActivo())
			cout << "No puedes atacar tu propio edifico" << endl;
		else {
			string edificio = static_cast<CasilleroConstruible*>(casillero) -> obtenerEdificio();
			cout << "Se ha " << ((static_cast<CasilleroConstruible *>(casillero) -> atacarEdificio()) ? "atacado" : "destruido") << " el edificio " << edificio << endl; 			juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA);
			juego -> obtenerJugador() -> buscarMaterial(BOMBAS) -> modificarCantidad(-1);
			juego -> obtenerJugador() -> aumentarBombasUsadas(1);
		}
	} 
	else
		cout << "No hay un edificio en ese casillero" << endl;

	return;
}

void Menu::repararEdificioPorCoordenada() {
	int fila, columna;
	cout << "¿Qué edificio desea reparar? Ingrese la primer coordenada: ";
	cin >> fila;
	cout << "Ingrese la segunda coordenada: ";
	cin >> columna;
	Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
	int propietario;
	
	if(casillero -> obtenerTipo() != TERRENO)
		cout << "No es un casillero construible, no hay ningun edificio" << endl;

	else {
		CasilleroConstruible* casilleroConstruible = static_cast<CasilleroConstruible*>(casillero);
		Receta* receta = juego -> obtenerAbb() -> buscar(casilleroConstruible -> obtenerEdificio());
		for(int i = 0; i < 3; i++) {
			if(juego -> obtenerJugador() -> buscarMaterial(MATERIALES_CONSTRUCCION[i]) -> obtenerCantidadMaterial() < 
			(receta -> obtenerMaterial(MATERIALES_CONSTRUCCION[i]) / 4)) {
				cout <<"Te faltan " << receta -> obtenerMaterial(MATERIALES_CONSTRUCCION[i]) - juego -> obtenerJugador() -> 
				buscarMaterial(MATERIALES_CONSTRUCCION[i]) -> obtenerCantidadMaterial() << " de " << MATERIALES_CONSTRUCCION[i] << 
				" para contruir el edificio" << endl; 
			}
		}

		if((propietario = (static_cast<CasilleroConstruible*>(casillero) -> obtenerPropietarioEdificio())) > -1) {
			if(propietario != juego -> obtenerJugadorActivo())
				cout << "No puedes reparar un edificio que no te pertenece" << endl;
			else {
				repararEdificio(casillero);
			}
		}
		else
			cout << "No hay un edificio en ese casillero" << endl;
	}
}

void Menu::repararEdificio(Casillero* casillero) {
	CasilleroConstruible* casilleroConstruible = static_cast<CasilleroConstruible*>(casillero);
	int piedraNecesaria = 0, maderaNecesaria = 0, metalNecesario = 0;

	string edificio = static_cast<CasilleroConstruible*>(casillero) -> obtenerEdificio();
	string nombre = casilleroConstruible -> obtenerEdificio();
	
	juego -> verificarEdificio(nombre, &piedraNecesaria, &maderaNecesaria, &metalNecesario);
	juego -> obtenerJugador() -> buscarMaterial(PIEDRA) -> modificarCantidad(-piedraNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(MADERA) -> modificarCantidad(-maderaNecesaria);
	juego -> obtenerJugador() -> buscarMaterial(METAL) -> modificarCantidad(-metalNecesario);
	juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA);

	cout << "Se ha reparado el edificio " << edificio << endl; 
}

void Menu::comprarBomba() {
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
		juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_COMPRAR_BOMBA);
		cout << "Ahora cuenta con " << cantidadAndycoins << " de andycoins" << endl;
	}
}

void Menu::consultarCoordenada() {
	int fila = -1, columna = -1;

	juego -> obtenerMapa() -> pedirCoordenada(fila, columna);

	Casillero* casillero = juego -> obtenerMapa() -> obtenerCasillero(fila, columna);
	if(casillero -> obtenerTipo() == TERRENO) 
		static_cast<CasilleroConstruible*>(casillero) -> responder();
	else if(casillero -> obtenerTipo() == CAMINO)
		static_cast<CasilleroTransitable*>(casillero) -> responder();
	else if(casillero -> obtenerTipo() == LAGO)
		static_cast<CasilleroInaccesible*>(casillero) -> responder();
	
}

void Menu::mostrarInventario() {

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

void Menu::mostrarObjetivos() {
	int* objetivosJugador = juego -> obtenerJugador() -> obtenerObjetivos();
	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++) {
		cout << OBJETIVOS[objetivosJugador[i]] << ": " ;
		mostrarProgresoObjetivos(objetivosJugador[i]);
	}
}

void Menu::mostrarProgresoObjetivos(int objetivos) {
	switch(objetivos) {
		case COMPRAR_ANDYPOLIS: 
			cout << (juego -> obtenerJugador() -> comprarAndypolis() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() -> 
			obtenerAndycoinsRecolectadas()) + " / " + to_string(CANTIDAD_ANDYCOINS_COMPRAR_ANDYPOLIS))) << endl;
			break;
		
		case EDAD_DE_PIEDRA:
			cout << (juego -> obtenerJugador() -> edadDePiedra() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() -> 
			buscarMaterial(PIEDRA) -> obtenerCantidadMaterial()) + " / " + to_string(CANTIDAD_EDAD_DE_PIEDRA))) << endl;
			break;

		case BOMBARDERO:
			cout << (juego -> obtenerJugador() -> bombardero() ? MJE_CUMPLIDO : (to_string(juego -> 
			obtenerJugador() -> obtenerCantidadBombasUsadas()) + " / " + to_string(CANTIDAD_BOMBARDERO))) << endl;
			break;

		case ENERGETICO:
			cout << (juego -> obtenerJugador() -> energetico() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() -> 
			obtenerEnergia()) + " / " + to_string(CANTIDAD_MAXIMA_ENERGIA))) << endl;
			break;

		case LETRADO:
			//cout << (juego -> obtenerJugador() -> letrado() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() ->
			//obtenerCantidadEscuelasConstruidas()) + " / " + to_string(juego -> obtenerAbb() -> buscar(ESCUELA) -> obtenerMaximoConstruible))) << endl;
			break;

		case MINERO:
			cout << (juego -> obtenerJugador() -> minero() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() ->
			minasConstruidas()) + " / 2" )) << endl;
			break;

		case CANSADO:
			cout << (juego -> obtenerJugador() -> cansado() ? MJE_CUMPLIDO : to_string(juego -> obtenerJugador() ->
			obtenerEnergia()) + " / " + to_string(CANTIDAD_MINIMA_ENERGIA)) << endl;
			break;
		
		case CONSTRUCTOR:
			cout << (juego -> obtenerJugador() -> constructor() ? MJE_CUMPLIDO : to_string(juego -> obtenerJugador() ->
			edificiosContruidos()) + " / " + to_string(juego -> obtenerCantidadEdificios())) << endl;
			break;

		case ARMADO:
			cout << (juego -> obtenerJugador() -> armado() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() -> 
			buscarMaterial(BOMBAS) -> obtenerCantidadMaterial()) + " / " + to_string(CANTIDAD_ARMADO))) << endl;
			break;

		case EXTREMISTA:
			cout << (juego -> obtenerJugador() -> extremista() ? MJE_CUMPLIDO : (to_string(juego -> obtenerJugador() -> 
			obtenerCantidadBombasCompradas()) + " / " + to_string(CANTIDAD_EXTREMISTA))) << endl;
			break;
	}
}

void Menu::moverseAUnaCoordenada(Juego *juego) {
	string coordenada;
	int xCoord = 0, yCoord = 0, energiaGastada = 0;
	
	juego -> crearCaminos();
	cout << "Ingrese la coordenada a la que desea moverse (ej: 0,1): ";
	cin >> coordenada;
	string posicionActual = juego -> obtenerMapa() -> obtenerPosicionJugador(juego -> obtenerJugadorActivo());
	cout << "Posicion Actual: " << posicionActual << endl << endl;
	juego -> mostrarCaminoMinimo(posicionActual, coordenada, &energiaGastada);
	cout << endl;
	
	if(juego -> obtenerJugador() -> obtenerEnergia() >= energiaGastada){
		xCoord = stoi(&coordenada[0]);
		yCoord = stoi(&coordenada[2]);
		juego -> obtenerMapa() -> obtenerCasillero(stoi(&posicionActual[0]), stoi(&posicionActual[2])) -> removerJugador(juego -> obtenerJugadorActivo());
		juego -> obtenerMapa() -> obtenerCasillero(xCoord, yCoord) -> setearJugador(juego -> obtenerJugadorActivo());
		juego -> obtenerJugador() -> restarEnergia(energiaGastada);
	}
	else{
		int opcion = 0;
		cout << "No tiene suficiente energía para completar esta acción. Puede elegir otra coordenada(1) o volver al menú(2)" << endl;
		cout << "Ingrese la opción elegida: ";
		cin >> opcion;
		if(opcion == 1)
			moverseAUnaCoordenada(juego);
	}
}

void Menu::finalizarTurno() {
	juego -> obtenerJugador() -> modificarEnergia(ENERGIA_POR_FINALIZAR_TURNO);
	cout << "Su energia ahora es: " << juego -> obtenerJugador() -> obtenerEnergia() << endl;
	if(juego -> obtenerJugadorActivo() == 1)
		juego -> lluviaElementos();
	juego -> establecerJugadorActivo(juego -> obtenerJugadorActivo() ? 0 : 1);
}

void Menu::chequearObjetivos() {
	int* objetivosJugador = juego -> obtenerJugador() -> obtenerObjetivos();
	int cantidadCumplidos = 0;
	bool objetivosCumplidos = false;
	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++) {
		switch(objetivosJugador[i]) {
			case COMPRAR_ANDYPOLIS:
				if(juego -> obtenerJugador() -> comprarAndypolis()) cantidadCumplidos++;
				break;
			case EDAD_DE_PIEDRA:
				if(juego -> obtenerJugador() -> edadDePiedra()) cantidadCumplidos++;
				break;
			case BOMBARDERO:
				if(juego -> obtenerJugador() -> bombardero()) cantidadCumplidos++;
				break;
			case ENERGETICO: 
				if(juego -> obtenerJugador() -> energetico()) cantidadCumplidos++;
				break;
			case LETRADO:
				if(juego -> obtenerJugador() -> letrado()) cantidadCumplidos++;
				break;
			case MINERO:
				if(juego -> obtenerJugador() -> minero()) cantidadCumplidos++;
				break;
			case CANSADO:
				if(juego -> obtenerJugador() -> cansado()) cantidadCumplidos++;
				break;
			case CONSTRUCTOR:
				if(juego -> obtenerJugador() -> constructor()) cantidadCumplidos++;
				break;
			case ARMADO:
				if(juego -> obtenerJugador() -> armado()) cantidadCumplidos++;
				break;
			case EXTREMISTA:
				if(juego -> obtenerJugador() -> extremista()) cantidadCumplidos++;
				break;
		}
	}
	if(cantidadCumplidos == 3 || juego -> obtenerJugador() -> masAltoQueLasNubes())
		objetivosCumplidos = true;
	partidaGanada  = objetivosCumplidos;
}

// *************** GENERALES ***************

void Menu::mostrarMenu() {
	(juego -> obtenerJugadorActivo() < 0 && juego -> esPartidaNueva() == true)	?  mostrarMenuPrincipal() : mostrarSubmenu();
}

void Menu::pedirOpcion(int* opcion) {
	cout << "Ingrese el numero de la accion que desea realizar." << endl;
	cin >> *opcion;
}

void Menu::validarOpcionSeleccionada(int& opcionSeleccionada) {
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

void Menu::procesarOpciones(int opcion) {
	string nombreIngresado;
    if(juego -> obtenerJugadorActivo() < 0)
        procesarOpcionesMenu(opcion);
    else {
        procesarOpcionesSubmenu(opcion);
	}
}

void Menu::ganarPartida(int* opcion) {
	cout << "Cumpliste todos los objetivos! Felicitaciones, has ganado el juego!" << endl;
	*opcion = JUGADOR_GUARDAR_Y_SALIR;
}
