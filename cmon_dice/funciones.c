#include "funciones.h"

int continuarTimer;
int tiempoResp;
int perdio;

int cmpNombre(const void *e1, const void *e2)
{
    return strcmpi((char*)e1,(char*)e2);
}

void mostrarJug(const void *e)
{
    printf("%s\n", ((char*)e));
}

int menuInicial(const char *msj)
{
    char opc;
    int priVez = 1;
    do{
        system("cls");
        printf("%s\n%s", priVez ? priVez = 0, "" : "-----OPCION INVALIDA-----", msj);
        fflush(stdin);
        scanf("%c", &opc);
        opc = toupper(opc);
    }while((opc<'A') || (opc>'B'));
    if(opc == 'B')
        return SALIR;
    return opc;
}

void mostrarConf(t_conf conf)
{
    printf("Nivel de dificultad: %c\n"
           "Tiempo que se mostrara la secuencia: %d segundos\n"
           "Tiempo maximo de respuesta: %d segundos\n"
           "Cantidad de vidas disponibles: %d\n",
           conf.nivel, conf.cantTiempoSec, conf.cantTiempoResp, conf.cantVidas);
}
void mostrarJugadores(t_lista* jugadores)
{
    printf("=================="
           "LISTA DE JUGADORES"
           "==================\n\n");

    recorrerLista(jugadores, mostrarJug);
    printf("\n");
}

int ingresoJugadores(t_lista* jugadores)
{
    char jugador[MAX_NOM];
    char opc, *auxChar;
    int cant=0, ret;

    do{
        do{
            mostrarJugadores(jugadores);
            printf("Ingrese el nombre del jugador(max. 30 caracteres): ");
            fflush(stdin);
            fgets(jugador, sizeof(jugador), stdin);
            auxChar= strchr(jugador, '\n');
            if(auxChar)
                *auxChar = '\0';

            if(*(jugador) == '\0')
            {
                printf("Debe ingresar por lo menos un caracter\n\n");
                system("pause");
                system("cls");
            }
        }while(*(jugador) == '\0');

        ret= insertarOrdenado(jugadores, &jugador, sizeof(jugador), cmpNombre, 1); //PARA NO DUPLICADOS

        if(ret == NO_MEM)
            return ERROR_MEM;
        if(ret == DUPLICADO)
        {
            printf("El jugador %s ya había sido ingresado\n\n", jugador);
            system("pause");
        }
        else
            cant++;

        do{
            system("cls");
            mostrarJugadores(jugadores);
            printf("¿Desea ingresar otro jugador? [Y/N]\n");
            fflush(stdin);
            scanf("%c", &opc);
            opc = toupper(opc);
            if(opc != 'Y' && opc != 'N')
            {
                printf("\nOpción inválida\n\n");
                system("pause");
            }
        }while(opc != 'Y' && opc != 'N');
        system("cls");

    }while(opc == 'Y');

    return cant;
}

int leerConf(const char* archConf, t_conf* varConf)
{
    char *auxChar, cad[11];
    int cantRegistros = 0;
    t_conf auxConf;
    FILE* pf= fopen(archConf, "rt");
    if(!pf)
        return ERROR_ARCH;

    do{
        printf("DIFICULTAD DE LA PARTIDA\n"
               "F - Facil\n"
               "M - Medio\n"
               "D - Dificil\n\n"
               "Ingrese el nivel de dificultad deseado: ");
        fflush(stdin);
        scanf("%c", &varConf->nivel);
        varConf->nivel = toupper(varConf->nivel);
        if(varConf->nivel != 'F' && varConf->nivel != 'M' && varConf->nivel != 'D')
        {
            printf("\n\nLa opción elegida no es valida");
            system("pause");
            system("cls");
        }
    }while(varConf->nivel != 'F' && varConf->nivel != 'M' && varConf->nivel != 'D');

    system("cls");
    while(fgets(cad, sizeof(cad), pf))
    {
        cantRegistros++;
        auxChar= strchr(cad, '\n');
        if(auxChar)
            *auxChar= '\0';

        if(CAMPOS_ARCH_CONF !=
           sscanf(cad, "%c|%d|%d|%d", &auxConf.nivel, &auxConf.cantTiempoSec, &auxConf.cantTiempoResp, &auxConf.cantVidas))
        {
            fclose(pf);
            return ERROR_ARCH_FORMAT;
        }

        if(!esNivelValido(auxConf.nivel) || !enRango(auxConf.cantTiempoSec,1,20) || !enRango(auxConf.cantTiempoResp,1,20) || !enRango(auxConf.cantVidas,0,5))
        {
            fclose(pf);
            return ERROR_ARCH_FORMAT;
        }

        if(auxConf.nivel == varConf->nivel)
            *varConf = auxConf;
    }

    fclose(pf);
    if(cantRegistros != CANT_DIFS)
    {
        printf("Error en la lectura del archivo de configuración: formato invalido");
        return ERROR_ARCH;
    }
    else
        return TODO_OK;
}

char mostrarInfoPartida(t_lista* jugadores, t_conf* conf)
{
    char resp;

    do{
        mostrarJugadores(jugadores);
        printf("Se jugará según el orden de la lista de jugadores\n");
        printf("\nLa configuración seleccionada para la partida fue la siguiente:\n\n");
        mostrarConf(*conf);
        printf("\n\nTeclas para jugar:\n\n"
               "A - AZUL\n"
               "V - VERDE\n"
               "R - ROJO\n"
               "N - NARANJA\n"
               "U - USAR VIDAS");
        printf("\n\n¿Está listo para comenzar la partida? [Y/N]\n");
        fflush(stdin);
        scanf("%c", &resp);
        resp = toupper(resp);
        if(resp != 'Y' && resp != 'N')
        {
            printf("\nOpción inválida\n\n");
            system("pause");
            system("cls");
        }
    }while(resp != 'Y' && resp != 'N');

    return resp;
}

int wrapper_mostrarInfoPartida(t_lista* jugadores, t_conf* conf, int *cantJres)
{
    int opc, cantAdc;
    char resp;

    resp = mostrarInfoPartida(jugadores, conf);

    while(resp == 'N')
    {
        system("cls");
        do{
            printf("¿Que acción desea realizar antes de comenzar?\n\n"
                   "1 - Agregar jugadores\n"
                   "2 - Cambiar la dificultad\n"
                   "3 - Comenzar\n"
                   "4 - Salir\n\n");
            fflush(stdin);
            scanf("%d", &opc);
            if(opc<1 || opc>4)
            {
                printf("\nOpción inválida\n\n");
                system("pause");
                system("cls");
            }
        }while(opc<1 || opc>4);

        system("cls");
        switch(opc)
        {
            case 1: cantAdc = ingresoJugadores(jugadores);
                    if(cantAdc == ERROR_MEM)
                        return ERROR_MEM;
                    *cantJres+= cantAdc;
                    desordenarLista(jugadores, *cantJres);
                    break;
            case 2: if(leerConf(NOM_ARCH_CONF, conf) != TODO_OK)
                        return ERROR_ARCH;
                    break;
            case 3: return TODO_OK;
                    break;
            case 4: return SALIR;
        }

        system("cls");
        resp = mostrarInfoPartida(jugadores, conf);
    }

    return TODO_OK;
}

void timerResp(void* arg)
{
    tiempoResp = *(int*)arg;

    while(tiempoResp > 0 && continuarTimer)
    {
        Sleep(1000);
        tiempoResp--;
    }

    if(tiempoResp==0 && continuarTimer)
    {
        system("cls");
        printf("Se acabó el tiempo. Presione ENTER para continuar...\n");
    }
}

void guardarSecuencia(t_round* infoRound, t_contenedor* secuencia, int ronda)
{
    char colores[]= {'A','V','R','N'};
    int numLetra, pos;

    for(numLetra=0; numLetra<ronda; numLetra++)
    {
        pos = *(secuencia->cadena_datos+(numLetra*2)) - '0';
        *(infoRound->secuencia+numLetra) = colores[pos-1];
    }

    *(infoRound->secuencia+numLetra) = '\0';
}

void mostrarSecuencia(char const* secuencia, int cantTiempoSec)
{
    int i=0;

    printf("Secuencia: ");
    while(*(secuencia+i) != '\0')
    {
        printf("%c", *(secuencia+i));
        cambiarColorFondo(*(secuencia+i));
        i++;
        Sleep(1000);
    }

    Sleep((cantTiempoSec-1)*1000);
    system("color 07");
    system("cls");
}

int usarVidas(int* pVidas, char* secuencia, char* respuesta, int cantTiempoSec, int ronda)
{
    int vidasUsadas, largoResp;

    continuarTimer = 0;
    system("cls");
    if(*pVidas == 0)
    {
        printf("No tiene mas vidas para utilizar\n\n");
        PlaySoundA("multimedia\\game_over.wav",NULL,SND_ASYNC);
        system("pause");
        perdio = 1;
        return 0;
    }

    largoResp = strlen(respuesta);
    do{
        printf("Ronda %d\n\n"
                "Respuesta actual: %s\n\n"
                "¿Cuantas vidas desea utilizar? Vidas disponibles: %d\n\n"
                "\rPuede utilizar %d vidas para volver a mostrar la secuencia.\n\n", ronda, respuesta, *pVidas, largoResp + 1);

        fflush(stdin);
        scanf("%d", &vidasUsadas);
        if(vidasUsadas > *pVidas || vidasUsadas> largoResp + 1 || vidasUsadas<=0)
        {
            printf("\b\033[1A");
            printf("\033[2K");
            printf("La cantidad de vidas solicitada no es válida\n\n");
            system("pause");
            system("cls");
        }
    }while(vidasUsadas > *pVidas || vidasUsadas> largoResp + 1 || vidasUsadas<=0);

    system("cls");
    if(vidasUsadas == largoResp + 1)
    {
        *(respuesta) = '\0';
        system("cls");
        printf("Ronda %d\n\n", ronda);
        mostrarSecuencia(secuencia, cantTiempoSec);
    }
    else
    {
        *(respuesta + (largoResp - vidasUsadas)) = '\0';
    }

    *pVidas -= vidasUsadas;
    continuarTimer = 1;
    return vidasUsadas;
}

int recibirRespuesta(t_round* infoRound, t_conf* conf, int ronda, int* vidas)
{
    int numLetra, argTimer;
    char auxChar;

    continuarTimer = 1;
    argTimer= conf->cantTiempoResp + (ronda-1);
    if(_beginthread(timerResp, 0, &argTimer) == -1)
        return ERROR_THREAD;

    Sleep(100); //espera un instante a que se inicialice el timer
    numLetra= strlen(infoRound->respuesta);

    while(tiempoResp>0 && numLetra != ronda && !perdio)
    {
        system("cls");
        printf("Ronda %d\n\n"
                "Ingrese su respuesta (una letra a la vez)\n\n"
                "Respuesta: %s", ronda, infoRound->respuesta);
        fflush(stdin);
        scanf("%c", &auxChar);
        auxChar = toupper(auxChar);
        if(tiempoResp>0)
        {
            if(auxChar == 'A' || auxChar == 'R' || auxChar == 'V' || auxChar == 'N')
            {
                *(infoRound->respuesta+numLetra) = auxChar;
                numLetra++;
                *(infoRound->respuesta+numLetra) = '\0';
            }

            if(auxChar == 'U')
            {
                *(infoRound->respuesta+numLetra) = '\0';
                infoRound->vidasUsadas += usarVidas(vidas, infoRound->secuencia, infoRound->respuesta, conf->cantTiempoSec, ronda);
                numLetra = strlen(infoRound->respuesta);
                if(_beginthread(timerResp, 0, &argTimer) == -1)
                    return ERROR_THREAD;
            }
        }
    }

    continuarTimer = 0;
    if(numLetra == ronda)
        return RESP_COMPLETA;
    else
        return RESP_NO_COMP;
}

int extenderSecuencia(t_round* infoRound, t_contenedor* secuencia, CURL** curl)
{
    int nueTam;
    char* temp;

    obtener_secuencia(curl, secuencia);
    nueTam = secuencia->tamcontenido*0.5;

    temp = (char*)realloc(infoRound->secuencia, nueTam + 1);
    if(!temp)
        return ERROR_MEM;
    infoRound->secuencia = temp;

    temp = (char*)realloc(infoRound->respuesta, nueTam + 1);
    if(!temp)
    {
        free(infoRound->secuencia);
        return ERROR_MEM;
    }
    infoRound->respuesta = temp;

    return TODO_OK;
}

void limpiezaCurl(CURL** curl, char *URL, char *cadena_datos)
{
    curl_easy_cleanup(*curl);
    curl_global_cleanup();
    free(URL);
    free(cadena_datos);
}

int jugar(t_lista* jugadores, t_lista* infoRoundsPorJugador, t_conf* conf, int cantJres)
{
    int vidas, ronda, estado, puntMax=0, puntJugador, i;
    char jugador[MAX_NOM];
    t_round infoRound;
    t_cola infoRoundsJugador;
    t_lista_it itJugadores;
    t_contenedor secuencia;
    CURL *curl;
    char *URL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(!curl)
        return ERROR_CURL;

    if(!armado_url(&URL))
        return ERROR_MEM;

    config_curl(&curl, URL, &secuencia);

    crearIterador(&itJugadores);
    inicializarIterador(&itJugadores, jugadores);
//INICIO
    for(i= 1; i<= cantJres; i++)
    {
        leerElemento(&itJugadores, jugador, sizeof(jugador));
        vidas = conf->cantVidas;
        ronda = 1;
        puntJugador = 0;
        perdio= 0;
        crearCola(&infoRoundsJugador);
        secuencia.tamcontenido = 0;
        obtener_secuencia(&curl, &secuencia);
        system("cls");
        printf("Turno del jugador %s", jugador);
        Sleep(2000);

        do{
            PlaySoundA("multimedia\\gameplay.wav",NULL,SND_LOOP | SND_ASYNC);
            infoRound.vidasUsadas = 0;
            infoRound.secuencia = (char*)malloc(TAM_SEC_INI + 1);
            if(!infoRound.secuencia || (infoRound.respuesta = (char*)malloc(TAM_SEC_INI + 1)) == NULL)
            {
                free(infoRound.secuencia);
                limpiezaCurl(&curl, URL, secuencia.cadena_datos);
                return ERROR_MEM;
            }

            *(infoRound.respuesta) = '\0';
            guardarSecuencia(&infoRound, &secuencia, ronda);
            system("cls");
            printf("Ronda %d\n\n", ronda);
            mostrarSecuencia(infoRound.secuencia, conf->cantTiempoSec);
            do{
                estado= recibirRespuesta(&infoRound, conf, ronda, &vidas);

                if(estado == ERROR_THREAD)
                {
                    limpiezaCurl(&curl, URL, secuencia.cadena_datos);
                    return ERROR_THREAD;
                }

                if(estado == RESP_COMPLETA)
                {
                    if(strcmp(infoRound.respuesta, infoRound.secuencia) != 0)
                    {
                        estado = RESP_INCORRECTA;
                        printf("\nLa respuesta es incorrecta\n\n");
                        system("pause");
                        infoRound.vidasUsadas += usarVidas(&vidas, infoRound.secuencia, infoRound.respuesta, conf->cantTiempoSec, ronda);
                    }
                }
                else if(!perdio)
                    infoRound.vidasUsadas += usarVidas(&vidas, infoRound.secuencia, infoRound.respuesta, conf->cantTiempoSec, ronda);

            }while((estado == RESP_INCORRECTA || estado == RESP_NO_COMP) && !perdio);

            if(!perdio)
            {
                if(infoRound.vidasUsadas != 0)
                    infoRound.punt = 1;
                else
                    infoRound.punt = 3;

                puntJugador += infoRound.punt;

                ponerEnCola(&infoRoundsJugador, &infoRound, sizeof(t_round));

                if(ronda == secuencia.tamcontenido*0.5)
                    if(extenderSecuencia(&infoRound, &secuencia, &curl) != TODO_OK)
                    {
                        limpiezaCurl(&curl, URL, secuencia.cadena_datos);
                        return ERROR_MEM;
                    }

                ronda++;
                PlaySoundA(NULL, 0, 0);
                PlaySoundA("multimedia\\next_round.wav",NULL,SND_ASYNC);
                Sleep(500); //para que se escuche el next_round.wav
            }
            else
                infoRound.punt = 0;

        }while(!perdio);

        if(puntJugador > puntMax)
            puntMax = puntJugador;

        insertarAlFinal(infoRoundsPorJugador, &infoRoundsJugador, sizeof(t_cola));
        leerElemento(&itJugadores, &jugador, sizeof(jugador));
    }
//FIN
    limpiezaCurl(&curl, URL, secuencia.cadena_datos);

    return puntMax;
}

void liberarInfoRounds(t_lista* infoRoundsPorJugador)
{
    t_cola infoRoundsJugador;
    t_round auxRound;

    while(sacarPrimeroDeLista(infoRoundsPorJugador, &infoRoundsJugador, sizeof(t_cola)) != LISTA_VACIA)
    {
        while(sacarDeCola(&infoRoundsJugador, &auxRound, sizeof(t_round)) != COLA_VACIA)
        {
            free(auxRound.secuencia);
            free(auxRound.respuesta);
        }
    }
}

int mostrar_y_generar_informe(t_lista* jug, t_lista* rondas, int* puntMax,
                               void(*accion)(void* dato1, void* dato2, void* p, void* pf, void* pc))
{
    //genero nombre de archivo con fecha y hora actuales
    char fecha[70];
    char ruta[MAX_NOM]="reportes\\";
    char nom[MAX_NOM]="informe-juego_";
    time_t tiempoAct = time(NULL);
    struct tm tLocal = *localtime(&tiempoAct);
    strftime(fecha, sizeof(fecha), "%Y-%m-%d_%H-%M", &tLocal);
    strcat(nom, fecha);
    strcat(nom, ".txt");
    strcat(ruta, nom);

    char buffer[MAX_NOM];
    t_cola colaGanadores;
    crearCola(&colaGanadores);

    FILE* archInf = fopen(ruta, "wt");
    if(!archInf)
        return ERROR_ARCH;
    fprintf(archInf, "************RESUMEN DE LA PARTIDA***********\n");
    printf("*******MEJOR PUNTAJE DE LA PARTIDA: %d*******\n***********GANADORES DE LA PARTIDA***********\n", *puntMax);
    recorrer_listas_iguales_paralelo(jug, rondas, accion_mostrar, puntMax, archInf, &colaGanadores);
    printf("****************FIN DEL JUEGO****************");
    printf("\n\nSe ha generado un informe de la partida en el archivo: '%s'\n", nom);

    fprintf(archInf, "*********GANADORES DE LA PARTIDA***********\n");
    while(!colaVacia(&colaGanadores))
    {
        sacarDeCola(&colaGanadores, buffer, MAX_NOM);
        fprintf(archInf, "%s\n", buffer);
    }
    fprintf(archInf, "**************FIN DEL INFORME**************");

    vaciarCola(&colaGanadores);
    fclose(archInf);

    return TODO_OK;
}

//p: puntaje max, pf: ptr file
//dato1 : nombre de lista de nombres, dato2: cola de la lista de colas
void accion_mostrar(void* dato1, void* dato2, void* p, void* pf, void* pc)
{
    char nom[MAX_NOM];
    int round=1;
    int total=0;
    t_round ronda;
    t_cola colaRounds = *(t_cola*)dato2;
    FILE* arch = (FILE*)pf;

    memcpy(nom, dato1, MAX_NOM);
    fprintf(arch, "Nombre de jugador: %s\n", nom);

    while(!colaVacia(&colaRounds))
    {
        sacarDeCola(&colaRounds, &ronda, sizeof(t_round));
        fprintf(arch, "******************ROUND %d*******************\nSecuencia: %s\nRespuesta: %s\nVidas usadas: %d\nPuntos obtenidos: %d\n",
                round, ronda.secuencia, ronda.respuesta, ronda.vidasUsadas, ronda.punt);
        round++;
        total+=ronda.punt;
        free(ronda.secuencia);
        free(ronda.respuesta);
    }
    if(*(int*)p == total && total>0)
    {
        printf("%s\n", nom);
        ponerEnCola((t_cola*)pc, nom, MAX_NOM);
    }

    fprintf(arch, "\nPuntos totales obtenidos por %s: %d\n\n\n", nom, total);
}

void mostrarError(int cod)
{
    system("cls");
    printf("Error: ");
    switch(cod)
    {
        case -1: printf("Error al abrir un archivo\n");break;
        case -2: printf("Se agotó la memoria\n");break;
        case -3: printf("No se pudo configurar la API\n");break;
        case -4: printf("Error al inicializar el temporizador\n");
        case -5: printf("Error en la lectura del archivo de configuración: formato invalido\n");
    }
}

