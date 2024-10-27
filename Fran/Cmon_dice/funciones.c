#include "funciones.h"

int cmpNombre(const void *e1, const void *e2)
{
    return strcmpi((char*)e1,(char*)e2);
}

void mostrarJug(const void *e)
{
    printf("%s\n", ((t_jugador*)e)->nombre);
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
    t_jugador jugador;
    char opc, *auxChar;
    int ret;

    do{
        do{
            mostrarJugadores(jugadores);
            printf("Ingrese el nombre del jugador(max. 30 caracteres): ");
            fflush(stdin);
            fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
            auxChar= strchr(jugador.nombre, '\n');
            if(auxChar)
                *auxChar = '\0';

            if(*(jugador.nombre) == '\0')
            {
                printf("Debe ingresar por lo menos un caracter\n");
                system("pause");
                system("cls");
            }
        }while(*(jugador.nombre) == '\0');

        jugador.puntTotal = 0;
        crearCola(&jugador.infoRounds);

        ret= insertarOrdenado(jugadores, &jugador, sizeof(jugador), cmpNombre, 1);

        if(ret == NO_MEM)
            return ERROR_MEM;
        if(ret == DUPLICADO)
        {
            printf("El jugador %s ya habia sido ingresado\n", jugador.nombre);
            system("pause");
        }

        printf("\n");
        system("cls");
        mostrarJugadores(jugadores);
        printf("\u00a8Desea ingresar otro jugador? Y/N\n");
        fflush(stdin);
        scanf("%c", &opc);
        while(opc != 'Y' && opc != 'N' && opc != 'y' && opc != 'n')
        {
            printf("\nOpcion invalida\n\n");
            system("pause");
            system("cls");
            mostrarJugadores(jugadores);
            printf("\u00a8Desea ingresar otro jugador? Y/N\n");
            fflush(stdin);
            scanf("%c", &opc);
        }
        system("cls");
    }while(opc == 'Y' || opc == 'y');

    return TODO_OK;
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
