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
    t_lista listaRondas;//lista con ptr a cola
    int puntajeMax;

    crearlista(&listaJugadores);
    crearlista(&listaRondas);

    /*****************************************************************************/
    /*********LOTE DE PRUEBA PARA PROBAR FUNCION mostrar_y_generar_informe()******/
    t_cola colaJ1, colaJ2, colaJ3, colaJ4;
    crearCola(&colaJ1);
    crearCola(&colaJ2);
    crearCola(&colaJ3);
    crearCola(&colaJ4);

    t_jugador jugadores[]={ {"jugador1"},
                            {"jugador2"},
                            {"jugador3"},
                            {"jugador4"}};
    for(int i = 0; i<sizeof(jugadores)/sizeof(t_jugador); i++)
        ponerenlista_final(&listaJugadores, &jugadores[i], TAM_NOMBRE);//puede fallar el tam

    t_round datosJ1[] = {
        {"Q", "E", 2, 0},
        {"QW", "EF", 2, 0},
        {"QWE", "QWE", 2, 50},
        {"QWER", "REWQ", 2, 0}
    };

    for(int j=0; j<4; j++)
        ponerEnCola(&colaJ1, &datosJ1[j], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ1, sizeof(colaJ1));///!!!!!!!!!!!

    t_round datosJ2[] = {
        {"R", "R", 2, 1},
        {"RE", "RQ", 2, 1},
        {"REQ", "REQ", 2, 5},
        {"REQW", "RECQ", 2, 1}
    };
    for(int k=0; k<4; k++)
        ponerEnCola(&colaJ2, &datosJ2[k], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ2, sizeof(colaJ2));///!!!!!!!!!!!

    t_round datosJ3[] = {
        {"A", "S", 2, 2},
        {"AS", "SA", 2, 1},
        {"ASD", "DSA", 2, 5},
        {"ASDF", "FDSA", 2, 1}
    };
    for(int m=0; m<4; m++)
        ponerEnCola(&colaJ3, &datosJ3[m], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ3, sizeof(colaJ3));///!!!!!!!!!!!

    t_round datosJ4[] = {
        {"B", "D", 2, 0},
        {"BO", "AA", 2, 0},
        {"BOC", "DD", 2, 0},
        {"BOCA", "BOCA", 2, 50}
    };
    for(int n=0; n<4; n++)
        ponerEnCola(&colaJ4, &datosJ4[n], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ4, sizeof(colaJ4));///!!!!!!!!!!!

    /*****************************************************************************/

    puntajeMax = iniciar_juego();

    /*
    luego de terminado el juego:
    -listaJugadores tiene los nombres de los jugadores
    -listaRondas tiene variables tipo cola por cada jugador,
    dentro de cada cola, tengo el puntaje por ronda.
    -las colas se vacian dentro de la funcion mostrar_y_generar_informe
    -iniciar_juego devuelve el puntaje maximo entre los jugadores.
    */
    mostrar_y_generar_informe(&listaJugadores, &listaRondas, &puntajeMax, accion_mostrar);

    vaciarlista(&listaJugadores);
    vaciarlista(&listaRondas);

    return 0;
}

void mostrar_y_generar_informe(t_lista* jug, t_lista* rondas, int* puntMax,
                               void(*accion)(void* dato1, void* dato2, void* p, void* pf))
{
    //genero nombre de archivo con fecha y hora actuales
    char fecha[70];
    char nom[]="informe-juego_";
    time_t tiempoAct = time(NULL);
    struct tm tLocal = *localtime(&tiempoAct);
    strftime(fecha, sizeof(fecha), "%Y-%m-%d_%H-%M", &tLocal);
    strcat(nom, fecha);
    strcat(nom, ".txt");

    FILE* archInf = fopen(nom, "wt");
    if(!archInf)
        return;

    printf("Mejor Puntaje de la partida: %d \nGanador/es de la partida: ", *puntMax);
    recorrer_listas_iguales_paralelo(jug, rondas, accion_mostrar, puntMax, archInf);

    fclose(archInf);
}

//p: puntaje max, pf: ptr file
//dato1 : nombre de lista de nombres, dato2: cola de la lista de colas
void accion_mostrar(void* dato1, void* dato2, void* p, void* pf)
{
    char nom[TAM_NOMBRE];
    int round=1;
    int total=0;

    t_round ronda;
    t_cola colaRounds = *(t_cola*)dato2;
    FILE* arch = (FILE*)pf;

    memcpy(nom, dato1, TAM_NOMBRE);
    fprintf(arch, "Nombre de jugador: %s\n", nom);

    while(!colaVacia(&colaRounds))
    {
        sacarDeCola(&colaRounds, &ronda, sizeof(t_round));
        fprintf(arch, "Round: %d\nSecuencia: %s\nRespuesta: %s\nVidas usadas: %d\nPuntos obtenidos: %d\n",
                round, ronda.secuencia, ronda.respuesta, ronda.vidas_usadas, ronda.puntos);
        round++;
        total+=ronda.puntos;
    }
    if(*(int*)p == total)
    {
        printf("%s ", nom);
        fprintf(arch, "\nEl jugador %s gano la partida!", nom);
    }
    fprintf(arch, "\nPuntos totales obtenidos por %s: %d\n\n\n", nom, total);
}


int iniciar_juego()
{
    int num = 50;
    return num;
}








