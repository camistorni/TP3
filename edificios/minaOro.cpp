#include <iostream>

#include "minaOro.h"
#include "edificio.h"


MinaOro::MinaOro (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_MINA_ORO;
    cantidadConstruidos = 0;
    brindaMateriales = true;
}
