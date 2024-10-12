#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <curl/curl.h>

//la composicion de la URL determina las caracteristicas del pedido (solo para este caso donde la API interactua de esta manera)
#define datos_URL "https://www.random.org/integers/?num=4&min=1&max=4&col=1&base=10&format=plain&rnd=new"
//num = cantidad de enteros solicitados
//min = menor entero posible
//max = mayor entero posible
//col = cantidad de columnas en que se van a ordenar los numeros
//base = base en que se presentan los numeros
//format = formato del documento en el que se entregan los datos
//rnd = determina la forma de randomizar los elementos

#define NO_MEMORY 0
#define CHAR_NOTFOUND 0

typedef struct
{
    char*cadena_datos;
    unsigned tamcontenido;

}t_contenedor;

#endif // TP_H_INCLUDED
