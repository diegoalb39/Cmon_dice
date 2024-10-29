#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../listaDinamica/lista.h"
#include "desordenar_lista.h"

#define MSJ_MENU_INICIAL "///CMON DICE///\n\n[A] Jugar\n[B] Salir\n\nIngrese opcion: "
#define LI_MENU_INICIAL 'A'
#define LS_MENU_INICIAL 'B'

#define TAM_SECUENCIA 50
#define TAM_NOMBRE 25
#define ALL_OK 1
#define END 2


typedef struct
{
    char* secuencia;
    char* respuesta;
    unsigned vidas_usadas;
    unsigned puntos;//por ronda
}t_round;
//t_jugador solo conserva cadenas, se puede desistir de esta estructura.
typedef struct
{
    //unsigned n_orden;
    char nombre[TAM_NOMBRE];
    //unsigned puntaje_total;
    //t_cola rounds;
}t_jugador;



int menu(const char *msj, int li, int ls);
void wrapper_menuInicial();
int jugar();//funcion de francisco

int iniciar_juego();//agregada
void mostrar_y_generar_informe(t_lista* jug, t_lista* rondas, int* puntMax,
                               void(*accion)(void* dato1, void* dato2, void* p, void* pf));
void accion_mostrar(void* dato1, void* dato2, void* p, void* pf);








#endif // FUNCIONES_H_INCLUDED
