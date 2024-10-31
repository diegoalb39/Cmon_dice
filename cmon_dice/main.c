#include "funciones.h"

int main()
{
    t_lista jugadores;
    t_lista infoRoundsPorJugador;
    t_conf conf;
    int cantJres;
    int puntMax;
    int ret;

    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    if(menuInicial(MSJ_MENU_INICIAL) != SALIR){
        system("cls");
        crearLista(&jugadores);
        crearLista(&infoRoundsPorJugador);
        PlaySoundA("multimedia\\menu.wav",NULL,SND_LOOP | SND_ASYNC);
        cantJres = ingresoJugadores(&jugadores);
        if(cantJres != TODO_OK)
        {
            mostrarError(cantJres);
            vaciarLista(&jugadores);
            return 1;
            return cantJres;
        }

        ret = leerConf(NOM_ARCH_CONF, &conf);
        if(ret != TODO_OK)
        {
            mostrarError(ret);
            vaciarLista(&jugadores);
            return 1;
            return ret;
        }
        desordenarLista(&jugadores, cantJres);
        ret = wrapper_mostrarInfoPartida(&jugadores, &conf, &cantJres);
        if(ret != TODO_OK)
        {
            mostrarError(ret);
            vaciarLista(&jugadores);
            return 1;
            return ret;
        }

        puntMax = jugar(&jugadores, &infoRoundsPorJugador, &conf, cantJres);
        if(puntMax < 0){
            mostrarError(puntMax);
            vaciarLista(&jugadores);
            liberarInfoRounds(&infoRoundsPorJugador);
            return puntMax;
        }

        ret = mostrar_y_generar_informe(&jugadores, &infoRoundsPorJugador, &puntMax, accion_mostrar);
        if(ret != TODO_OK)
        {
            mostrarError(ret);
            vaciarLista(&jugadores);
            liberarInfoRounds(&infoRoundsPorJugador);
            return ret;
        }

        vaciarLista(&jugadores);
        liberarInfoRounds(&infoRoundsPorJugador);
    }
    return 0;
}
