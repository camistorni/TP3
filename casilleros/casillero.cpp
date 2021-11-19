#include <iostream>

#include "casillero.h"


Casillero::Casillero(int fila, int columna, char caracter){
    this -> fila = fila;
    this -> columna = columna;
    this -> caracter = caracter;
}



char Casillero::obtener_caracter(){
    return caracter;
}
int Casillero::obtener_fila(){
    return fila;
}
int Casillero::obtener_columna(){
    return columna;
}
std::string Casillero::obtener_caracter_color(){
    return caracter_color;
}
bool Casillero::es_construible(){
   return caracter == 'T';
}
bool Casillero::es_transitable(){
    return caracter == 'C';
}
