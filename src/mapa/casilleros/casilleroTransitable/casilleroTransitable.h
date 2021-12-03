#ifndef CASILLEROTRANSITABLE_H
#define CASILLEROTRANSITABLE_H

#include "../casillero.h"
#include "../../../materiales/materiales.h"

class CasilleroTransitable: public Casillero{
    private:
        Material* material;
        bool hayMaterial;
    public:
        Material* recolectarMaterial();
        void depositarMaterial(Material* material);
        void responder();
        bool hayMaterialDepositado();

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
