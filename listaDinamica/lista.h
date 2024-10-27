#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Nodo/nodo.h"

#define NO_MEMORY 0
#define EMPTY 0
#define ALL_OK 1

#define MINIMO(x,y) ((x)<(y) ? (x) : (y))

//typedef struct s_nodo
//{
//    void *dato;
//    unsigned tam;
//    struct s_nodo *sig;
//}t_nodo;

typedef struct
{
    t_nodo *pri;
    t_nodo *ult;
}t_cola;

typedef struct
{
    t_nodo *ini;
    t_nodo *cursor;
}t_lista_it; //lista iteradora

//typedef t_nodo* lista;

void crearCola(t_cola *pc);
void vaciarCola(t_cola *pc);
int colaVacia(const t_cola *pc);
int colaLlena(const t_cola *pc, unsigned tam);
int ponerEnCola(t_cola *pc, const void *info, unsigned tam);
int verPrimeroCola(const t_cola *pc, void *dato, unsigned tam);
int sacarDeCola(t_cola *pc, void *buffer, unsigned tam);


#endif // LISTA_H_INCLUDED
