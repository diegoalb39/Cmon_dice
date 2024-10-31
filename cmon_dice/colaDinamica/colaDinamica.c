#include "colaDinamica.h"

void crearCola(t_cola *c)
{
    c->pri = NULL;
    c->ult = NULL;
}

void vaciarCola(t_cola* c)
{
    t_nodo *elim;

    while(c->pri)
    {
        elim= c->pri;

        c->pri= elim->sig;
        free(elim->info);
        free(elim);
    }
}

int colaVacia(const t_cola* c)
{
    return c->pri == NULL;
}

int colaLlena(const t_cola* c, unsigned tamInfo)
{
    return TODO_OK;
}

int ponerEnCola(t_cola* c, const void* info, unsigned tamInfo)
{
    t_nodo* nue= (t_nodo*) malloc(sizeof(t_nodo));

    if(!nue || (nue->info = malloc(tamInfo)) == NULL)
    {
        free(nue);
        return NO_MEM;
    }

    nue->tam = tamInfo;
    memcpy(nue->info, info, tamInfo);
    nue->sig = NULL;

    if(!c->pri)
        c->pri = nue;
    else
        c->ult->sig= nue;

    c->ult = nue;

    return TODO_OK;
}

int verPrimero(const t_cola* c, void* dato, unsigned tamDato)
{
    if(!c->pri)
        return COLA_VACIA;

    memcpy(dato, c->pri->info, minimo(c->pri->tam, tamDato));

    return TODO_OK;
}

int sacarDeCola(t_cola* c, void* dato, unsigned tamDato)
{
    if(!c->pri)
        return COLA_VACIA;

    t_nodo *elim= c->pri;

    c->pri= elim->sig;
    memcpy(dato, elim->info, minimo(elim->tam, tamDato));

    free(elim->info);
    free(elim);

    return TODO_OK;
}
