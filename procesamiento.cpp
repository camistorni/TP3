#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "materiales.h"
#include "procesamiento.h"
#include "edificios/edificio.h"
#include "edificios/tipos_edificios.h"
#include "edificios/parser.h"
#include "edificios/edificio.h"
#include "casilleros/casillero.h"
#include "casilleros/casillero_construible.h"
#include "casilleros/casillero_inaccesible.h"
#include "casilleros/casillero_transitable.h"

using namespace std;

const int CANT_CARACTERISTICAS_EDIFICIOS = 5;

//

Proceso::Proceso (){
	cantidadEdificios = 0;
	cantidadMateriales = 0;
	cantidadUbicaciones = 0;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------

void Proceso::leerMateriales(){

	fstream archivoMateriales(PATH_MATERIALES, ios::in);
	
	this -> cantidadMateriales = 0;
	Material *material;
	string nombre, cantidadMaterial;
	
	while(archivoMateriales >> nombre){
		archivoMateriales >> cantidadMaterial;
		
		material = new Material;
		*material = Material(nombre, stoi(cantidadMaterial));

		agregarMaterial(material);

	}
	
	archivoMateriales.close();
}


void Proceso::agregarMaterial(Material *nuevoMaterial){

	Material **vectorMateriales = new Material*[this -> cantidadMateriales + 1];
	if(vectorMateriales == NULL)
		delete[] vectorMateriales;
	
	for(int i = 0; i < this -> cantidadMateriales; i++)
		vectorMateriales[i] = this -> material[i];
		
	vectorMateriales[this -> cantidadMateriales] = nuevoMaterial;
	
	if(this -> cantidadMateriales != 0){
		delete[] this -> material;
	}
	
	this -> material = vectorMateriales;
	this -> cantidadMateriales++;	

}




void Proceso::cerrarMateriales(){

	ofstream archivoMateriales(PATH_MATERIALES);
	
	for(int i = 0; i < this -> cantidadMateriales; i++){
		archivoMateriales << this -> material[i]->obtenerNombreMaterial() << ' '
						   << this -> material[i]->obtenerCantidadMaterial() << '\n';
		delete this -> material[i];
	}
	
	delete[] this -> material;
	this -> material = nullptr;
}

bool Proceso::verificarMateriales(string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario, int construidos, int cantidadMax){

	int errores = 0;
	for(int i = 0; i < cantidadMateriales; i++){
		if((material[i]->obtenerNombreMaterial() == "piedra") && (material[i]->obtenerCantidadMaterial() < piedraNecesaria)){				
			imprimirMensajeError(nombreIngresado, material[i]->obtenerNombreMaterial(), material[i]->obtenerCantidadMaterial(), piedraNecesaria);
			errores++;
		}
			
		if((material[i]->obtenerNombreMaterial() == "madera") && (material[i]->obtenerCantidadMaterial() < maderaNecesaria)){
			imprimirMensajeError(nombreIngresado, material[i]->obtenerNombreMaterial(), material[i]->obtenerCantidadMaterial(), maderaNecesaria);
			errores++;
		}
				
		if((material[i]->obtenerNombreMaterial() == "metal") && (material[i]->obtenerCantidadMaterial() < metalNecesario)){
			imprimirMensajeError(nombreIngresado, material[i]->obtenerNombreMaterial(), material[i]->obtenerCantidadMaterial(), metalNecesario);
			errores++;
		}
			
	}
	if(errores > 0)
		return false;
	
	//Verifica la cantidad de edificios construidos
	if(construidos == cantidadMax){
		std::cout << "Se ha llegado a la cantidad máxima permitida de: "<< nombreIngresado << ". (Cantidad máxima = " << cantidadMax << "). No se pueden construir más" << endl;
		return false;
	}
	
	return true;
}


void Proceso::mostrarInventario(){

	long nombre_mas_largo = 0;
	long nombre = 0;

	std::cout << endl << endl;
	std::cout << "Lista de materiales propios:" << endl << endl;
	
	std::cout << "            ═══════════════════════════════" << endl;
	std::cout << "             Materiales        Cantidades"<< endl;
	std::cout << "            ═══════════════════════════════" << endl;
	
	for(int i = 0; i < this->cantidadMateriales; i++){
		nombre = this->material[i]->obtenerNombreMaterial().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}
	
	for(int i = 0; i < this->cantidadMateriales; i++){
		long espacio = nombre_mas_largo - this->material[i]->obtenerNombreMaterial().length();
		std::cout << "              " << this->material[i]->obtenerNombreMaterial();
		std::cout << setw(17 + (int)espacio);
		std::cout << this->material[i]->obtenerCantidadMaterial() <<endl;
	}
	
	std::cout << endl << endl;
}






//----------------------------------------------------------------------------------------------------------------------------------------------------




void Proceso::leerOpcionesEdificios(){
	
	
	fstream archivoEdificios(PATH_EDIFICIOS, ios::in);


	TipoEdificio* tipoEdificio;
    std::string lecturaEdificios[CANT_CARACTERISTICAS_EDIFICIOS];


    while (archivoEdificios >> lecturaEdificios[0]){

        archivoEdificios >> lecturaEdificios[1];
        archivoEdificios >> lecturaEdificios[2];
        archivoEdificios >> lecturaEdificios[3];
        archivoEdificios >> lecturaEdificios[4];
		
		
		Parser parser = Parser(lecturaEdificios);
		tipoEdificio = parser.procesarEntrada();


		agregarTipoEdificio(tipoEdificio);

	}
	
	archivoEdificios.close();
}

bool Proceso::verificarEdificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidadMax){

	int existe = 0;
	
	for(int i = 0; i < cantidadEdificios; i++){
		//Verifica que exista el edificio ingresado
		if(listaEdificios[i]->obtenerTipo() == nombreIngresado){
			*piedraNecesaria = listaEdificios[i]->obtenerPiedra();
			*maderaNecesaria = listaEdificios[i]->obtenerMadera();
			*metalNecesario = listaEdificios[i]->obtenerMetal();
			*construidos = listaEdificios[i]->obtenerCantConstruidos();
			*cantidadMax = listaEdificios[i]->obtenerCantMaxConstruido();
			existe = 1;
		}
	}
	
	if(existe == 0){
		std::cout << "El edificio '" << nombreIngresado << "' no existe" << endl << endl;
		return false;
	}
	
	return true;
}




void Proceso::listarEdificiosConstruidos(){

	int construidosTotal = 0;
	long nombreMasLargo = 0;
	long nombre = 0;
	
	std::cout << endl << endl;
	std::cout << "Lista de edificios construidos:" << endl << endl;
	
	std::cout << "            ═════════════════════════════════════════════════════════" << endl;
	std::cout << "             Nombre\t\tCantidad\t\tCoordenadas"<< endl;
	std::cout << "            ═════════════════════════════════════════════════════════" << endl;
	
	for(int i = 0; i < this ->cantidadEdificios; i++){
		nombre = listaEdificios[i]->obtenerTipo().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}
	for(int i = 0; i < this ->cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> obtenerCantConstruidos() != 0){
		
			long espacio = nombreMasLargo - listaEdificios[i]->obtenerTipo().length();
			std::cout << "             " << listaEdificios[i]->obtenerTipo();
			std::cout << setw(8 + (int)espacio);
			std::cout << this -> listaEdificios[i] -> obtenerCantConstruidos() << setw(20);
			
			for(int j = 0; j < listaEdificios[i] -> obtenerCantConstruidos(); j++)
		 		std::cout << "(" << this -> listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerFila() << ", " << this -> listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerColumna() << ")";
			
			construidosTotal += listaEdificios[i]->obtenerCantConstruidos();
			std::cout << endl;
		}
	}
	std::cout << endl << endl;
	std::cout << "Cantidad total de edificios construidos: " << construidosTotal << endl << endl;

}



void Proceso::agregarTipoEdificio(TipoEdificio* tipoEdificio){

    TipoEdificio** nuevaListaEdificios = new TipoEdificio*[(this -> cantidadEdificios) + 1];
    
    
    for (int i = 0; i < (this -> cantidadEdificios); i++){
        nuevaListaEdificios[i] = this -> listaEdificios[i];
    }
    
 
    nuevaListaEdificios[this -> cantidadEdificios] = tipoEdificio;

    if (cantidadEdificios != 0){
        delete [] listaEdificios;
    } 
    
    this -> listaEdificios = nuevaListaEdificios;
    this -> cantidadEdificios++;
	
}





void Proceso::listarEdificios(){

	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos\tTodavía puede construir\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	
	long nombreMasLargo = 0;
	long nombre = 0;
	for(int i = 0; i < this -> cantidadEdificios; i++){
		nombre = this -> listaEdificios[i] -> obtenerTipo().length();
		if(nombre > nombreMasLargo)
			nombreMasLargo = nombre;
	}	
	for(int i = 0; i < this->cantidadEdificios; i++){
		long espacio = nombreMasLargo - this -> listaEdificios[i] -> obtenerTipo().length();
		cout << "             " << this -> listaEdificios[i] -> obtenerTipo();
		cout << setw(5 + (int)espacio);
		cout << this -> listaEdificios[i] -> obtenerPiedra() << setw(16);
		cout << this -> listaEdificios[i] -> obtenerMadera() << setw(16);
		cout << this -> listaEdificios[i] -> obtenerMetal() << setw(23);
		cout << this -> listaEdificios[i] -> obtenerCantMaxConstruido() - this -> listaEdificios[i] -> obtenerCantConstruidos() << endl;
	}
}



bool Proceso::construirEdificio(string nombreIngresado){
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

void Proceso::agregarRecursos(string nombreEdificio){
	if(nombreEdificio == "mina"){
		
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "piedra")
				material[i]->modificarCantidad(PIEDRA_AGREGADA);
		}
	}
		
	if(nombreEdificio == "aserradero"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "madera")
				material[i]->modificarCantidad(MADERA_AGREGADA);
		}		
	}
	
	if(nombreEdificio == "fabrica"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "metal")
				material[i]->modificarCantidad(METAL_AGREGADO);
		}		
	}

}

void Proceso::recolectarRecursos(){
	for(int i = 0; i < this -> cantidadEdificios; i++){
		if(this -> listaEdificios[i] -> brindaMaterial())
			agregarRecursos(this -> listaEdificios[i] -> obtenerTipo());		
	}
	
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}


void Proceso::cerrarEdificios(){
	
	for(int i = 0; i < this -> cantidadEdificios; i++){
		listaEdificios[i] -> liberarEdificosConstruidos();
		delete this -> listaEdificios[i];
	}
   
	delete[] this -> listaEdificios;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------


void Proceso::leerUbicaciones(){

	fstream archivoUbicaciones(PATH_UBICACIONES, ios::in);
	Edificio* edificio;
	
	int posicion_edificio;

	char caracter;
	int fila = '0';
	int columna = '0';
	string tipoEdificio;
	
	while(archivoUbicaciones >> tipoEdificio){
		archivoUbicaciones >> caracter;
		archivoUbicaciones >> fila;
		archivoUbicaciones >> caracter;
		archivoUbicaciones >> columna;
		archivoUbicaciones >> caracter;


		edificio  = new Edificio (fila , columna);
		posicion_edificio = identificarEdificio(tipoEdificio);

		listaEdificios[posicion_edificio] -> agregarEdificioConstruido(edificio);
		mapa -> obtenerCasillero(fila, columna) -> establecerTipo(tipoEdificio);


	}
	archivoUbicaciones.close();
}



int Proceso::identificarEdificio(string tipoEdficio){

	int posicionEdificio = 0;
	while (listaEdificios[posicionEdificio] -> obtenerTipo() != tipoEdficio){

		posicionEdificio++;
	}
	
	return posicionEdificio;
}



void Proceso::cerrarUbicaciones(){

	ofstream archivoUbicaciones(PATH_UBICACIONES);

	for(int i = 0; i < cantidadEdificios; i++){
		for(int j = 0; j < listaEdificios[i] -> obtenerCantConstruidos(); j++){
			
			cout << listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerFila() << " - " << listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerColumna() << endl;
			archivoUbicaciones << this -> listaEdificios[i] -> obtenerTipo() << " ("
								<< listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerFila() << ", "
								<< listaEdificios[i] -> obetenerEdificiosConstruidos(j) -> obtenerColumna() << ')' << '\n';
		}

	}
	cerrarEdificios();
	archivoUbicaciones.close();
}





//----------------------------------------------------------------------------------------------------------------------------------------------------

void Proceso::leerMapa(){
	
	fstream archivoMapa(PATH_MAPA, ios::in);
	Casillero* casillero;
	Mapa *mapa = new Mapa();

	int filas = '0';
	int columnas = '0';
	char caracter;
	archivoMapa >> filas;
	archivoMapa >> columnas;
	
	mapa -> inicializarMapa(filas , columnas);

	
	for(int i = 0; i < mapa -> obtenerCantidadFilas(); i++){
		for(int j = 0; j < mapa -> obtenerCantidadColumnas(); j++){

			archivoMapa >> caracter;
			casillero = mapa -> identificarCasillero (i, j, caracter);
			mapa -> agregarCasillero(casillero);
		}
	}
	
	this->mapa = mapa;
	archivoMapa.close();
}




bool Proceso::verificarCoordenadas(int fila, int columna){
	
	if(fila < 0 || fila > mapa->obtenerCantidadFilas()){
		cout << "La fila ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}
	
	if(columna < 0 || columna > mapa->obtenerCantidadColumnas()){
		cout << "La columna ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}


	return true;
}







//----------------------------------------------------------------------------------------------------------------------------------------------------



void Proceso::leerArchivos(){
	leerMateriales();
	leerOpcionesEdificios();
	leerMapa();
	leerUbicaciones();
}

void Proceso::mostrarMenu(){
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



int Proceso::pedirOpcion(){
	
	int opcionElegida = 0;
	cout << "Ingrese el número de la opción elegida: ";
	cin >> opcionElegida;
	
	while(opcionElegida < 1 || opcionElegida > 10){
		cout << "La opción elegida no es válida" << endl << "Ingrese una opción válida: ";
		cin >> opcionElegida;
	}
	
	return opcionElegida;
}



void Proceso::procesarOpciones(int opcion){
	
	string nombreIngresado;
	
	switch(opcion){
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
	}
}



void Proceso::guardarYSalir(){
	cerrarMateriales();
	cerrarUbicaciones();
	cerrarMapa();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------





void Proceso::imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidadNecesaria){
	cout << "No hay suficiente " << material << "." << endl;
	cout << "Hay " << cantidad << " " << material << " disponibles. Se necesitan "<< cantidadNecesaria << " para construir " << nombre_edificio << endl << endl;
}




void Proceso::mostrarMapa(){
	mapa -> mostrarMapa();
}

void Proceso::cerrarMapa(){
	mapa -> liberarCasilleros();
	delete mapa;
}





//----------------------------------------------------------------------------------------------------------------------------------------------------

int Proceso::identificarMaterial(string nombreMaterial){
	int posicion_material = 0;
	while (material[posicion_material] -> obtenerNombreMaterial() != nombreMaterial){
		posicion_material ++;
	}
	return posicion_material;
}

void Proceso::aumentarMaterialesDerrumbe(TipoEdificio* tipoEdificio){
	for (int i = 0; i < cantidadMateriales; i++){
		if (material[i] -> obtenerNombreMaterial() == "piedra"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerPiedra());
		}
		else if (material[i] -> obtenerNombreMaterial() == "madera"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerMadera());
		}
		else if (material[i] -> obtenerNombreMaterial() == "metal"){
			material[i] -> establecerCantidad(material[i] -> obtenerCantidadMaterial() + tipoEdificio -> obtenerMetal());
		}
	}
}


void Proceso::demolerEdificioCoordenada(){
	int fila, columna;
	mapa -> pedirCoordenada(fila, columna);
	int posicion;
	if (mapa -> sePuedeDemoler(fila, columna)){

		posicion = identificarEdificio(mapa -> obtenerCasillero(fila, columna) -> obtenerTipo());

		mapa -> obtenerCasillero(fila, columna) -> liberar ();
		aumentarMaterialesDerrumbe(listaEdificios[posicion]);

	}
}	


void Proceso::consultarCoordenada(){
	int fila,columna;
	mapa -> pedirCoordenada(fila,columna);
	mapa -> obtenerCasillero(fila, columna) -> responder();
}



void Proceso::lluviaElementos(){
	bool generoPiedra = false;
	bool generoMadera = false;
	bool generoMetal = false;
	int cantidadPiedra = 1 + rand() % 2;
	int cantidadMadera =  rand() % 2;
	int cantidadMetal = 2 + rand() % 5;
	int contadorPiedra = 0;
	int contadorMadera = 0;
	int contadorMetal = 0;

	while (!generoMadera || !generoMetal || !generoPiedra){
		int fil_random = rand()% (mapa -> obtenerCantidadFilas());
		int col_random = rand()% (mapa -> obtenerCantidadColumnas());
		if (mapa -> obtenerCasillero(fil_random,col_random) -> esTransitable()){
			if (!generoPiedra){
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("piedra");
				contadorPiedra ++;
				if (cantidadPiedra == contadorPiedra){
					generoPiedra = true;
				}
			}
			else if (!generoMadera){
				if (cantidadMadera == 0){
					generoMadera = true;
				}
				else {
					mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
					mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("madera");
					contadorMadera ++;
				}
			}
			else if (!generoMetal){

				mapa -> obtenerCasillero(fil_random,col_random) -> establecerCantidadMaterial(1);
				mapa -> obtenerCasillero(fil_random,col_random) -> establecerTipo("metal");
				contadorMetal ++;
				if (cantidadMetal == contadorMetal){
					generoMetal = true;
				}
			}
		}			
	}
}