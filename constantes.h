#ifndef CONSTANTES_H
#define CONSTANTES_H

// juego.cpp
const int CANT_CARACTERISTICAS_EDIFICIOS = 5;

// juego.h
#define PATH_MATERIALES "materiales.txt"
#define PATH_EDIFICIOS "edificios.txt"
#define PATH_UBICACIONES "ubicaciones.txt"
#define PATH_MAPA "mapa.txt"
#define PIEDRA_AGREGADA 15
#define MADERA_AGREGADA 25
#define METAL_AGREGADO 40

#define TXT_LIGHT_AQUA_123 "\033[38;5;123m"
#define END_COLOR "\033[0m"
#define TXT_ITALIC "\033[3m"
#define TXT_UNDERLINE "\033[4m"
#define BGND_LIGHT_BLUE_32 "\033[48;5;32m"
#define BGND_GREEN_34 "\033[48;5;34m"
#define BGND_GRAY_240 "\033[48;5;240m"

// mapa.cpp
const char TERRENO = 'T';
const char LAGO = 'L';
const char CAMINO = 'C';



#endif