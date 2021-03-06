#ifndef CONSTANTESCASILLEROS_H
#define CONSTANTESCASILLEROS_H

const std::string CARACTER_COLOR_TERRENO    = "\033[1;41mT\033[0m";
const std::string CARACTER_COLOR_LAGO       = "\033[1;44mI\033[0m";
const std::string CARACTER_COLOR_CAMINO     = "\033[1;42mC\033[0m";
const std::string CARACTER_COLOR_BETUN      = "\033[1;42mC\033[0m";
const std::string CARACTER_COLOR_MUELLE     = "\033[1;42mC\033[0m";

// Para usarlo : cout << TXT_BOLD << "Bold text TXT_BOLD" << END_COLOR << endl;
const std::string TXT_BOLD = "\033[1m";
const std::string COLOR_JUGADOR_1 = "\033[38;5;8m";
const std::string COLOR_JUGADOR_2 = "\033[38;5;16m";
const std::string COLOR_NEUTRAL = "\033[38;5;7m";

const int ENERGIA_TERRENO = 25;
const int ENERGIA_LAGO_JUGADOR_1 = 2;
const int ENERGIA_LAGO_JUGADOR_2 = 5;
const int ENERGIA_CAMINO = 4;
const int ENERGIA_BETUN = 0;
const int ENERGIA_MUELLE_JUGADOR_1 = 5;
const int ENERGIA_MUELLE_JUGADOR_2 = 2;

#endif