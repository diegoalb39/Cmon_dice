#include "TP.h"

//funcion encargada de manejar el paquete recibido
size_t solicitar_numeros(void*paquete, size_t tamdato, size_t tampaquete, void *contenedor)
{
    size_t tamtotal;//tamtotal del paquete
    char *paq, *p1;

    tamtotal = tamdato * tampaquete;

    //como existe la posibilidad de que la totalidad del contenido sea recibido en varios paquetes,
    //es necesario contemplar esa situacion y, por lo tanto, este bloque de codigo se ocupa de asignar memoria
    //y expandirla, de ser necesario, tal que el contenido pueda ser concatenado. Ademas, tambien asigna el caracter
    //de final de linea para el correcto manejo como string.
    if( tamtotal > 0 )
    {
        if( 0 == ((t_contenedor*)contenedor)->tamcontenido )
        {
            paq = malloc(tamtotal + 1);
            if(!paq)
                return NO_MEMORY;

            memcpy(paq, paquete, tamtotal);

            ((t_contenedor*)contenedor)->tamcontenido = tamtotal;

            p1 = paq;

            *( p1 + (((t_contenedor*)contenedor)->tamcontenido) ) = '\0';
        }
        else
        {
            paq = malloc( tamtotal + (((t_contenedor*)contenedor)->tamcontenido) + 1 );
            if(!paq)
                return NO_MEMORY;

            memcpy( paq, (((t_contenedor*)contenedor)->cadena_datos), ( (((t_contenedor*)contenedor)->tamcontenido) + 1 ) );

            free( ((t_contenedor*)contenedor)->cadena_datos );

            p1 = strrchr(paq, '\0');
            if(!p1)
                return CHAR_NOTFOUND;

            memcpy(p1, paquete, tamtotal);

            ((t_contenedor*)contenedor)->tamcontenido += tamtotal;

            *(p1 + tamtotal) = '\0';
        }

        ((t_contenedor*)contenedor)->cadena_datos = paq;
    }

    return tampaquete;
}

int armado_url(char**URL)
{
    *URL = (char*)malloc( strlen(DATOS_URL_START) + strlen(DATOS_URL_END) + MAX_LINE_CANT_SECUENCIA );
    if(!(*URL))
        return NO_MEMORY;

    strcpy(*URL, DATOS_URL_START);
    strcat(*URL, CANT_SECUENCIA);
    strcat(*URL, DATOS_URL_END);

    return ALL_OK;
}

void config_curl(CURL**curl, char*URL, t_contenedor*contenedor)
{
    //Establecimiento de URL de la solicitud GET
    curl_easy_setopt(*curl, CURLOPT_URL, URL);

    //Determina si se chequea la auntenticidad del certificado mostrado por el servidor demostrando que es quien dice ser
    ////Por default, verifica
    curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, 0L);

    //Establecimiento de funcion encargada de manejar el paquete recibido.
    ////Dicha funcion puede realizar multiples acciones siempre y cuando se mantenga el formato del prototipo
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(*curl, CURLOPT_WRITEFUNCTION, solicitar_numeros);

    //Establecimiento de variable donde se colocaran los datos recibidos en el paquete
    curl_easy_setopt(*curl, CURLOPT_WRITEDATA, contenedor);
}

int obtener_secuencia(CURL**curl, t_contenedor*contenedor)
{
    CURLcode respuesta;//variable que almacena el codigo de retorno de ejecucion de easy_curl_perform
    char *pl, error, clave[] = "Error:";

    do
    {
        error = 'N';//Inicializo la variable que contiene el indicador de error

        //Ejecucion del pedido a la API por medio de la funcion previamente establecida
        respuesta = curl_easy_perform(*curl);

        pl = strstr( (contenedor->cadena_datos), clave );//busco si hubo un mensaje de error en lo recibido

        if(respuesta != CURLE_OK)//chequeo si hubo error durante la ejecucion de curl
        {
            //curl_easy_strerror devuelve un string que describe el codigo de error enviado como parametro
            //stderr es la salida directa a consola
            fprintf(stderr, "//Error en la solicitud: %s//\n", curl_easy_strerror(respuesta));
            error = 'Y';
        }
        else if(pl)
        {
            puts("//Error en servidor.//");
            error = 'Y';
            free(contenedor->cadena_datos);
            contenedor->tamcontenido = 0;
        }

        if('Y' == error)//en caso de error...
            Sleep(1000);//...espero 1s antes de volver a hacer un pedido

    }while('Y' == error);
    ////while: hubo error en respuesta o hubo error por sobrecarga de servidor (string recibido tiene "Error:")

    return ALL_OK;
}

int juego_princicipal()
{
    t_contenedor secuencia;
    CURL*curl;//puntero al handle creado
    char*URL;

    ////Inicializacion de manejo de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_global_init(CURL_GLOBAL_DEFAULT);//prepara el area de trabajo para ejecutar funciones curl
    curl = curl_easy_init();//crea un handle/usuario para la transmision de datos

    if(!curl)
        return ERROR;

    if( !armado_url(&URL) )
        return NO_MEMORY;

    printf("-URL: %s\n\n", URL);//linea de prueba

    config_curl(&curl, URL, &secuencia);

    secuencia.tamcontenido = 0;
    obtener_secuencia(&curl, &secuencia);
    ////en ejecucion tendria esta forma
    //while( haya jugadores que falten jugar )
    //{
    ////secuencia.tamcontenido = 0;

    ////obtener_secuencia(&curl, &secuencia);

    ////funcion de juego

    ////free( secuencia.cadena_datos );
    //}

    ////Cierre de operaciones de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_easy_cleanup(curl);//cierra y libera todo lo asociado al handle previamente creado
    curl_global_cleanup();//libera todos los recursos adquiridos por curl_global_inint

    printf("-Secuencia obtenida:\n%s", secuencia.cadena_datos);//linea de prueba

    free(URL);
    free( secuencia.cadena_datos );

    return 1;
}

/*
int funcion_general(int dificultad)
{
    CURL*curl;//puntero al handle creado
    char  *URL;
    t_contenedor contenedor;

    contenedor.tamcontenido = 0;

    armado_url(&URL, dificultad);
    //printf("%s", URL);

    ////Inicializacion de manejo de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_global_init(CURL_GLOBAL_DEFAULT);//prepara el area de trabajo para ejecutar funciones curl
    curl = curl_easy_init();//crea un handle/usuario para la transmision de datos

    if(!curl)
        return ERROR;

    config_curl(&curl, URL, &contenedor);

    ejecutar_curl(&curl, &contenedor);

    ////Cierre de operaciones de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_easy_cleanup(curl);//cierra y libera todo lo asociado al handle previamente creado
    curl_global_cleanup();//libera todos los recursos adquiridos por curl_global_inint

    free(URL);

    printf("%s\n", contenedor.cadena_datos);

    free(contenedor.cadena_datos);

    return ALL_OK;
}
*/
