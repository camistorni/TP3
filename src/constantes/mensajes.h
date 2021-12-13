#ifndef MENSAJES_H
#define MENSAJES_H
#include <iostream>

const std::string MJE_ERROR_OPCION = "Error, la opcion ingresada es incorrecta.";

const string MJE_COMPRAR_ANDYPOLIS = "Comprar Andypolis: haber juntado 100.000 andycoins a lo largo de la partida.";
const string MJE_EDAD_DE_PIEDRA = "Edad de piedra: tener en el inventario 50.000 piedras.";
const string MJE_BOMBARDERO = "Bombardero: haber usado 5 bombas.";
const string MJE_ENERGETICO = "Energetico: haber terminado un turno con 100 puntos de energia.";
const string MJE_LETRADO = "Letrado: haber construido el maximo posible de escuelas.";
const string MJE_MINERO = "Minero: haber construido una mina de cada tipo.";
const string MJE_CANSADO = "Cansado: terminar un turno con 0 de energia.";
const string MJE_CONSTRUCTOR = "Constructor: constuir un edificio de cada tipo.";
const string MJE_ARMADO = "Armado: tener 10 bombas en el inventario.";
const string MJE_EXTREMISTA = "Extremista: haber comprado 500 bombas en una partida";

enum listadoObjetivos_t {
    COMPRAR_ANDYPOLIS = 0,
    EDAD_DE_PIEDRA = 1,
    BOMBARDERO = 2,
    ENERGETICO = 3,
    LETRADO = 4,
    MINERO = 5, 
    CANSADO = 6,
    CONSTRUCTOR = 7,
    ARMADO = 8,
    EXTREMISTA = 9,
};

const string OBJETIVOS[10] = {
    MJE_COMPRAR_ANDYPOLIS,
    MJE_EDAD_DE_PIEDRA,
    MJE_BOMBARDERO,
    MJE_ENERGETICO,
    MJE_LETRADO,
    MJE_MINERO,
    MJE_CANSADO,
    MJE_CONSTRUCTOR,
    MJE_ARMADO,
    MJE_EXTREMISTA
};

#endif