#include "../listaDinamica/lista.h"//cola en lista circular
#include "funciones.h"

#include "TP.h"//curl
#include "desordenar_lista.h"//funciones de lista


int main()
{
    //prueba de funciones de tp.h
    if ( !juego_princicipal() )
        puts("////error durante juego////");

    //prueba desordenar lista
    /*
    int i, cant;

    cant = 7;

    srand(time(NULL));

    for(i = 0;i < cant;i++)
        printf("%d ", (rand()%2));

    printf("\n");
    */

    t_lista lista_prueba;
    int i, vec_prueba[] = {1, 2, 3, 4, 5, 6, 7};

    crearlista(&lista_prueba);

    for(i = 0;i < ( sizeof(vec_prueba)/sizeof(vec_prueba[i]) );i++)
        ponerenlista_final(&lista_prueba, &vec_prueba[i], sizeof(vec_prueba[i]));

    printf("//lista original//\n");
    recorrerlista(&lista_prueba, mostrar_int);
    printf("\n");

    desordenarlista(&lista_prueba, ( sizeof(vec_prueba)/sizeof(vec_prueba[0]) ));

    printf("\n\n//lista a//\n");
    recorrerlista(&lista_prueba, mostrar_int);
    printf("\n");

    vaciarlista(&lista_prueba);

    return 0;
}
