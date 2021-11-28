#include <iostream>

#include "planta_electrica.h"
#include "edificio.h"


PlantaElectrica::PlantaElectrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_PLANTA_ELECTRICA;
    cantidadConstruidos = 0;
    brindaMateriales = false;
}
