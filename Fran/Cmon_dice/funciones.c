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

void mostrarConf(t_conf conf)
{
    printf("Nivel de dificultad: %c\n"
           "Tiempo que se mostrara la secuencia: %d segundos\n"
           "Tiempo maximo de respuesta: %d segundos\n"
           "Cantidad de vidas disponibles: %d",
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
                printf("Debe ingresar por lo menos un caracter\n");
                system("pause");
                system("cls");
            }
        }while(*(jugador) == '\0');

        cant++;

        ret= insertarOrdenado(jugadores, &jugador, sizeof(jugador), cmpNombre, 1); //PARA NO DUPLICADOS

        if(ret == NO_MEM)
            return ERROR_MEM;
        if(ret == DUPLICADO)
        {
            printf("El jugador %s ya habia sido ingresado\n", jugador);
            system("pause");
        }

        printf("\n");
        system("cls");
        mostrarJugadores(jugadores);
        printf("\u00a8Desea ingresar otro jugador? Y/N\n");
        fflush(stdin);
        scanf("%c", &opc);
        opc = toupper(opc);
        while(opc != 'Y' && opc != 'N')
        {
            printf("\nOpcion invalida\n\n");
            system("pause");
            system("cls");
            mostrarJugadores(jugadores);
            printf("\u00a8Desea ingresar otro jugador? [Y/N]\n");
            fflush(stdin);
            scanf("%c", &opc);
        }
        system("cls");
    }while(opc == 'Y');

    return cant;
}

int leerConf(const char* archConf, t_conf* varConf)
{
    char *auxChar, cad[11];
    t_conf auxConf;
    FILE* pf= fopen(archConf, "rt");
    if(!pf)
        return ERROR_ARCH;

    do{
        printf("DIFICULTAD DE LA PARTIDA\n"
               "F - Facil\n"
               "M - Medio\n"
               "D - Dificil\n"
               "Ingrese el nivel de dificultad deseado: ");
        fflush(stdin);
        scanf("%c", &varConf->nivel);
        varConf->nivel = toupper(varConf->nivel);
        if(varConf->nivel != 'F' && varConf->nivel != 'M' && varConf->nivel != 'D')
        {
            printf("\n\nLa opcion elegida no es valida");
            system("pause");
            system("cls");
        }
    }while(varConf->nivel != 'F' && varConf->nivel != 'M' && varConf->nivel != 'D');

    system("cls");
    while(fgets(cad, sizeof(cad), pf))
    {
        auxChar= strchr(cad, '\n');
        if(auxChar)
            *auxChar= '\0';

        if(CAMPOS_ARCH_CONF !=
           sscanf(cad, "%c|%d|%d|%d", &auxConf.nivel, &auxConf.cantTiempoSec, &auxConf.cantTiempoResp, &auxConf.cantVidas))
        {
            fclose(pf);
            printf("Error en la lectura del arch de configuracion: formato invalido");
            return ERROR_ARCH;
        }

        if(!esNivelValido(auxConf.nivel) || auxConf.cantTiempoSec>20 || auxConf.cantTiempoResp>20 || auxConf.cantVidas>5)
        {
            fclose(pf);
            printf("Error en la lectura del arch de configuracion: formato invalido");
            return ERROR_ARCH;
        }

        if(auxConf.nivel == varConf->nivel)
            *varConf = auxConf;
    }

    fclose(pf);
    return TODO_OK;
}

char mostrarInfoPartida(t_lista* jugadores, t_conf* conf)
{
    char resp;

    do{
        mostrarJugadores(jugadores);
        printf("Se jugara segun el orden de la lista de jugadores\n");
        printf("\nLa configuracion seleccionada para la partida fue la siguiente:\n\n");
        mostrarConf(*conf);
        printf("Teclas para jugar:\n\n"
               "A - AZUL\n"
               "V - VERDE\n"
               "R - ROJO\n"
               "N - NARANJA\n"
               "U - USAR VIDAS");
        printf("\n\n\u00a8Esta listo para comenzar la partida? [Y/N]\n");
        fflush(stdin);
        scanf("%c", &resp);
        resp = toupper(resp);
        if(resp != 'Y' && resp != 'N')
        {
            printf("\nOpcion invalida\n\n");
            system("pause");
            system("cls");
        }
    }while(resp != 'Y' && resp != 'N');

    return resp;
}

int wrapper_mostrarInfoPartida(t_lista* jugadores, t_conf* conf, int cantJres)
{
    int opc, cantAdc;
    char resp;

    resp = mostrarInfoPartida(jugadores, conf);

    while(resp == 'N')
    {
        system("cls");
        do{
            printf("\u00a8Que accion desea realizar antes de comenzar?\n\n"
                   "1 - Agregar jugadores\n"
                   "2 - Cambiar la dificultad\n"
                   "3 - Comenzar\n"
                   "4 - Salir\n\n");
            fflush(stdin);
            scanf("%d", &opc);
            if(opc<1 || opc>4)
            {
                printf("\nOpcion invalida\n\n");
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
                    cantJres+= cantAdc;
                    desordenarLista(jugadores, cantJres);
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
        printf("Se acabo el tiempo. Presione ENTER para continuar...");
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
        i++;
        Sleep(1000);
    }

    Sleep((cantTiempoSec-1)*1000);
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
        system("pause");
        perdio = 1;
        return 0;
    }

    do{
        printf("Ronda %d\n\n"
               "Respuesta actual: %s\n\n"
               "\r\u00a8Cuantas vidas desea utilizar? Vidas disponibles: %d\n", ronda, respuesta, *pVidas);
        fflush(stdin);
        scanf("%d", &vidasUsadas);
        if(vidasUsadas > *pVidas || vidasUsadas<=0)
        {
            printf("\b\033[A");
            printf("\033[2K");
            printf("La cantidad de vidas solicitada no es valida\n");
            system("pause");
            system("cls");
        }
    }while(vidasUsadas > *pVidas || vidasUsadas<0);

    system("cls");
    largoResp = strlen(respuesta);
    if(vidasUsadas > largoResp)
    {
        *(respuesta) = '\0';
        printf("La cantidad de vidas utilizadas excede la cantidad de colores ingresados. Se mostrara la secuencia nuevamente...");
        vidasUsadas = largoResp+1;
        Sleep(3000);
        system("cls");
        printf("Ronda %d\n\n", ronda);
        mostrarSecuencia(secuencia, cantTiempoSec);
    }
    else
    {
        *(respuesta + (largoResp - vidasUsadas)) = '\0';
    }

    if(largoResp < ronda)
        printf("Ronda %d\n\n"
                "Ingrese su respuesta(una letra a la vez)\n\n\n", ronda, respuesta);

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
    printf("Ingrese su respuesta(una letra a la vez)\n\n\n");

    numLetra= strlen(infoRound->respuesta);
    while(tiempoResp>0 && numLetra != ronda && !perdio)
    {
        printf("\033[A\rRespuesta: %s", infoRound->respuesta);
        fflush(stdin);
        scanf("%c", &auxChar);
        auxChar = toupper(auxChar);
        if(auxChar == 'A' || auxChar == 'R' || auxChar == 'V' || auxChar == 'N')
        {
            *(infoRound->respuesta+numLetra) = auxChar;
            numLetra++;
            *(infoRound->respuesta+numLetra) = '\0';
        }

        if(auxChar == 'U')
        {
            *(infoRound->respuesta+numLetra+1) = '\0';
            infoRound->vidasUsadas += usarVidas(vidas, infoRound->secuencia, infoRound->respuesta, conf->cantTiempoSec, ronda);
            numLetra = strlen(infoRound->respuesta);
            if(_beginthread(timerResp, 0, &argTimer) == -1)
                return ERROR_THREAD;
        }
    }

    continuarTimer = 0;
    if(numLetra == ronda)
    {
        *(infoRound->respuesta+numLetra) = '\0';
        return RESP_COMPLETA;
    }
    else
    {
        *(infoRound->respuesta+numLetra+1) = '\0';
        return RESP_NO_COMP;
    }
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
            infoRound.vidasUsadas = 0;

            guardarSecuencia(&infoRound, &secuencia, ronda);
            system("cls");
            printf("Ronda %d\n\n", ronda);
            mostrarSecuencia(infoRound.secuencia, conf->cantTiempoSec);
            do{
                printf("Ronda %d\n\n", ronda);
                *(infoRound.respuesta) = '\0';
                estado= recibirRespuesta(&infoRound, conf, ronda, &vidas);

                if(estado == ERROR_THREAD)
                {
                    curl_easy_cleanup(curl);
                    curl_global_cleanup();
                    free(URL);
                    free(secuencia.cadena_datos);
                    return ERROR_THREAD;
                }

                if(estado == RESP_COMPLETA)
                {
                    if(strcmp(infoRound.respuesta, infoRound.secuencia) != 0)
                    {
                        estado = RESP_INCORRECTA;
                        printf("\n\nLa respuesta es incorrecta\n\n");
                        system("pause");
                        infoRound.vidasUsadas += usarVidas(&vidas, infoRound.secuencia, infoRound.respuesta, conf->cantTiempoSec, ronda);
                    }
                }
                else
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
                {
                    system("cls");
                    printf("Felicidades, ha completado todas las rondas."); //esto lo puse porque despues habria que ver si expandir o no la secuencia
                }

                ronda++;
            }
            else
                infoRound.punt = 0;

        }while(!perdio && ronda != secuencia.tamcontenido*0.5);

        if(puntJugador > puntMax)
            puntMax = puntJugador;

        insertarAlFinal(infoRoundsPorJugador, &infoRoundsJugador, sizeof(t_cola));
        leerElemento(&itJugadores, &jugador, sizeof(jugador));
    }
//FIN
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    free(URL);
    free(secuencia.cadena_datos);

    return puntMax;
}
