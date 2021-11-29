#include <iostream>

#include "parser.h"
#include "edificio.h"
#include "tiposEdificios.h"
#include "aserradero.h"
#include "escuela.h"
#include "fabrica.h"
#include "mina.h"
#include "obelisco.h"
#include "plantaElectrica.h"

Parser::Parser (std::string* lectura){
    lecturaArchivo = lectura;
}

TipoEdificio* Parser::procesarEntrada(){
    TipoEdificio* tipoEdificio;
    
    if (this -> tipoEdificio() == "aserradero"){
        tipoEdificio = new Aserradero (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else if (this -> tipoEdificio() == "escuela"){
        tipoEdificio = new Escuela (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else if (this -> tipoEdificio() == "fabrica"){
        tipoEdificio = new Fabrica (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else if (this -> tipoEdificio() == "mina"){
        tipoEdificio = new Mina (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else if (this -> tipoEdificio() == "obelisco"){
        tipoEdificio = new Obelisco (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else if (this -> tipoEdificio() == "plantaElectrica"){
        tipoEdificio = new PlantaElectrica (piedra(), madera(), metal(), cantMaxConstruido(), this -> tipoEdificio());
    }
    else {
        std::cout << "Hay un edificio que no existe" << std::endl; 
    }
    
    return tipoEdificio;

}




std::string Parser::tipoEdificio(){
    return lecturaArchivo[0];
}

int Parser::piedra(){
    return stoi(lecturaArchivo[1]);
}

int Parser::madera(){
    return stoi(lecturaArchivo[2]);
}

int Parser::metal(){
    return stoi(lecturaArchivo[3]);
}

int Parser::cantMaxConstruido(){
    return stoi(lecturaArchivo[4]);
}
