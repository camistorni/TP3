#ifndef OPCIONES_H
#define OPCIONES_H

enum opcionMenu_t {
    ERROR = -1,
    MODIFICAR_EDIFICIO_POR_NOMBRE = 1,
    LISTAR_EDIFICIOS = 2,
    MOSTRAR_MAPA = 3, 
    COMENZAR_PARTIDA = 4, 
    GUARDAR_Y_SALIR = 5, 
    SALIR = 6
};

enum opcionSubmenu_t {
    ERROR = -1,
    CONSTRUIR_EDIFICIO_POR_NOMBRE = 1, 
    LISTAR_EDIFICIOS_CONSTRUIDOS = 2,
    DEMOLER_EDIFICIO_POR_COORDENADA = 3,
    ATACAR_EDIFICIO_POR_COORDENADA = 4,
    REPARAR_EDIFICIO_POR_COORDENADA = 5,
    COMPRAR_BOMBAS = 6,
    CONSULTAR_COORDENADA = 7, 
    MOSTRAR_INVENTARIO = 8, 
    MOSTRAR_OBJETIVOS = 9,
    RECOLECTAR_RECURSOS_PRODUCIDOS = 10,
    MOVERSE_A_UNA_COORDENADA = 11,
    FINALIZAR_TURNO = 12,
    GUARDAR_Y_SALIR = 13,
    SALIR = 14
};

#endif