#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "colaDinamica/colaDinamica.h"
#include "listaDinamica/listaDinamica.h"
#include "curl/TP.h"
//faltaria la de time

#define esNivelValido(a)((a) == 'F' || (a) == 'M' || (a) == 'D')

#define NOM_ARCH_CONF "config.txt"

#define MAX_SEC 11
#define MAX_NOM 31
#define CAMPOS_ARCH_CONF 4

#define ERROR_MEM 1
#define ERROR_ARCH 1

typedef struct
{
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
int ingresoJugadores(t_lista* jugadores);
void mostrarJugadores(t_lista* jugadores);
//lectura de conf segun dificultad elegida -> despues de esto usar desordenarLista
int leerConf(const char* archConf, t_conf* varConf);
void mostrarConf(t_conf conf);
//mostrar orden jugadores, conf, teclas y preguntar si esta listo para empezar
//jugar -> usa biblioteca time y curl, conio usa colores, investigar sonidos y displays
//generar archivo informe

#endif // FUNCIONES_H_INCLUDED
