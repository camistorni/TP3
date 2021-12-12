#include <iostream>

#include "casillero.h"


Casillero::Casillero() {}
Casillero::~Casillero() {}

void Casillero::responder() {}

void Casillero::setearTipo(char tipo) {
    this -> tipo = tipo;
}
char Casillero::obtenerTipo() {
    return tipo;
}
void Casillero::setearCaracter(char caracter) {
    this -> caracter = caracter;
}		
char Casillero::obtenerCaracter() {
    return (jugador != -1) ? (jugador ? '2' : '1') : caracter;
}	
void Casillero::setearColor(std::string color) {
    this -> color = color;
}
std::string Casillero::obtenerColor() {
    return color;
}
void Casillero::setearEnergia(int energia) {
    this -> energia = energia;
}
int Casillero::obtenerEnergia(int jugadorActivo) {
    return energia;
}
void Casillero::setearJugador(int jugador) {
    this -> jugador = jugador;
}

int Casillero::obtenerJugador() {
    return jugador;
}

void Casillero::removerJugador(int jugador) {
    jugador = CARACTER_VACIO;
}