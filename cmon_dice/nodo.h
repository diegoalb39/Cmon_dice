#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

typedef struct s_nodo
{
    void* info;
    unsigned tam;
    struct s_nodo* sig;
}t_nodo;

#endif // NODO_H_INCLUDED
