#ifndef GRAFOS_DIJKSTRA_H
#define GRAFOS_DIJKSTRA_H


#include "CaminoMinimo.h"

class Dijkstra : public CaminoMinimo{
//Atributos
private:
    bool* verticesVisitados;
    int* distancia;
    int* recorrido;

//Métodos
    // Post: pone todos los valores del vector de verticesVisitados en "false" menos el origen
    void inicializarVisitados(int origen);

    // Post: pone las distancias exactamente igual que la distanciaOrigen
    void inicializarDistancia(const int * distanciaOrigen);

    // Post: llena el vector de recorrido con el origen
    void inicializarRecorrido(int origen);

    // Post: devuelve el número de vértice con menor distancia al origen
    int verticeMinimaDistancia();

    // Post: actualiza el vector de distancias y el de recorrido con los valores que impone vertice.
    void actualizarDistancia(int vertice);

    // Pre: para que tenga sentido, debe ejecutarse un recorrido previamente
    // Post: muestra por pantalla el resultado del recorrido.
    void mostrarRecorrido(int origen, int destino, int *energia, string *camino, int *tamano);

    // Post: muestra el estado instantaneo del vector de recorrido, distancia y visitados.
    void mostrarIteracion(int iteracion);
public:
    Dijkstra(Lista<Vertice> * vertices, int ** matrizAdyacencia);

    // Post: muestra por pantalla el camino mínimo entre el origen y el destino, detallando su recorrido y peso
    void caminoMinimo(int origen, int destino, int *energia, string *camino, int* tamano) override;

    ~Dijkstra() override;

};


#endif //GRAFOS_DIJKSTRA_H
