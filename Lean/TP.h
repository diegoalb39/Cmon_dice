#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED

#include <curl/curl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//la composicion de la URL determina las caracteristicas del pedido (solo para este caso donde la API interactua de esta manera)
//formato de la URL "https://www.random.org/integers/?num=4&min=1&max=4&col=1&base=10&format=plain&rnd=new"
//num = cantidad de enteros solicitados
//min = menor entero posible
//max = mayor entero posible
//col = cantidad de columnas en que se van a ordenar los numeros
//base = base en que se presentan los numeros
//format = formato del documento en el que se entregan los datos
//rnd = determina la forma de randomizar los elementos

//Constantes que determinan el inicio y final de la URL donde se ignora la cantidad de numeros con tal de concatenar luego
#define DATOS_URL_START "https://www.random.org/integers/?num="
#define DATOS_URL_END "&min=1&max=4&col=1&base=10&format=plain&rnd=new"

////Constantes que determinan elementos del juego
//MAX_LINE_CANT_SECUENCIA determina el largo a agregar a la cadena de la URL para contener las lineas mas abajo
#define MAX_LINE_CANT_SECUENCIA 2
//Constantes que determinan una linea describiendo la cantidad de numeros a pedir a la API segun la dificultad y que seran
//concatenadas para conformar la URL
#define CANT_SECUENCIA_FACIL "4"
#define CANT_SECUENCIA_NORMAL "6"
#define CANT_SECUENCIA_DIFICIL "8"

//Constantes generales
#define NO_MEMORY 0
#define CHAR_NOTFOUND 0
#define ALL_OK 1
#define ERROR 0

typedef struct
{
    char*cadena_datos;
    unsigned tamcontenido;

}t_contenedor;

//RECOMENDACION: Leer el "manual" dado por la API para mayor comprension de la manera en que se realizan los pedidos
///////////////////y el retorno que se hace (link al final del PDF del TP)

//size_t nombre_de_funcion(puntero a paquete enviado desde api, tamaño default de un elemento, tamaño del paquete recibido, variable de guardado)
//size_t WriteCallback(void*, size_t, size_t, void*);
//el size_t retornado es el tamaño total del paquete recibido

size_t solicitar_numeros(void*, size_t, size_t, void*);

int armado_url(char**, int);
int config_curl(CURL**, char*, t_contenedor*);
int ejecutar_curl(CURL**, t_contenedor*);
int funcion_general(int);

#endif // TP_H_INCLUDED
