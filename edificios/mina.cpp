#include <iostream>

#include "mina.h"
#include "edificio.h"


Mina::Mina (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_MINA;
    cantidadConstruidos = 0;
    brindaMateriales = true;
}
