#ifndef CASILLERO_INACCESIBLE_H
#define CASILLERO_INACCESIBLE_H

#include "casillero.h"

class CasilleroInaccesible: public Casillero{
public:
    CasilleroInaccesible(int fila, int columna, char caracter);
    std::string obtenerTipo();
    void establecerTipo(std::string tipo);
    int obtenerCantidadMaterial();
    void establecerCantidadMaterial(int cantidad);
	void establecerRecursos();
	virtual void responder();
    void establecerCaracterContenido(std::string caracter);
    std::string obtenerCaracterContenido();
    void liberar();
};


#endif // CASILLERO_INACCESIBLE_H
