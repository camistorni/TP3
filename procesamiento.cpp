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

const int CANT_CARACTERISTICAS_EDIFICIOS = 5;

using namespace std;

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
	string nombre, cantidad_material;
	
	while(archivoMateriales >> nombre){
		archivoMateriales >> cantidad_material;
		
		material = new Material;
		*material = Material(nombre, stoi(cantidad_material));

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

bool Proceso::verificarMateriales(string nombreIngresado, int piedraNecesaria, int maderaNecesaria, int metalNecesario, int construidos, int cantidad_max){

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
	if(construidos == cantidad_max){
		cout << "Se ha llegado a la cantidad máxima permitida de: "<< nombreIngresado << ". (Cantidad máxima = " << cantidad_max << "). No se pueden construir más" << endl;
		return false;
	}
	
	return true;
}


void Proceso::mostrarInventario(){

	long nombre_mas_largo = 0;
	long nombre = 0;

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << "            ═══════════════════════════════" << endl;
	cout << "             Materiales        Cantidades"<< endl;
	cout << "            ═══════════════════════════════" << endl;
	
	for(int i = 0; i < this->cantidadMateriales; i++){
		nombre = this->material[i]->obtenerNombreMaterial().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}
	
	for(int i = 0; i < this->cantidadMateriales; i++){
		long espacio = nombre_mas_largo - this->material[i]->obtenerNombreMaterial().length();
		cout << "              " << this->material[i]->obtenerNombreMaterial();
		cout << setw(17 + (int)espacio);
		cout << this->material[i]->obtenerCantidadMaterial() <<endl;
	}
	
	cout << endl << endl;
}






//----------------------------------------------------------------------------------------------------------------------------------------------------




void Proceso::leer_opciones_edificios(){
	
	
	fstream archivo_edificios(PATH_EDIFICIOS, ios::in);


	Tipo_edificio* tipo_edificio;
    std::string lectura_edificios[CANT_CARACTERISTICAS_EDIFICIOS];


    while (archivo_edificios >> lectura_edificios[0]){

        archivo_edificios >> lectura_edificios[1];
        archivo_edificios >> lectura_edificios[2];
        archivo_edificios >> lectura_edificios[3];
        archivo_edificios >> lectura_edificios[4];
		
		
		Parser parser = Parser(lectura_edificios);
		tipo_edificio = parser.procesar_entrada();


		agregar_tipo_edificio(tipo_edificio);

	}
	
	archivo_edificios.close();
}

bool Proceso::verificar_edificio(string nombreIngresado, int *piedraNecesaria, int *maderaNecesaria, int *metalNecesario, int *construidos, int *cantidad_max){

	int existe = 0;
	
	for(int i = 0; i < cantidadEdificios; i++){
		//Verifica que exista el edificio ingresado
		if(lista_edificios[i]->obtener_tipo() == nombreIngresado){
			*piedraNecesaria = lista_edificios[i]->obtener_piedra();
			*maderaNecesaria = lista_edificios[i]->obtener_madera();
			*metalNecesario = lista_edificios[i]->obtener_metal();
			*construidos = lista_edificios[i]->obtener_cant_construidos();
			*cantidad_max = lista_edificios[i]->obtener_cant_max_construido();
			existe = 1;
		}
	}
	
	if(existe == 0){
		cout << "El edificio '" << nombreIngresado << "' no existe" << endl << endl;
		return false;
	}
	
	return true;
}




void Proceso::listar_edificios_construidos(){

	int construidos_total = 0;
	long nombre_mas_largo = 0;
	long nombre = 0;
	
	cout << endl << endl;
	cout << "Lista de edificios construidos:" << endl << endl;
	
	cout << "            ═════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tCantidad\t\tCoordenadas"<< endl;
	cout << "            ═════════════════════════════════════════════════════════" << endl;
	
	for(int i = 0; i < this ->cantidadEdificios; i++){
		nombre = lista_edificios[i]->obtener_tipo().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}
	for(int i = 0; i < this ->cantidadEdificios; i++){
		if(this -> lista_edificios[i] -> obtener_cant_construidos() != 0){
		
			long espacio = nombre_mas_largo - lista_edificios[i]->obtener_tipo().length();
			cout << "             " << lista_edificios[i]->obtener_tipo();
			cout << setw(8 + (int)espacio);
			cout << this -> lista_edificios[i] -> obtener_cant_construidos() << setw(20);
			
			for(int j = 0; j < lista_edificios[i] -> obtener_cant_construidos(); j++)
		 		cout << "(" << this -> lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_fila() << ", " << this -> lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_columna() << ")";
			
			construidos_total += lista_edificios[i]->obtener_cant_construidos();
			cout << endl;
		}
	}
	cout << endl << endl;
	cout << "Cantidad total de edificios construidos: " << construidos_total << endl << endl;

}



void Proceso::agregar_tipo_edificio(Tipo_edificio* tipo_edificio){

    Tipo_edificio** nueva_lista_edificios = new Tipo_edificio*[(this -> cantidadEdificios) + 1];
    
    
    for (int i = 0; i < (this -> cantidadEdificios); i++){
        nueva_lista_edificios[i] = this->lista_edificios[i];
    }
    
 
    nueva_lista_edificios[this -> cantidadEdificios] = tipo_edificio;

    if (cantidadEdificios != 0){
        delete [] lista_edificios;
    } 
    
    this -> lista_edificios = nueva_lista_edificios;
    this -> cantidadEdificios++;
	
}





void Proceso::listar_edificios(){

	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos\tTodavía puede construir\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	
	long nombre_mas_largo = 0;
	long nombre = 0;
	for(int i = 0; i < this -> cantidadEdificios; i++){
		nombre = this -> lista_edificios[i] -> obtener_tipo().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}	
	for(int i = 0; i < this->cantidadEdificios; i++){
		long espacio = nombre_mas_largo - this -> lista_edificios[i] -> obtener_tipo().length();
		cout << "             " << this -> lista_edificios[i] -> obtener_tipo();
		cout << setw(5 + (int)espacio);
		cout << this -> lista_edificios[i] -> obtener_piedra() << setw(16);
		cout << this -> lista_edificios[i] -> obtener_madera() << setw(16);
		cout << this -> lista_edificios[i] -> obtener_metal() << setw(23);
		cout << this -> lista_edificios[i] -> obtener_cant_max_construido() - this -> lista_edificios[i] -> obtener_cant_construidos() << endl;
	}
}



bool Proceso::construir_edificio(string nombreIngresado){
	int piedraNecesaria = 0, maderaNecesaria = 0, metalNecesario = 0, construidos = 0, cantidad_max = 0;
	
	//Verifica que el edificio ingresado exista
	if(!verificar_edificio(nombreIngresado, &piedraNecesaria, &maderaNecesaria, &metalNecesario, &construidos, &cantidad_max)){
		return false;
	}
	
	//Verifica que se tengan todos los materiales
	if(!verificar_materiales(nombreIngresado, piedraNecesaria, maderaNecesaria, metalNecesario, construidos, cantidad_max))
		return false;
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombreIngresado << "? Ingrese la primer coordenada: " << endl;
	cin >> fila;
	cout << "Ingrese la segunda coordenada: " << endl;
	cin >> columna;
	
	if(!verificar_coordenadas(fila, columna))
		return false;
	
	char respuesta;
	bool done = false;
	
	cout << "Todo listo para construir " << nombreIngresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	do{
		cin >> respuesta;
		Edificio* edificio;
		int posicion_edificio;
		switch(respuesta){
			case 'y':
				cout << "El edificio ha sido construido correctamente" << endl << endl;
				edificio  = new Edificio (fila , columna);
				posicion_edificio = identificar_edificio(nombreIngresado);
				lista_edificios[posicion_edificio] -> agregar_edificio_construido(edificio);

				mapa -> obtener_casillero(fila, columna) -> establecer_tipo(nombreIngresado);
				for(int i = 0; i < cantidadMateriales; i++){
					if(material[i]->obtenerNombreMaterial() == "piedra")
						material[i]->modificar_cantidad(piedraNecesaria);
					if(material[i]->obtenerNombreMaterial() == "madera")
						material[i]->modificar_cantidad(maderaNecesaria);
					if(material[i]->obtenerNombreMaterial() == "metal")
						material[i]->modificar_cantidad(metalNecesario);
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

void Proceso::agregar_recursos(string nombre_edificio){
	if(nombre_edificio == "mina"){
		
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "piedra")
				material[i]->modificar_cantidad(PIEDRA_AGREGADA);
		}
	}
		
	if(nombre_edificio == "aserradero"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "madera")
				material[i]->modificar_cantidad(MADERA_AGREGADA);
		}		
	}
	
	if(nombre_edificio == "fabrica"){
		for(int i = 0; i < cantidadMateriales; i++){
			if(material[i]->obtenerNombreMaterial() == "metal")
				material[i]->modificar_cantidad(METAL_AGREGADO);
		}		
	}

}

void Proceso::recolectar_recursos(){
	for(int i = 0; i < this->cantidadEdificios; i++){
		if(this -> lista_edificios[i] -> brinda_material())
			agregar_recursos(this -> lista_edificios[i] -> obtener_tipo());		
	}
	
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}


void Proceso::cerrar_edificios(){
	
	for(int i = 0; i < this->cantidadEdificios; i++){
		lista_edificios[i] -> liberar_edificos_construidos();
		delete this->lista_edificios[i];
	}
   
	delete[] this->lista_edificios;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------


void Proceso::leer_ubicaciones(){

	fstream archivo_ubicaciones(PATH_UBICACIONES, ios::in);
	Edificio* edificio;
	
	int posicion_edificio;

	char caracter;
	int fila = '0';
	int columna = '0';
	string tipo_edificio;
	
	while(archivo_ubicaciones >> tipo_edificio){
		archivo_ubicaciones >> caracter;
		archivo_ubicaciones >> fila;
		archivo_ubicaciones >> caracter;
		archivo_ubicaciones >> columna;
		archivo_ubicaciones >> caracter;


		edificio  = new Edificio (fila , columna);
		posicion_edificio = identificar_edificio(tipo_edificio);

		lista_edificios[posicion_edificio] -> agregar_edificio_construido(edificio);
		mapa -> obtener_casillero(fila, columna) -> establecer_tipo(tipo_edificio);


	}
	archivo_ubicaciones.close();
}



int Proceso::identificar_edificio(string tipo_edficio){

	int posicion_edificio = 0;
	while (lista_edificios[posicion_edificio] -> obtener_tipo() != tipo_edficio){

		posicion_edificio++;
	}
	
	return posicion_edificio;
}



void Proceso::cerrar_ubicaciones(){

	ofstream archivo_ubicaciones(PATH_UBICACIONES);

	for(int i = 0; i < cantidadEdificios; i++){
		for(int j = 0; j < lista_edificios[i] -> obtener_cant_construidos(); j++){
			
			cout << lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_fila() << " - " << lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_columna() << endl;
			archivo_ubicaciones << this -> lista_edificios[i] -> obtener_tipo() << " ("
								<< lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_fila() << ", "
								<< lista_edificios[i] -> obetener_edificios_construidos(j) -> obtener_columna() << ')' << '\n';
		}

	}
	cerrar_edificios();
	archivo_ubicaciones.close();
}





//----------------------------------------------------------------------------------------------------------------------------------------------------

void Proceso::leer_mapa(){
	
	fstream archivo_mapa(PATH_MAPA, ios::in);
	Casillero* casillero;
	Mapa *mapa = new Mapa();

	int filas = '0';
	int columnas = '0';
	char caracter;
	archivo_mapa >> filas;
	archivo_mapa >> columnas;
	
	mapa -> inicializar_mapa(filas , columnas);

	
	for(int i = 0; i < mapa -> obtener_cantidad_filas(); i++){
		for(int j = 0; j < mapa -> obtener_cantidad_columnas(); j++){

			archivo_mapa >> caracter;
			casillero = mapa -> identificar_casillero (i, j, caracter);
			mapa -> agregar_casillero(casillero);
		}
	}
	
	this->mapa = mapa;
	archivo_mapa.close();
}




bool Proceso::verificar_coordenadas(int fila, int columna){
	
	if(fila < 0 || fila > mapa->obtener_cantidad_filas()){
		cout << "La fila ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}
	
	if(columna < 0 || columna > mapa->obtener_cantidad_columnas()){
		cout << "La columna ingresada está fuera de rango. No se puede construir el edificio" << endl;
		return false;
	}


	return true;
}







//----------------------------------------------------------------------------------------------------------------------------------------------------



void Proceso::leer_archivos(){
	leerMateriales();
	leer_opciones_edificios();
	leer_mapa();
	leer_ubicaciones();
}

void Proceso::mostrar_menu(){
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



int Proceso::pedir_opcion(){
	
	int opcion_elegida = 0;
	cout << "Ingrese el número de la opción elegida: ";
	cin >> opcion_elegida;
	
	while(opcion_elegida < 1 || opcion_elegida > 10){
		cout << "La opción elegida no es válida" << endl << "Ingrese una opción válida: ";
		cin >> opcion_elegida;
	}
	
	return opcion_elegida;
}



void Proceso::procesar_opciones(int opcion){
	
	string nombreIngresado;
	
	switch(opcion){
		case 1:
			cout << "Ingrese el nombre del edificio que desea construir: ";
			cin >> nombreIngresado;
			construir_edificio(nombreIngresado);
			break;
			
		case 2:
			listar_edificios_construidos();
			break;
		
		case 3:
			listar_edificios();
			break;
		
		case 4:
			demoler_edificio_coordenada();
			break;
		
		case 5:
			mostrar_mapa();
			break;
		
		case 6:
			consultar_coordenada();
			break;
			
		case 7:
			mostrarInventario();
			break;
		
		case 8:
			recolectar_recursos();
			break;
		
		case 9:
			lluvia_elementos();
			break;
		
		case 10:
			guardar_y_salir();
			break;
	}
}



void Proceso::guardar_y_salir(){
	cerrar_materiales();
	cerrar_ubicaciones();
	cerrar_mapa();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------





void Proceso::imprimirMensajeError(string nombre_edificio, string material, int cantidad, int cantidad_necesaria){
	cout << "No hay suficiente " << material << "." << endl;
	cout << "Hay " << cantidad << " " << material << " disponibles. Se necesitan "<< cantidad_necesaria << " para construir " << nombre_edificio << endl << endl;
}




void Proceso::mostrar_mapa(){
	mapa->mostrar_mapa();
}

void Proceso::cerrar_mapa(){
	mapa -> liberar_casilleros();
	delete mapa;
}





//----------------------------------------------------------------------------------------------------------------------------------------------------

int Proceso::identificar_material(string nombre_material){
	int posicion_material = 0;
	while (material[posicion_material] -> obtenerNombreMaterial() != nombre_material){
		posicion_material ++;
	}
	return posicion_material;
}

void Proceso::aumentar_materiales_derrumbe(Tipo_edificio* tipo_edificio){
	for (int i = 0; i < cantidadMateriales; i++){
		if (material[i] -> obtenerNombreMaterial() == "piedra"){
			material[i] -> establecer_cantidad(material[i] -> obtenerCantidadMaterial() + tipo_edificio -> obtener_piedra());
		}
		else if (material[i] -> obtenerNombreMaterial() == "madera"){
			material[i] -> establecer_cantidad(material[i] -> obtenerCantidadMaterial() + tipo_edificio -> obtener_madera());
		}
		else if (material[i] -> obtenerNombreMaterial() == "metal"){
			material[i] -> establecer_cantidad(material[i] -> obtenerCantidadMaterial() + tipo_edificio -> obtener_metal());
		}
	}
}


void Proceso::demoler_edificio_coordenada(){
	int fila, columna;
	mapa -> pedir_coordenada(fila, columna);
	int posicion;
	if (mapa -> se_puede_demoler(fila, columna)){

		posicion = identificar_edificio(mapa -> obtener_casillero(fila, columna) -> obtener_tipo());

		mapa -> obtener_casillero(fila, columna) -> liberar ();
		aumentar_materiales_derrumbe(lista_edificios[posicion]);

	}
}	


void Proceso::consultar_coordenada(){
	int fila,columna;
	mapa -> pedir_coordenada(fila,columna);
	mapa -> obtener_casillero(fila, columna) -> responder();
}



void Proceso::lluvia_elementos(){
	bool genero_piedra = false;
	bool genero_madera = false;
	bool genero_metal = false;
	int cantidad_piedra = 1 + rand() % 2;
	int cantidad_madera =  rand() % 2;
	int cantidad_metal = 2 + rand() % 5;
	int contador_piedra = 0;
	int contador_madera = 0;
	int contador_metal = 0;

	while (!genero_madera || !genero_metal || !genero_piedra){
		int fil_random = rand()% (mapa -> obtener_cantidad_filas());
		int col_random = rand()% (mapa -> obtener_cantidad_columnas());
		if (mapa -> obtener_casillero(fil_random,col_random) -> es_transitable()){
			if (!genero_piedra){
				mapa -> obtener_casillero(fil_random,col_random) -> establecer_cantidad_material(1);
				mapa -> obtener_casillero(fil_random,col_random) -> establecer_tipo("piedra");
				contador_piedra ++;
				if (cantidad_piedra == contador_piedra){
					genero_piedra = true;
				}
			}
			else if (!genero_madera){
				if (cantidad_madera == 0){
					genero_madera = true;
				}
				else {
					mapa -> obtener_casillero(fil_random,col_random) -> establecer_cantidad_material(1);
					mapa -> obtener_casillero(fil_random,col_random) -> establecer_tipo("madera");
					contador_madera ++;
				}
			}
			else if (!genero_metal){

				mapa -> obtener_casillero(fil_random,col_random) -> establecer_cantidad_material(1);
				mapa -> obtener_casillero(fil_random,col_random) -> establecer_tipo("metal");
				contador_metal ++;
				if (cantidad_metal == contador_metal){
					genero_metal = true;
				}
			}
		}			
	}
}
