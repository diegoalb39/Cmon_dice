#include "listaDinamica.h"

void crearLista(t_lista* pl)
{
    *pl=NULL;
}

int insertarAlFinal(t_lista* pl, const void* dato, unsigned tam)
{
    //aca se podria reservar memoria para el nuevo nodo y guardar la direccion de la memoira reservada en una variable aux.

    while(*pl)
    {
        pl = &(*pl)->sig;
    }

    *pl= (t_nodo*) malloc(sizeof(t_nodo));
    if(*pl == NULL ||  ((*pl)->info = malloc(tam)) == NULL)
    {
        free(*pl);
        *pl=NULL;
        return NO_MEM;
    }

    memcpy((*pl)->info, dato, tam);
    (*pl)->tam= tam;
    (*pl)->sig= NULL;

    return TODO_OK;
}

int insertarOrdenado(t_lista* pl, const void* dato, unsigned tam, Cmp funCmp, int sinDup)
{
    t_nodo* nue;

    while(*pl && funCmp((*pl)->info, dato)<0)
    {
        pl = &(*pl)->sig;
    }

    if(sinDup && *pl && funCmp((*pl)->info, dato)==0)
        return DUPLICADO;

    nue= (t_nodo*) malloc(sizeof(t_nodo));
    if(!nue || (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return NO_MEM;
    }

    memcpy(nue->info, dato, tam);
    nue->tam= tam;

    nue->sig= *pl;
    *pl= nue;
    return TODO_OK;
}
void recorrerLista(t_lista* pl, Accion accion)
{
    while(*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }
}

/*int sacarDeLista(t_lista* pl, void* clave, unsigned tam, Cmp funCmp, Accion accion)
{
    t_nodo* elim;
    float total=0;

    while(*pl)
    {
        if(funCmp((*pl)->info, clave)==0)
        {
            elim= *pl;
            *pl= elim->sig;

            //memcpy(clave, (*pl)->info, minimo((*pl)->tam, tam));
            //accion
            free(elim->info);
            free(elim);
        }

         pl = &(*pl)->sig;
    }


    return  NO_ENCONTRADO;
}
*/

int sacarPrimeroDeLista(t_lista* pl, void* dato, unsigned tam)
{
    t_nodo* elim;

    if(!(*pl))
        return LISTA_VACIA;

    elim = *pl;
    memcpy(dato, elim->info, minimo(tam, elim->tam));
    *pl = elim->sig;

    free(elim->info);
    free(elim);

    return TODO_OK;
}
int sacarDeListaOrd(t_lista* pl, void* clave, unsigned tam, Cmp funCmp)
{
    t_nodo* elim;

    while(*pl && funCmp((*pl)->info, clave)<0)
    {
        pl = &(*pl)->sig;
    }

    if(*pl && funCmp((*pl)->info, clave)==0)
    {
        elim= *pl;
        *pl= elim->sig;

        memcpy(clave, elim->info, minimo(elim->tam, tam));
        free(elim->info);
        free(elim);

        return ENCONTRADO;
    }

    return  NO_ENCONTRADO;
}

int ordenarLista(t_lista* pl, Cmp funCmp)
{
    t_nodo **pSig, **pAct, *aux;

    if(!(*pl))
        return LISTA_VACIA;

    pSig= &(*pl)->sig;

    while(*pSig)
    {
        pAct= pl;

        while(*pAct != *pSig && funCmp((*pSig)->info, (*pAct)->info)>0)
        {
            pAct= &(*pAct)->sig;
        }

        if(*pAct != *pSig)
        {
            aux= *pAct;

            *pAct= *pSig;
            *pSig= (*pSig)->sig;
            (*pAct)->sig = aux;
        }
        else
            pSig= &(*pSig)->sig;
    }

    return TODO_OK;
}

void vaciarLista(t_lista* pl)
{
    t_nodo* elim;

    while(*pl)
    {
        elim= *pl;

        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int listaVacia(t_lista* pl)
{
    return *pl == NULL;
}

//PRIMITIVAS PARA DESORDENAR

t_nodo* obtener_nodo_porpos(t_lista*lista, int pos)
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

void desordenarLista(t_lista*lista_a, int cant)
{
    t_lista lista_b;
    int pos;

    pos = cant*0.5;

    lista_b = obtener_nodo_porpos(lista_a, pos);

    mezclaryunirlistas(lista_a, &lista_b);

    vaciarLista(&lista_b);
}
//PRIMITVAS DE ITERADOR

void crearIterador(t_lista_it* it)
{
    it->ini = NULL;
    it->cursor = NULL;
}
int inicializarIterador(t_lista_it* it, t_lista* lista) //esta implementacion sirve para una lista simple
{
    if(!*lista)
        return LISTA_VACIA;

    it->ini = *lista;
    it->cursor = it->ini;

    return TODO_OK;
}

int leerElemento(t_lista_it* it, void* dato, unsigned tam)
{
    if(!it->ini)
        return LISTA_VACIA;

    memcpy(dato, it->cursor->info, minimo(tam, it->cursor->tam));
    if(it->cursor->sig != NULL)
        it->cursor= it->cursor->sig;

    return TODO_OK;
}
void reiniciarCursor(t_lista_it* it)
{
    it->cursor= it->ini;
}
int finIterador(t_lista_it* it) //indefinido si se utiliza antes de inicializar
{
    return (it->cursor == NULL || it->cursor == it->ini);
}
