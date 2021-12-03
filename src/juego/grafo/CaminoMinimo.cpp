#include "CaminoMinimo.h"

CaminoMinimo::CaminoMinimo(Lista<Vertice> *vertices, int **matrizAdyacencia) {
    this -> vertices = vertices;
    this -> matrizAdyacencia = matrizAdyacencia;
    cantidadVertices = vertices -> obtenerCantidadDeElementos();
}

void CaminoMinimo::mostrarRecorrido(int origen, int destino){
}
