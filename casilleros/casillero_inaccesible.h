#ifndef CASILLERO_INACCESIBLE_H
#define CASILLERO_INACCESIBLE_H

#include "casillero.h"

class Casillero_inaccesible: public Casillero{
public:
    Casillero_inaccesible(int fila, int columna, char caracter);
    std::string obtener_tipo();
    void establecer_tipo(std::string tipo);
    int obtener_cantidad_material();
    void establecer_cantidad_material(int cantidad);
	void establecer_recursos();
	virtual void responder();
    void establecer_caracter_contenido(std::string caracter);
    std::string obtener_caracter_contenido();
    void liberar();
};


#endif // CASILLERO_INACCESIBLE_H
