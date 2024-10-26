#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define minimo(a,b)((a)<(b)?(a):(b))

#define NO_MEM 1
#define COLA_VACIA 1
#define TODO_OK 0

typedef struct s_nodo
{
    unsigned tam;
    void* info;
    struct s_nodo* sig;
}t_nodo;

typedef struct
{
    t_nodo* pri;
    t_nodo* ult;
}t_cola;

//7 prim
void crearCola(t_cola *c);
void vaciarCola(t_cola* c);
int colaVacia(const t_cola* c);
int colaLlena(const t_cola* c, unsigned tamInfo);
int ponerEnCola(t_cola* c, const void* info, unsigned tamInfo);
int verPrimero(const t_cola* c, void* dato, unsigned tamDato);
int sacarDeCola(t_cola* c, void* dato, unsigned tamDato);

#endif // COLADINAMICA_H_INCLUDED
