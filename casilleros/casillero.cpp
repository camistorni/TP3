#include <iostream>

#include "casillero.h"


Casillero::Casillero(int fila, int columna, char caracter){
    this -> fila = fila;
    this -> columna = columna;
    this -> caracter = caracter;
}



char Casillero::obtenerCaracter(){
    return caracter;
}
int Casillero::obtenerFila(){
    return fila;
}
int Casillero::obtenerColumna(){
    return columna;
}
std::string Casillero::obtenerCaracterColor(){
    return caracterColor;
}
bool Casillero::esConstruible(){
   return caracter == 'T';
}
bool Casillero::esTransitable(){
    return caracter == 'C';
}
