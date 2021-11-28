#ifndef CASILLERO_TRANSITABLE_H
#define CASILLERO_TRANSITABLE_H

#include "casillero.h"
#include "../materiales.h"

class CasilleroTransitable: public Casillero{
private:
    Material material;
public:
    CasilleroTransitable(int fila, int columna, char caracter);
    std::string obtenerTipo();
    void establecerTipo(std::string tipo);
    int obtenerCantidadMaterial();
    void establecerCantidadMaterial(int cantidad);
	void establecerRecursos();
    void establecerCaracterContenido();
	void responder();
    void establecerCaracterContenido(std::string caracter);
    std::string obtenerCaracterContenido();
    void liberar();

};


#endif // CASILLERO_TRANSITABLE_H
