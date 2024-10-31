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
#include <mmsystem.h>
#include "colaDinamica/colaDinamica.h"
#include "listaDinamica/listaDinamica.h"
#include "curl/TP.h"

#define esNivelValido(a)((a) == 'F' || (a) == 'M' || (a) == 'D')
#define enRango(num,limInf,limSup)((num)>=(limInf) && (num)<=(limSup))
#define cambiarColorFondo(c) ((c)=='A' ? system("color 17") : ((c)=='V' ? system("color 27") : ((c)=='R' ? system("color 47") : system("color 67"))))

#define NOM_ARCH_CONF "config.txt"

#define TAM_SEC_INI 10
#define MAX_NOM 41
#define CAMPOS_ARCH_CONF 4
#define CANT_DIFS 3

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

int ingresoJugadores(t_lista* jugadores);
void mostrarJugadores(t_lista* jugadores);
int leerConf(const char* archConf, t_conf* varConf);
int wrapper_mostrarInfoPartida(t_lista* jugadores, t_conf* conf, int *cantJres);
char mostrarInfoPartida(t_lista* jugadores, t_conf* conf);
void mostrarConf(t_conf conf);
int jugar(t_lista* jugadores, t_lista* infoRoundsPorJugador, t_conf* conf, int cantJres);
void guardarSecuencia(t_round* infoRound, t_contenedor* secuencia, int ronda);
void mostrarSecuencia(char const* secuencia, int cantTiempoSec);
int recibirRespuesta(t_round* infoRound, t_conf* conf, int ronda, int* pVidas);
int usarVidas(int* pVidas, char* secuencia, char* respuesta, int cantTiempoSec, int ronda);
int extenderSecuencia(t_round* infoRound, t_contenedor* secuencia, CURL** curl);
void limpiezaCurl(CURL** curl, char *URL, char *cadena_datos);

void mostrar_y_generar_informe(t_lista* jug, t_lista* rondas, int* puntMax,
                               void(*accion)(void* dato1, void* dato2, void* p, void* pf, void* pc));
void accion_mostrar(void* dato1, void* dato2, void* p, void* pf, void* pc);

#endif // FUNCIONES_H_INCLUDED
