#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define MAX_VIDAS 5
#define TAM_INPUT 100
#define TIEMPO_LIMITE 20
#include "../listaDinamica/lista.h"

#define MSJ_MENU_INICIAL "///CMON DICE///\n\n[A] Jugar\n[B] Salir\n\nIngrese opcion: "
#define LI_MENU_INICIAL 'A'
#define LS_MENU_INICIAL 'B'

#define TAM_SECUENCIA 50
#define TAM_NOMBRE 25
#define ALL_OK 1
#define END 2


typedef struct
{
    char secuencia[TAM_SECUENCIA];
    char respuesta [TAM_SECUENCIA];
    unsigned vidas_usadas;
    unsigned puntos;
}t_round;

typedef struct
{
    unsigned n_orden;
    char nombre[TAM_NOMBRE];
    unsigned puntaje_total;
    t_cola rounds;
}t_jugador;

typedef struct
{
    char*cadena_datos;
    unsigned tamcontenido;

}t_contenedor;


int menu(const char *msj, int li, int ls);
void wrapper_menuInicial();
int jugar();



















#endif // FUNCIONES_H_INCLUDED
