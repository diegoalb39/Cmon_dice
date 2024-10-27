#include "funciones.h"

int menu(const char *msj, int li, int ls)
{
    char opc;
    int priVez = 1;
    do{
        system("cls");//test
        printf("%s\n%s", priVez ? priVez = 0, "" : "-----OPCION INVALIDA-----", msj);
        fflush(stdin);
        scanf("%c", &opc);
    }while((opc<li) || (opc>ls));
    return opc;
}

void wrapper_menuInicial()
{
    int estado;
    switch(menu(MSJ_MENU_INICIAL,LI_MENU_INICIAL,LS_MENU_INICIAL))
    {
        case 'A': estado = jugar();
        case 'B': estado = END;
    }
    if(estado == END)
        return;
}

int jugar()
{
    t_lista listaJugadores;
    crearlista(&listaJugadores);


    //una vez finalizado el juego, listajugadores debera estar cargada con
    //los datos del juego, informacion de rondas y puntaje total de cada jugador
    //esta funcion muestra los datos de la ronda de cada jugador y lo guarda en un archivo txt,
    //ademas, muestra una lista de ganadores.
    mostrar_y_generar_informe(&listaJugadores, accionCmpYMostrar);

    return 0;
}

void mostrar_y_generar_informe(t_lista* pl, void(*accion)(void* e, void* p, void* pf, void* pc, Cmp cmp))
{
    int puntMax = 0;
    char nombre[TAM_NOMBRE];
    //nombre de archivo de prueba, cambiar a tiempo actual con time.h
    FILE* archInf = fopen("informe.txt", "wt");

    if(!archInf)
        return;

    t_cola colaWin;//ganadores
    crearCola(&colaWin);

    //recorro lista de jugadores, muestro y guardo en arch, tambien cargo lista de ganadores
    recorrerlista_d(pl, accion, cmp_puntaje, &puntMax, archInf, &colaWin);

    printf("\nlos ganadores son: ");
    fprintf(archInf, "ganadores: \n");
    while(!colaVacia(&colaWin))
    {
        sacarDeCola(&colaWin, nombre, TAM_NOMBRE);
        printf("%s ", nombre);
        fprintf(archInf, "%s\n", nombre);
    }
    printf("\npuntaje maximo: %d", puntMax);
    fprintf(archInf, "puntaje maximo de la partida: %d", puntMax);

    fclose(archInf);
}

//e: elemento, p:puntaje max
void accionCmpYMostrar(void* e, void* p, void* pf, void* pc, Cmp cmp)
{
    //
}

int cmp_puntaje(const void* a, const void* b)
{
    return ALL_OK;
}











