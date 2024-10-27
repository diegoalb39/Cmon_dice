#ifndef LISTADINAMICA_H_INCLUDED
#define LISTADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../nodo.h"

#define minimo(a,b)((a)<(b)?(a):(b))

#define NO_MEM 1
#define TODO_OK 0

#define ENCONTRADO 0
#define NO_ENCONTRADO 1
#define DUPLICADO 2

#define LISTA_VACIA 1

typedef t_nodo* t_lista;

typedef struct
{
    t_nodo* ini;
    t_nodo* cursor;
}t_lista_it;

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Accion)(const void* e);

void crearLista(t_lista* pl);
int insertarAlFinal(t_lista* pl, const void* dato, unsigned tam);
int insertarOrdenado(t_lista* pl, const void* dato, unsigned tam, Cmp funCmp, int sinDup);
int sacarDeLista(t_lista* pl,void* clave, unsigned tam, Cmp funCmp, Accion accion);
int sacarDeListaOrd(t_lista* pl, void* clave, unsigned tam, Cmp funCmp);
void recorrerLista(t_lista* pl, Accion accion);
int ordenarLista(t_lista* pl, Cmp funCmp);
void vaciarLista(t_lista* pl);

//PRIMITIVAS PARA ITERADOR DE LISTA
void crearIterador(t_lista_it* it);
int inicializarIterador(t_lista_it* it, t_lista* lista);
int leerElemento(t_lista_it* it, void* dato, unsigned tam);
void reiniciarCursor(t_lista_it* it);
int finIterador(t_lista_it* it);
#endif // LISTADINAMICA_H_INCLUDED
