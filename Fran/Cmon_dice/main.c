#include "funciones.h"

int main()
{
    t_lista jugadores;
    t_conf conf;

    crearLista(&jugadores);
    if(ingresoJugadores(&jugadores)!= TODO_OK)
        return 1;
    if(leerConf(NOM_ARCH_CONF, &conf)!= TODO_OK)
        return 1;
    mostrarJugadores(&jugadores); //ESTAS LINEAS SON DE PRUEBA
    mostrarConf(conf);
    printf("\n");
    vaciarLista(&jugadores);
}
