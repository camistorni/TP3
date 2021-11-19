#ifndef CASILLERO_TRANSITABLE_H
#define CASILLERO_TRANSITABLE_H

#include "casillero.h"
#include "../materiales.h"

class Casillero_transitable: public Casillero{
private:
    Material material;
public:
    Casillero_transitable(int fila, int columna, char caracter);
    std::string obtener_tipo();
    void establecer_tipo(std::string tipo);
    int obtener_cantidad_material();
    void establecer_cantidad_material(int cantidad);
	void establecer_recursos();
    void establecer_caracter_contenido();
	void responder();
    void establecer_caracter_contenido(std::string caracter);
    std::string obtener_caracter_contenido();
    void liberar();

};


#endif // CASILLERO_TRANSITABLE_H
