#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_nodo
{
    void *dato;
    unsigned tam;
    struct s_nodo *sig;
}t_nodo;

typedef struct
{
    t_nodo *ini;
    t_nodo *ult;
}t_cola;

typedef struct
{
    t_nodo *ini;
    t_nodo *cursor;
}t_lista_it; //lista iteradora

typedef t_nodo* lista;


#endif // LISTA_H_INCLUDED
