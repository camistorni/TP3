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
    return caracter;
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
    setearCaracter(jugador == 0 ? CARACTER_JUGADOR1 : CARACTER_JUGADOR2);
    this -> jugador = jugador;
}

int Casillero::obtenerJugador() {
    return jugador;
}

void Casillero::removerJugador() {
    caracter = CARACTER_VACIO;
    jugador = -1;
}