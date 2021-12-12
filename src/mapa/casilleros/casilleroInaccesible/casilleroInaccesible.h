#ifndef casilleroInaccesible_H
#define casilleroInaccesible_H

#include "../casillero.h"

class CasilleroInaccesible: public Casillero{
    public:
        CasilleroInaccesible();
        int obtenerEnergia(int jugadorActivo);
        void responder();
};


#endif // casilleroInaccesible_H
