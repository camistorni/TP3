#include "materiales/materiales.h"
#include "edificios/edificio.h"
#include "juego/juego.h"
#include "menu/Menu.hpp"
#include "juego/grafo/Grafo.h"
#include "constantes/opciones.h"


#ifdef __linux__
#define CLR_SCREEN "clear"
#endif

#ifdef __MINGW32__
#define CLR_SCREEN "CLS"
#endif

int main() {
	Menu menu;

	menu.iniciarJuego();
	
	return 0;
}
