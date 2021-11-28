#include <iostream>

#include "edificio.h"

Edificio::~Edificio(){
}

//Cosntructor 
Edificio::Edificio(int fila, int columna){
    this -> fila = fila;
    this -> columna = columna;
}
//Constructor
Edificio::Edificio(){
    this -> fila = -1;
    this -> columna = -1;
}


int Edificio::obtenerColumna(){
    return columna;
}

int Edificio::obtenerFila(){
    return fila;
}