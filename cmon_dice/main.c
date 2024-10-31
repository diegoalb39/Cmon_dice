#include "funciones.h"

int main()
{
    t_lista jugadores;
    t_lista infoRoundsPorJugador;
    t_conf conf;
    int cantJres;
    int puntMax;

    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    if(menuInicial(MSJ_MENU_INICIAL) != SALIR){
        system("cls");
        crearLista(&jugadores);
        crearLista(&infoRoundsPorJugador);
        PlaySoundA("multimedia\\menu.wav",NULL,SND_LOOP | SND_ASYNC);
        cantJres = ingresoJugadores(&jugadores);
        if(cantJres == ERROR_MEM)
        {
            vaciarLista(&jugadores);
            return 1;
        }
        if(leerConf(NOM_ARCH_CONF, &conf)!= TODO_OK)
        {
            vaciarLista(&jugadores);
            return 1;
        }
        desordenarLista(&jugadores, cantJres);
        if(wrapper_mostrarInfoPartida(&jugadores, &conf, &cantJres) != TODO_OK)
        {
            vaciarLista(&jugadores);
            return 1;
        }
        puntMax = jugar(&jugadores, &infoRoundsPorJugador, &conf, cantJres);
        if(puntMax < 0){
            vaciarLista(&jugadores);
            liberarInfoRounds(&infoRoundsPorJugador);
            return puntMax;
        }
        mostrar_y_generar_informe(&jugadores, &infoRoundsPorJugador, &puntMax, accion_mostrar);
        vaciarLista(&jugadores);
        liberarInfoRounds(&infoRoundsPorJugador);
    }

    return 0;
}
