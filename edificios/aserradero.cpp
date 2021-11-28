#include <iostream>

#include "aserradero.h"
#include "edificio.h"


Aserradero::Aserradero (int piedra, int madera, int metal, int cantMaxConstruido, std::string tipoEdificio): 
TipoEdificio (piedra, madera, metal, cantMaxConstruido, tipoEdificio){
    caracter = CARACTER_ASERRADERO;
    cantidadConstruidos = 0;
    brindaMateriales = true;
    
}
