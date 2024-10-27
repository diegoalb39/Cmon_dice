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
t_nodo*obtener_nodo_porpos(t_lista*lista, int pos)
{
    t_nodo*nodobuscado;

    while( (*lista) && (0 != pos) )
    {
        lista = &(*lista)->sig;

        pos--;
    }

    if(0 != pos)
        nodobuscado = NULL;
    else
    {
        nodobuscado = *lista;
        *lista = NULL;
    }

    return nodobuscado;
}

void mezclaryunirlistas(t_lista*lista_a, t_lista*lista_b)
{
    t_nodo *aux, *aux_mov;
    int num_lista;

    aux = NULL;

    srand(time(NULL));

    while( (*lista_a) || (*lista_b) )
    {
        num_lista = (rand()%2);
        printf("%d ", num_lista);

        if( ( ((*lista_a) && (*lista_b)) && !(num_lista) ) || ((*lista_a) && !(*lista_b)) )
        {
            aux_mov = *lista_a;
            *lista_a = aux_mov->sig;
        }
        else
        {
            aux_mov = *lista_b;
            *lista_b = aux_mov->sig;
        }

        aux_mov->sig = aux;
        aux = aux_mov;
    }

    *lista_a = aux;
}

void desordenarlista(t_lista*lista_a, int cant)
{
    t_lista lista_b;
    int pos;

    pos = cant/2;
    printf("\n-pos: %d\n\n", pos);

    lista_b = obtener_nodo_porpos(lista_a, pos);

    printf("//lista_a//\n");
    recorrerlista(lista_a, mostrar_int);
    printf("\n\n");

    printf("//lista_b//\n");
    recorrerlista(&lista_b, mostrar_int);
    printf("\n\n");

    mezclaryunirlistas(lista_a, &lista_b);

    vaciarlista(&lista_b);
}
