#include <iostream>

#include "casilleroInaccesible.h"
#include "../constantesCasilleros.h"
#include "../../../constantes/constantes.h"


CasilleroInaccesible::CasilleroInaccesible(){
    setearTipo(LAGO);
    setearColor(COLOR_LAGO);
}

int CasilleroInaccesible::obtenerEnergia(int jugadorActivo){
    return jugadorActivo ? ENERGIA_LAGO_JUGADOR_2 : ENERGIA_LAGO_JUGADOR_1;
}

void CasilleroInaccesible::responder() {
    std::cout << "Soy un casillero inaccesible" << std::endl;
}