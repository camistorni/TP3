#include <iostream>

#include "obelisco.h"
#include "edificio.h"


Obelisco::Obelisco (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_OBELISCO;
    cantidadConstruidos = 0;
    brindaMateriales = false;
}
