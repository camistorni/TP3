#include <iostream>

#include "fabrica.h"
#include "edificio.h"


Fabrica::Fabrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_FABRICA;
    cantidadConstruidos = 0;
    brindaMateriales = true;
}
