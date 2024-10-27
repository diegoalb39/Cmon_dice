#include "desordenar_lista.h"

int main()
{
    t_lista lista_prueba;
    int i, vec_prueba[] = {1, 2, 3, 4, 5, 6, 7};

    crearlista(&lista_prueba);

    for(i = 0;i < ( sizeof(vec_prueba)/sizeof(vec_prueba[i]) );i++)
        ponerenlista_final(&lista_prueba, &vec_prueba[i], sizeof(vec_prueba[i]));

    printf("//lista original//\n");
    recorrerlista(&lista_prueba, mostrar_int);
    printf("\n");

    mezclar_jugadores(&lista_prueba, ( sizeof(vec_prueba)/sizeof(vec_prueba[0]) ));

    printf("\n\n//lista mezclada//\n");
    recorrerlista(&lista_prueba, mostrar_int);
    printf("\n");

    vaciarlista(&lista_prueba);

    return 0;
}
