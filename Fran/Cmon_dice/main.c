#include "funciones.h"

int main()
{
    t_lista jugadores;
    t_conf conf;
    int cantJres;

    crearLista(&jugadores);
    cantJres = ingresoJugadores(&jugadores);
    if(cantJres == ERROR_MEM)
        return 1;
    if(leerConf(NOM_ARCH_CONF, &conf)!= TODO_OK)
        return 1;
    desordenarLista(&jugadores, cantJres);
    mostrarInfoPartida(&jugadores, &conf, cantJres);
    printf("\n");
    vaciarLista(&jugadores);
}
