#ifndef RECETA_H
#define RECETA_H

#include <string>


class Receta{
    private:
        int piedraReceta, maderaReceta, metalReceta, maximoContruiblesReceta;
        std::string produccionReceta;
    public:
        Receta();
        Receta(int piedra, int madera, int metal, int maximoContruibles);
        int obtenerMaterial(std::string material);
        void modificarMaterial(std::string material, int nuevaCantidad);
        void setearProduccion(std::string produccion);
        std::string obtenerProduccion();

        int obtenerMaximoConstruible();
};

#endif
