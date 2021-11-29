#include <iostream>

#include "plantaElectrica.h"
#include "edificio.h"


PlantaElectrica::PlantaElectrica (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio):
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_plantaElectrica;
    cantidadConstruidos = 0;
    brindaMateriales = false;
}
