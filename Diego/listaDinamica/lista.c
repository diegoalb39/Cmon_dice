#include "lista.h"
void crearCola(t_cola *pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

void vaciarCola(t_cola *pc)
{
    t_nodo *elim;
    while(pc->pri){
        elim = pc->pri;
        pc->pri = elim->sig;
        free(elim->dato);
        free(elim);
    }
    pc->ult = NULL;
}

int colaVacia(const t_cola *pc)
{
    return NULL == pc->pri;
}

int colaLlena(const t_cola *pc, unsigned tam)
{
    return ALL_OK;
}

int ponerEnCola(t_cola *pc, const void *info, unsigned tam)
{
    t_nodo *nue;
    nue = malloc(sizeof(t_nodo));
    if(!nue)
        return NO_MEMORY;
    nue->dato = malloc(tam);
    if(!nue->dato){
        free(nue);
        return NO_MEMORY;
    }
    memcpy(nue->dato,info,tam);
    nue->tam = tam;
    nue->sig = NULL;

    if(!pc->pri)
        pc->pri = nue;
    else
        pc->ult->sig = nue;
    pc->ult = nue;

    return ALL_OK;
}

int verPrimeroCola(const t_cola *pc, void *dato, unsigned tam)
{
    if(!pc->pri)
        return EMPTY;
    memcpy(dato, pc->pri->dato, MINIMO(pc->pri->tam, tam));
    return ALL_OK;
}

int sacarDeCola(t_cola *pc, void *buffer, unsigned tam)
{
    t_nodo *elim;
    if(!pc->pri)
        return EMPTY;
    elim = pc->pri;
    pc->pri = elim->sig;
    memcpy(buffer, elim->dato, MINIMO(elim->tam, tam));
    free(elim->dato);
    free(elim);
    if(!pc->pri)
        pc->ult = NULL;
    return ALL_OK;
}








