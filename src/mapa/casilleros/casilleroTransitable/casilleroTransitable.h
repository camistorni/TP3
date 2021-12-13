#ifndef CASILLEROTRANSITABLE_H
#define CASILLEROTRANSITABLE_H

#include "../casillero.h"
#include "../../../materiales/materiales.h"

class CasilleroTransitable: public Casillero{
    private:
        Material* material;
        bool hayMaterial;
    public:
        ~CasilleroTransitable();
        Material* recolectarMaterial();
        void depositarMaterial(Material* material);
        bool hayMaterialDepositado();
        void responder();
        

};

class CasilleroCamino: public CasilleroTransitable{
    public:
        CasilleroCamino();
};
class CasilleroBetun: public CasilleroTransitable{
    public:
        CasilleroBetun();
};
class CasilleroMuelle: public CasilleroTransitable{
    public:
        CasilleroMuelle();
        int obtenerEnergia(int jugadorActivo);
};

#endif // casilleroTransitable_H
