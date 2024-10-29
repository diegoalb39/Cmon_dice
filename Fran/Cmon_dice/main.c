#include "funciones.h"

int main()
{
    t_lista jugadores;
    t_lista infoRoundsPorJugador;
    t_conf conf;
    int cantJres;
    int puntMax;

    crearLista(&jugadores);
    crearLista(&infoRoundsPorJugador);
    cantJres = ingresoJugadores(&jugadores);
    if(cantJres == ERROR_MEM)
        return 1;
    if(leerConf(NOM_ARCH_CONF, &conf)!= TODO_OK)
        return 1;
    desordenarLista(&jugadores, cantJres);
    if(wrapper_mostrarInfoPartida(&jugadores, &conf, &cantJres) != TODO_OK)
    {
        vaciarLista(&jugadores);
        return 1;
    }
    puntMax = jugar(&jugadores, &infoRoundsPorJugador, &conf, cantJres);
    system("cls");
    if(puntMax >=0)
        printf("El puntaje maximo fue: %d", puntMax);
    else
    {
        vaciarLista(&jugadores);
        vaciarLista(&infoRoundsPorJugador);
        return puntMax;
    }

    vaciarLista(&jugadores);
    //esto es codigo de prueba sin la funcion de informe, logicamente habria que liberar cada cola en la lista infoRounds
    vaciarLista(&infoRoundsPorJugador);
}
