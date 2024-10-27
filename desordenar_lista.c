#include "desordenar_lista.h"

void crearlista(t_lista*lista)
{
    *lista = NULL;
}

int ponerenlista_final(t_lista*lista, const void*dato, unsigned tamdato)
{
    t_nodo*nodonue;

    while(*lista)
        lista = &(*lista)->sig;

    nodonue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nodonue)
        return 0;

    nodonue->dato = malloc(tamdato);
    if(!(nodonue->dato))
    {
        free(nodonue);
        return 0;
    }

    memcpy( (nodonue->dato), dato, tamdato );
    nodonue->tamdato = tamdato;
    nodonue->sig = NULL;

    *lista = nodonue;

    return 1;
}

void mostrar_int(void*dato)
{
    printf("%d ", *(int*)dato);
}

void recorrerlista(t_lista*lista, void (*accion)(void*))
{
    while(*lista)
    {
        accion((*lista)->dato);

        lista = &(*lista)->sig;
    }
}

void vaciarlista(t_lista*lista)
{
    t_nodo*nodoelim;

    while(*lista)
    {
        nodoelim = *lista;

        *lista = nodoelim->sig;

        free(nodoelim->dato);
        free(nodoelim);
    }
}

////
t_nodo*crear_sublista_desdepos(t_lista*lista, int pos)
{
    t_nodo*nue_prinodo;

    pos--;

    while( (*lista) && (0 != pos) )
    {
        lista = &(*lista)->sig;

        pos--;
    }

    if(0 != pos)
        nue_prinodo = NULL;
    else
    {
        nue_prinodo = *lista;
        *lista = NULL;
    }

    return nue_prinodo;
}

void mezclar_y_unirlistas(t_lista*lista_a, t_lista*lista_b)
{
    t_nodo *destino_temp, *aux_movimiento;
    int num_lista;

    destino_temp = NULL;

    srand(time(NULL));

    while( (*lista_a) || (*lista_b) )
    {
        num_lista = (rand()%2);

        if( ( ((*lista_a) && (*lista_b)) && !(num_lista) ) || ((*lista_a) && !(*lista_b)) )
        {
            aux_movimiento = *lista_a;
            *lista_a = aux_movimiento->sig;
        }
        else
        {
            aux_movimiento = *lista_b;
            *lista_b = aux_movimiento->sig;
        }

        aux_movimiento->sig = destino_temp;
        destino_temp = aux_movimiento;
    }

    *lista_a = destino_temp;
}

void mezclar_jugadores(t_lista*lista_a, int cant)
{
    t_lista lista_b;

    lista_b = crear_sublista_desdepos(lista_a, ((cant/2) + 1));

    mezclar_y_unirlistas(lista_a, &lista_b);
}
