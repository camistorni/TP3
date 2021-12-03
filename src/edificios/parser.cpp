#include <iostream>

#include "parser.h"
#include "edificio.h"

Parser::Parser (std::string* lectura){
    lecturaArchivo = lectura;
}

Edificio* Parser::procesarEntrada(){
    /*
    Edificio* edificio;
    
    if (this -> edificio() == "aserradero"){
        edificio = new Aserradero();
    }
    else if (this -> edificio() == "escuela"){
        edificio = new Escuela (piedra(), madera(), metal(), cantMaxConstruido(), this -> edificio());
    }
    else if (this -> edificio() == "fabrica"){
        edificio = new Fabrica (piedra(), madera(), metal(), cantMaxConstruido(), this -> edificio());
    }
    else if (this -> edificio() == "mina"){
        edificio = new Mina (piedra(), madera(), metal(), cantMaxConstruido(), this -> edificio());
    }
    else if (this -> edificio() == "obelisco"){
        edificio = new Obelisco (piedra(), madera(), metal(), cantMaxConstruido(), this -> edificio());
    }
    else if (this -> edificio() == "plantaElectrica"){
        edificio = new PlantaElectrica (piedra(), madera(), metal(), cantMaxConstruido(), this -> edificio());
    }
    else {
        std::cout << "Hay un edificio que no existe" << std::endl; 
    }
    */
    return edificio;

}




std::string Parser::edificio(){
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
