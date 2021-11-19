#include <iostream>

#include "parser.h"
#include "edificio.h"
#include "tipos_edificios.h"
#include "aserradero.h"
#include "escuela.h"
#include "fabrica.h"
#include "mina.h"
#include "obelisco.h"
#include "planta_electrica.h"

Parser::Parser (std::string* lectura){
    lectura_archivo = lectura;
}

Tipo_edificio* Parser::procesar_entrada(){
    Tipo_edificio* tipo_edificio;
    
    if (this -> tipo_edificio() == "aserradero"){
        tipo_edificio = new Aserradero (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else if (this -> tipo_edificio() == "escuela"){
        tipo_edificio = new Escuela (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else if (this -> tipo_edificio() == "fabrica"){
        tipo_edificio = new Fabrica (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else if (this -> tipo_edificio() == "mina"){
        tipo_edificio = new Mina (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else if (this -> tipo_edificio() == "obelisco"){
        tipo_edificio = new Obelisco (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else if  (this -> tipo_edificio() == "planta_electrica"){
        tipo_edificio = new Planta_electrica (piedra(), madera(), metal(), cant_max_construido(), this -> tipo_edificio());
    }
    else {
        std::cout << "Hay un edificio que no existe" << std::endl; 
    }
    
    return tipo_edificio;

}




std::string Parser::tipo_edificio(){
    return lectura_archivo[0];
}

int Parser::piedra(){
    return stoi(lectura_archivo[1]);
}

int Parser::madera(){
    return stoi(lectura_archivo[2]);
}

int Parser::metal(){
    return stoi(lectura_archivo[3]);
}

int Parser::cant_max_construido(){
    return stoi(lectura_archivo[4]);
}
