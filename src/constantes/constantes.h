#ifndef CONSTANTES_H
#define CONSTANTES_H

// juego.cpp
const int CANT_CARACTERISTICAS_EDIFICIOS = 5;
const int LLUVIA_PIEDRA = 100;
const int LLUVIA_MADERA = 50;
const int LLUVIA_METAL = 50;
const int LLUVIA_ANDYCOINS = 250;

// juego.h
#define PATH_MATERIALES "src/data/materiales.txt"
#define PATH_EDIFICIOS "src/data/edificios.txt"
#define PATH_UBICACIONES "src/data/ubicaciones.txt"
#define PATH_MAPA "src/data/mapa.txt"

#define TXT_LIGHT_AQUA_123 "\033[38;5;123m"
#define TXT_ITALIC "\033[3m"
#define TXT_UNDERLINE "\033[4m"
#define BGND_LIGHT_BLUE_32 "\033[48;5;32m"
#define BGND_GREEN_34 "\033[48;5;34m"
#define BGND_GRAY_240 "\033[48;5;240m"

const std::string COLOR_CAMINO = "\033[48;5;240m";
const std::string COLOR_BETUN = "\033[48;5;234m";
const std::string COLOR_LAGO = "\033[48;5;27m";
const std::string COLOR_MUELLE = "\033[48;5;94m";
const std::string COLOR_TERRENO = "\033[48;5;40m";
const std::string END_COLOR = "\033[0m";

const std::string MADERA = "madera";
const std::string METAL = "metal";
const std::string PIEDRA = "piedra";
const std::string ENERGIA = "energia";
const std::string BOMBAS = "bombas";
const std::string ANDYCOINS = "andycoins";
const std::string MAXIMO_CONSTRUIBLES = "max";
const std::string PRODUCCION = "prod";
const std::string MATERIAL_NULO = "matnul";
const std::string MATERIALES_CONSTRUCCION[3] = {PIEDRA, MADERA, METAL}; 
const std::string MATERIALES_RECETA[5] = {PIEDRA, MADERA, METAL, MAXIMO_CONSTRUIBLES, PRODUCCION};


// mapa.cpp
const char CAMINO = 'C';
const char BETUN = 'B';
const char LAGO = 'L';
const char MUELLE = 'M';
const char TERRENO = 'T';

const char CARACTER_VACIO = ' ';

const char CARACTER_METAL = 'I';
const char CARACTER_PIEDRA = 'S';
const char CARACTER_MADERA = 'W';
const char CARACTER_ANDYCOINS = 'C';

// utilesMenu.h
const int ENERGIA_POR_FINALIZAR_TURNO = 20;
const int ENERGIA_POR_CONSTRUIR_EDIFICIO_POR_NOMBRE = -15;
const int ENERGIA_POR_DEMOLER_EDIFICIO_POR_COORDENADA = -15;
const int ENERGIA_POR_ATACAR_EDIFICIO_POR_COORDENADA = -30;
const int ENERGIA_POR_REPARAR_EDIFICIO_POR_COORDENADA = -25;
const int ENERGIA_POR_COMPRAR_BOMBA = -5;
const int ENERGIA_POR_RECOLECTAR_RECURSOS_PRODUCIDOS = -20;

const int COSTO_BOMBA = 100;

const int CANTIDAD_ANDYCOINS_COMPRAR_ANDYPOLIS = 100000;
const int CANTIDAD_BOMBARDERO = 5;
const int CANTIDAD_EDAD_DE_PIEDRA = 50000;
const int CANTIDAD_ARMADO = 10;
const int CANTIDAD_EXTREMISTA = 500;


#endif
