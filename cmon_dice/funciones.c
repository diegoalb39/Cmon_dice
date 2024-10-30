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
        //case 'A': estado = jugar();
        case 'A': estado = iniciar_juego();//test
        case 'B': estado = END;
    }
    if(estado == END)
        return;
}

int iniciar_juego()
{
    t_lista listaJugadores;
    t_lista listaRondas;
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
        ponerenlista_final(&listaJugadores, &jugadores[i], TAM_NOMBRE);

    char* cad1 = malloc(TAM_SECUENCIA);
    char* cad2 = malloc(TAM_SECUENCIA);
    char* cad3 = malloc(TAM_SECUENCIA);
    char* cad4 = malloc(TAM_SECUENCIA);
    char* cad5 = malloc(TAM_SECUENCIA);
    char* cad6 = malloc(TAM_SECUENCIA);
    char* cad7 = malloc(TAM_SECUENCIA);
    char* cad8 = malloc(TAM_SECUENCIA);
    char* cad9 = malloc(TAM_SECUENCIA);
    char* cad10 = malloc(TAM_SECUENCIA);
    char* cad11 = malloc(TAM_SECUENCIA);
    char* cad12 = malloc(TAM_SECUENCIA);
    char* cad13 = malloc(TAM_SECUENCIA);
    char* cad14 = malloc(TAM_SECUENCIA);
    char* cad15 = malloc(TAM_SECUENCIA);
    char* cad16 = malloc(TAM_SECUENCIA);

    strcpy(cad1, "Q");
    strcpy(cad2, "QW");
    strcpy(cad3, "QWE");
    strcpy(cad4, "QWER");
    strcpy(cad5, "R");
    strcpy(cad6, "RE");
    strcpy(cad7, "REW");
    strcpy(cad8, "REWQ");
    strcpy(cad9, "Q");
    strcpy(cad10, "Q");
    strcpy(cad11, "QW");
    strcpy(cad12, "QE");
    strcpy(cad13, "QWE");
    strcpy(cad14, "QRE");
    strcpy(cad15, "QTW");
    strcpy(cad16, "QQQQ");


    t_round datosJ1[] = {
        {cad1, cad9, 2, 0},
        {cad2, cad10, 2, 0},
        {cad3, cad11, 2, 50},
        {cad4, cad12, 2, 0}
    };

    for(int j=0; j<4; j++)
        ponerEnCola(&colaJ1, &datosJ1[j], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ1, sizeof(colaJ1));

    t_round datosJ2[] = {
        {cad5, cad13, 2, 1},
        {cad6, cad14, 2, 1},
        {cad7, cad15, 2, 5},
        {cad8, cad16, 2, 1}
    };
    for(int k=0; k<4; k++)
        ponerEnCola(&colaJ2, &datosJ2[k], sizeof(t_round));

    ponerenlista_final(&listaRondas, &colaJ2, sizeof(colaJ2));

    /*****************************************************************************/

    puntajeMax = jugar();

    /*
    luego de terminado el juego:
    -listaJugadores tiene los nombres de los jugadores
    -listaRondas tiene variables tipo cola por cada jugador,
    dentro de cada cola, tengo el puntaje por ronda.
    -las colas se vacian dentro de la funcion mostrar_y_generar_informe
    -iniciar_juego devuelve el puntaje maximo entre los jugadores.
    */
    mostrar_y_generar_informe(&listaJugadores, &listaRondas, &puntajeMax, accion_mostrar);

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
    fprintf(archInf, "************RESUMEN DE LA PARTIDA***********\n");
    printf("*******MEJOR PUNTAJE DE LA PARTIDA: %d*******\n***********GANADORES DE LA PARTIDA***********\n", *puntMax);
    recorrer_listas_iguales_paralelo(jug, rondas, accion_mostrar, puntMax, archInf);
    printf("****************FIN DEL JUEGO****************");
    printf("\n\nSe ha generado un informe de la partida en el archivo: '%s'\n", nom);
    fprintf(archInf, "**************FIN DEL INFORME**************");
    vaciarlista(jug);
    vaciarlista(rondas);

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
        fprintf(arch, "******************ROUND %d*******************\nSecuencia: %s\nRespuesta: %s\nVidas usadas: %d\nPuntos obtenidos: %d\n",
                round, ronda.secuencia, ronda.respuesta, ronda.vidas_usadas, ronda.puntos);
        round++;
        total+=ronda.puntos;
        free(ronda.secuencia);
        free(ronda.respuesta);
    }
    if(*(int*)p == total)
    {
        printf("%s\n", nom);
        fprintf(arch, "\nEl jugador %s gano la partida!", nom);
    }
    fprintf(arch, "\nPuntos totales obtenidos por %s: %d\n\n\n", nom, total);
}


int jugar()
{
    int num = 50;
    return num;
}








