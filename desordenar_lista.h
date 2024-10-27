#ifndef DESORDENAR_LISTA_H_INCLUDED
#define DESORDENAR_LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_nodo
{
    unsigned tamdato;
    void*dato;
    struct s_nodo*sig;

}t_nodo;

typedef t_nodo* t_lista;

void crearlista(t_lista*);

int ponerenlista_final(t_lista*, const void*, unsigned);

void mostrar_int(void*);
void recorrerlista(t_lista*, void (*accion)(void*));

void vaciarlista(t_lista*);

////
t_nodo*crear_sublista_desdepos(t_lista*, int);

void mezclar_y_unirlistas(t_lista*, t_lista*);

void mezclar_jugadores(t_lista*, int);

#endif // DESORDENAR_LISTA_H_INCLUDED
