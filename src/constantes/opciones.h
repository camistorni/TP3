#ifndef OPCIONES_H
#define OPCIONES_H

enum opcionMenu_t {
    MENU_ERROR = -1,
    MENU_MODIFICAR_EDIFICIO_POR_NOMBRE = 1,
    MENU_LISTAR_EDIFICIOS = 2,
    MENU_MOSTRAR_MAPA = 3, 
    MENU_COMENZAR_PARTIDA = 4, 
    MENU_GUARDAR_Y_SALIR = 5, 
};

enum opcionSubmenu_t {
    JUGADOR_CONSTRUIR_EDIFICIO_POR_NOMBRE = 1, 
    JUGADOR_LISTAR_MIS_EDIFICIOS_CONSTRUIDOS = 2,
    JUGADOR_DEMOLER_EDIFICIO_POR_COORDENADA = 3,
    JUGADOR_ATACAR_EDIFICIO_POR_COORDENADA = 4,
    JUGADOR_REPARAR_EDIFICIO_POR_COORDENADA = 5,
    JUGADOR_COMPRAR_BOMBAS = 6,
    JUGADOR_CONSULTAR_COORDENADA = 7, 
    JUGADOR_MOSTRAR_INVENTARIO = 8, 
    JUGADOR_MOSTRAR_OBJETIVOS = 9,
    JUGADOR_RECOLECTAR_RECURSOS_PRODUCIDOS = 10,
    JUGADOR_MOVERSE_A_UNA_COORDENADA = 11,
    JUGADOR_FINALIZAR_TURNO = 12,
    JUGADOR_GUARDAR_Y_SALIR = 13,
};

#endif