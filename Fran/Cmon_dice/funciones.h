#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <process.h>
#include "colaDinamica/colaDinamica.h"
#include "listaDinamica/listaDinamica.h"
#include "curl/TP.h"
#include <mmsystem.h>

#define esNivelValido(a)((a) == 'F' || (a) == 'M' || (a) == 'D')
#define enRango(num,limInf,limSup)((num)>=(limInf) && (num)<=(limSup))
#define cambiarColorFondo(c) ((c)=='A' ? system("color 17") : ((c)=='V' ? system("color 27") : ((c)=='R' ? system("color 47") : system("color 67"))))

#define NOM_ARCH_CONF "config.txt"

#define TAM_SEC_INI 3
#define MAX_NOM 31
#define CAMPOS_ARCH_CONF 4

#define ERROR_ARCH -1
#define ERROR_MEM -1
#define ERROR_CURL -2
#define ERROR_THREAD -3

#define SALIR 1
#define RESP_COMPLETA 1
#define RESP_NO_COMP 2
#define RESP_INCORRECTA 3

typedef struct
{
    char* secuencia;
    char* respuesta;
    int vidasUsadas;
    int punt;
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
//mostrar orden jugadores, conf, teclas y preguntar si esta listo para empezar
int wrapper_mostrarInfoPartida(t_lista* jugadores, t_conf* conf, int *cantJres);
char mostrarInfoPartida(t_lista* jugadores, t_conf* conf);
void mostrarConf(t_conf conf);
//jugar -> usa biblioteca time y curl, conio usa colores, investigar sonidos y displays
int jugar(t_lista* jugadores, t_lista* infoRoundsPorJugador, t_conf* conf, int cantJres);
void guardarSecuencia(t_round* infoRound, t_contenedor* secuencia, int ronda);
void mostrarSecuencia(char const* secuencia, int cantTiempoSec);
int recibirRespuesta(t_round* infoRound, t_conf* conf, int ronda, int* pVidas);
int usarVidas(int* pVidas, char* secuencia, char* respuesta, int cantTiempoSec, int ronda);
int extenderSecuencia(t_round* infoRound, t_contenedor* secuencia, CURL** curl);
void limpiezaCurl(CURL** curl, char *URL, char *cadena_datos);
//en el informe habra que utilizar free() sobre infoRound.secuencia y respuesta

//generar archivo informe

#endif // FUNCIONES_H_INCLUDED
