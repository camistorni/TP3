#include <iostream>

#include "escuela.h"
#include "edificio.h"


Escuela::Escuela (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_ESCUELA;
    cantidadConstruidos = 0;
    brindaMateriales = false;
}
