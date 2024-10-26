#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colaDinamica/colaDinamica.h"
#include "listaDinamica/listaDinamica.h"
#include "curl/TP.h"
//faltaria la de time

#define MAX_SEC 50
#define MAX_NOM 30

typedef struct
{
    int numJugador;
    char nombre[MAX_NOM];
    int puntTotal;
    t_cola infoRounds;
}t_jugador;

typedef struct
{
    char secuencia[MAX_SEC];
    char respuesta[MAX_SEC];
    int vidasUsadas;
}t_round;

typedef struct
{
    char nivel;
    int cantTiempoSec;
    int cantTiempoResp;
    int cantVidas;
}t_conf;

//menu
//ingreso de jugadores
//lectura de conf segun dificultad elegida -> despues de esto usar desordenarLista
//mostrar orden jugadores, conf, teclas y preguntar si esta listo para empezar
//jugar -> usa biblioteca time y curl, conio usa colores, investigar sonidos y displays
//generar archivo informe

#endif // FUNCIONES_H_INCLUDED
