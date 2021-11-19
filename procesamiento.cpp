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



#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>

const int CANT_CARACTERISTICAS_EDIFICIOS = 5;

using namespace std;

Proceso::Proceso (){
	cantidad_edificios = 0;
	cantidad_materiales = 0;
	cantidad_ubicaciones = 0;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------

void Proceso::leer_materiales(){

	fstream archivo_materiales(PATH_MATERIALES, ios::in);
	
	this->cantidad_materiales = 0;
	Material *material;
	string nombre, cantidad_material;
	
	while(archivo_materiales >> nombre){
		archivo_materiales >> cantidad_material;
		
		material = new Material;
		*material = Material(nombre, stoi(cantidad_material));

		agregar_material(material);

	}
	
	archivo_materiales.close();
}


void Proceso::agregar_material(Material *nuevo_material){

	Material **vector_materiales = new Material*[this->cantidad_materiales + 1];
	if(vector_materiales == NULL)
		delete[] vector_materiales;
	
	for(int i = 0; i < this->cantidad_materiales; i++)
		vector_materiales[i] = this->material[i];
		
	vector_materiales[this->cantidad_materiales] = nuevo_material;
	
	if(this->cantidad_materiales != 0){
		delete[] this->material;
	}
	
	this->material = vector_materiales;
	this->cantidad_materiales++;	

}




void Proceso::cerrar_materiales(){

	ofstream archivo_materiales(PATH_MATERIALES);
	
	for(int i = 0; i < this->cantidad_materiales; i++){
		archivo_materiales << this -> material[i]->obtener_nombre_material() << ' '
						   << this -> material[i]->obtener_cantidad_material() << '\n';
		delete this->material[i];
	}
	
	delete[] this->material;
	this->material = nullptr;
}

bool Proceso::verificar_materiales(string nombre_ingresado, int piedra_necesaria, int madera_necesaria, int metal_necesario, int construidos, int cantidad_max){

	int errores = 0;
	for(int i = 0; i < cantidad_materiales; i++){
		if((material[i]->obtener_nombre_material() == "piedra") && (material[i]->obtener_cantidad_material() < piedra_necesaria)){				
			imprimir_mensaje_error(nombre_ingresado, material[i]->obtener_nombre_material(), material[i]->obtener_cantidad_material(), piedra_necesaria);
			errores++;
		}
			
		if((material[i]->obtener_nombre_material() == "madera") && (material[i]->obtener_cantidad_material() < madera_necesaria)){
			imprimir_mensaje_error(nombre_ingresado, material[i]->obtener_nombre_material(), material[i]->obtener_cantidad_material(), madera_necesaria);
			errores++;
		}
				
		if((material[i]->obtener_nombre_material() == "metal") && (material[i]->obtener_cantidad_material() < metal_necesario)){
			imprimir_mensaje_error(nombre_ingresado, material[i]->obtener_nombre_material(), material[i]->obtener_cantidad_material(), metal_necesario);
			errores++;
		}
			
	}
	if(errores > 0)
		return false;
	
	//Verifica la cantidad de edificios construidos
	if(construidos == cantidad_max){
		cout << "Se ha llegado a la cantidad máxima permitida de: "<< nombre_ingresado << ". (Cantidad máxima = " << cantidad_max << "). No se pueden construir más" << endl;
		return false;
	}
	
	return true;
}


void Proceso::mostrar_inventario(){

	long nombre_mas_largo = 0;
	long nombre = 0;

	cout << endl << endl;
	cout << "Lista de materiales propios:" << endl << endl;
	
	cout << "            ═══════════════════════════════" << endl;
	cout << "             Materiales        Cantidades"<< endl;
	cout << "            ═══════════════════════════════" << endl;
	
	for(int i = 0; i < this->cantidad_materiales; i++){
		nombre = this->material[i]->obtener_nombre_material().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}
	
	for(int i = 0; i < this->cantidad_materiales; i++){
		long espacio = nombre_mas_largo - this->material[i]->obtener_nombre_material().length();
		cout << "              " << this->material[i]->obtener_nombre_material();
		cout << setw(17 + (int)espacio);
		cout << this->material[i]->obtener_cantidad_material() <<endl;
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

bool Proceso::verificar_edificio(string nombre_ingresado, int *piedra_necesaria, int *madera_necesaria, int *metal_necesario, int *construidos, int *cantidad_max){

	int existe = 0;
	
	for(int i = 0; i < cantidad_edificios; i++){
		//Verifica que exista el edificio ingresado
		if(lista_edificios[i]->obtener_tipo() == nombre_ingresado){
			*piedra_necesaria = lista_edificios[i]->obtener_piedra();
			*madera_necesaria = lista_edificios[i]->obtener_madera();
			*metal_necesario = lista_edificios[i]->obtener_metal();
			*construidos = lista_edificios[i]->obtener_cant_construidos();
			*cantidad_max = lista_edificios[i]->obtener_cant_max_construido();
			existe = 1;
		}
	}
	
	if(existe == 0){
		cout << "El edificio '" << nombre_ingresado << "' no existe" << endl << endl;
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
	
	for(int i = 0; i < this ->cantidad_edificios; i++){
		nombre = lista_edificios[i]->obtener_tipo().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}
	for(int i = 0; i < this ->cantidad_edificios; i++){
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

    Tipo_edificio** nueva_lista_edificios = new Tipo_edificio*[(this -> cantidad_edificios) + 1];
    
    
    for (int i = 0; i < (this -> cantidad_edificios); i++){
        nueva_lista_edificios[i] = this->lista_edificios[i];
    }
    
 
    nueva_lista_edificios[this -> cantidad_edificios] = tipo_edificio;

    if (cantidad_edificios != 0){
        delete [] lista_edificios;
    } 
    
    this -> lista_edificios = nueva_lista_edificios;
    this -> cantidad_edificios++;
	
}





void Proceso::listar_edificios(){

	cout << endl << endl;
	cout << "Lista de edificios:" << endl << endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	cout << "             Nombre\t\tPiedra\t\tMadera\t\tMetal\t\tConstruidos\tTodavía puede construir\t\t¿Brinda material?"<< endl;
	cout << "            ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
	
	long nombre_mas_largo = 0;
	long nombre = 0;
	for(int i = 0; i < this -> cantidad_edificios; i++){
		nombre = this -> lista_edificios[i] -> obtener_tipo().length();
		if(nombre > nombre_mas_largo)
			nombre_mas_largo = nombre;
	}	
	for(int i = 0; i < this->cantidad_edificios; i++){
		long espacio = nombre_mas_largo - this -> lista_edificios[i] -> obtener_tipo().length();
		cout << "             " << this -> lista_edificios[i] -> obtener_tipo();
		cout << setw(5 + (int)espacio);
		cout << this -> lista_edificios[i] -> obtener_piedra() << setw(16);
		cout << this -> lista_edificios[i] -> obtener_madera() << setw(16);
		cout << this -> lista_edificios[i] -> obtener_metal() << setw(23);
		cout << this -> lista_edificios[i] -> obtener_cant_max_construido() - this -> lista_edificios[i] -> obtener_cant_construidos() << endl;
	}
}



bool Proceso::construir_edificio(string nombre_ingresado){
	int piedra_necesaria = 0, madera_necesaria = 0, metal_necesario = 0, construidos = 0, cantidad_max = 0;
	
	//Verifica que el edificio ingresado exista
	if(!verificar_edificio(nombre_ingresado, &piedra_necesaria, &madera_necesaria, &metal_necesario, &construidos, &cantidad_max)){
		return false;
	}
	
	//Verifica que se tengan todos los materiales
	if(!verificar_materiales(nombre_ingresado, piedra_necesaria, madera_necesaria, metal_necesario, construidos, cantidad_max))
		return false;
	
	int fila, columna;
	cout << "¿Donde desea construir su " << nombre_ingresado << "? Ingrese la primer coordenada: " << endl;
	cin >> fila;
	cout << "Ingrese la segunda coordenada: " << endl;
	cin >> columna;
	
	if(!verificar_coordenadas(fila, columna))
		return false;
	
	char respuesta;
	bool done = false;
	
	cout << "Todo listo para construir " << nombre_ingresado << ", ¿Está seguro que quiere seguir? [y/n]: ";
	do{
		cin >> respuesta;
		Edificio* edificio;
		int posicion_edificio;
		switch(respuesta){
			case 'y':
				cout << "El edificio ha sido construido correctamente" << endl << endl;
				edificio  = new Edificio (fila , columna);
				posicion_edificio = identificar_edificio(nombre_ingresado);
				lista_edificios[posicion_edificio] -> agregar_edificio_construido(edificio);

				mapa -> obtener_casillero(fila, columna) -> establecer_tipo(nombre_ingresado);
				for(int i = 0; i < cantidad_materiales; i++){
					if(material[i]->obtener_nombre_material() == "piedra")
						material[i]->modificar_cantidad(piedra_necesaria);
					if(material[i]->obtener_nombre_material() == "madera")
						material[i]->modificar_cantidad(madera_necesaria);
					if(material[i]->obtener_nombre_material() == "metal")
						material[i]->modificar_cantidad(metal_necesario);
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
		
		for(int i = 0; i < cantidad_materiales; i++){
			if(material[i]->obtener_nombre_material() == "piedra")
				material[i]->modificar_cantidad(PIEDRA_AGREGADA);
		}
	}
		
	if(nombre_edificio == "aserradero"){
		for(int i = 0; i < cantidad_materiales; i++){
			if(material[i]->obtener_nombre_material() == "madera")
				material[i]->modificar_cantidad(MADERA_AGREGADA);
		}		
	}
	
	if(nombre_edificio == "fabrica"){
		for(int i = 0; i < cantidad_materiales; i++){
			if(material[i]->obtener_nombre_material() == "metal")
				material[i]->modificar_cantidad(METAL_AGREGADO);
		}		
	}

}

void Proceso::recolectar_recursos(){
	for(int i = 0; i < this->cantidad_edificios; i++){
		if(this -> lista_edificios[i] -> brinda_material())
			agregar_recursos(this -> lista_edificios[i] -> obtener_tipo());		
	}
	
	cout << "Se recolectaron todos los recursos disponibles" << endl;
}


void Proceso::cerrar_edificios(){
	
	for(int i = 0; i < this->cantidad_edificios; i++){
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

	for(int i = 0; i < cantidad_edificios; i++){
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
	leer_materiales();
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
	
	string nombre_ingresado;
	
	switch(opcion){
		case 1:
			cout << "Ingrese el nombre del edificio que desea construir: ";
			cin >> nombre_ingresado;
			construir_edificio(nombre_ingresado);
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
			mostrar_inventario();
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





void Proceso::imprimir_mensaje_error(string nombre_edificio, string material, int cantidad, int cantidad_necesaria){
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
	while (material[posicion_material] -> obtener_nombre_material() != nombre_material){
		posicion_material ++;
	}
	return posicion_material;
}

void Proceso::aumentar_materiales_derrumbe(Tipo_edificio* tipo_edificio){
	for (int i = 0; i < cantidad_materiales; i++){
		if (material[i] -> obtener_nombre_material() == "piedra"){
			material[i] -> establecer_cantidad(material[i] -> obtener_cantidad_material() + tipo_edificio -> obtener_piedra());
		}
		else if (material[i] -> obtener_nombre_material() == "madera"){
			material[i] -> establecer_cantidad(material[i] -> obtener_cantidad_material() + tipo_edificio -> obtener_madera());
		}
		else if (material[i] -> obtener_nombre_material() == "metal"){
			material[i] -> establecer_cantidad(material[i] -> obtener_cantidad_material() + tipo_edificio -> obtener_metal());
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
