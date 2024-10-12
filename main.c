#include "TP.h"

////RECOMENDACION: Leer el "manual" dado por la API para mayor comprension de la manera en que se realizan los pedidos
///////////////////y el retorno que se hace (link al final del PDF del TP)

//size_t nombre_de_funcion(puntero a paquete enviado desde api, tamaño default de un elemento, tamaño del paquete recibido, variable de guardado)
//size_t WriteCallback(void*, size_t, size_t, void*);
//el size_t retornado es el tamaño total del paquete recibido

size_t solicitar_numeros(void*, size_t, size_t, void*);

//Las funciones se desarrollaron simplemente en main pero seran ajustadas segun sea necesario bajo el diseño del
//resto del programa.
int main()
{
    t_contenedor contenedor;
    char error, *pl, clave[] = "Error:";

    contenedor.tamcontenido = 0;

    CURL*curl;//puntero al handle creado
    CURLcode respuesta;//variable que almacena el codigo de retorno de ejecucion de easy_curl_perform

    //Inicializacion de manejo de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_global_init(CURL_GLOBAL_DEFAULT);//prepara el area de trabajo para ejecutar funciones curl
    curl = curl_easy_init();//crea un handle/usuario para la transmision de datos

    //Si dicho handle se pudo crear...
    if(curl)
    {
        //Establecimiento de URL de la solicitud GET
        curl_easy_setopt(curl, CURLOPT_URL, datos_URL);

        //Determina si se chequea la auntenticidad del certificado mostrado por el servidor demostrando que es quien dice ser
        ////Por default, verifica
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        //Establecimiento de funcion encargada de manejar el paquete recibido.
        ////Dicha funcion puede realizar multiples acciones siempre y cuando se mantenga el formato del prototipo
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, solicitar_numeros);

        //Establecimiento de variable donde se colocaran los datos recibidos en el paquete
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contenedor);

        do
        {
            error = 'N';//Inicializo la variable que contiene el indicador de error

            //Ejecucion del pedido a la API por medio de la funcion previamente establecida
            respuesta = curl_easy_perform(curl);

            pl = strstr((contenedor.cadena_datos), clave);//busco si hubo un mensaje de error en lo recibido

            if(respuesta != CURLE_OK)//chequeo si hubo error durante la ejecucion de curl
            {
                //curl_easy_strerror devuelve un string que describe el codigo de error enviado como parametro
                //stderr es la salida directa a consola
                fprintf(stderr, "//Error en la solicitud: %s//\n", curl_easy_strerror(respuesta));
                error = 'Y';
            }
            else if(pl)
            {
                printf("//Error en servidor.//\n");
                error = 'Y';
            }

            if('Y' == error)//en caso de error...
                Sleep(1000);//...espero 1s antes de volver a hacer un pedido

        }while('Y' == error);
        ////while: hubo error en respuesta o hubo error por sobrecarga de servidor (string recibido tiene "Error:")
    }

    //Cierre de operaciones de curl//Dependiendo el diseño del resto del programa, esto podria terminar afuera.
    curl_easy_cleanup(curl);//cierra y libera todo lo asociado al handle previamente creado
    curl_global_cleanup();//libera todos los recursos adquiridos por curl_global_inint

    printf("%s\n", contenedor.cadena_datos);
    printf("-tam del contenido: %d\n", contenedor.tamcontenido);

    return 0;
}

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


////IGNORAR - solo funciones de ejemplo - funciones de base////
/*
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;

    printf("%.*s", (int)realsize, (char*)contents);

    printf("\n--FIN TANDA.--\n");

    return realsize;
}
*/

////funciones curl////

//{
/*//funcion de solicitud de datos
size_t guardar_datos(void*contenido, size_t tamestandar, size_t tamdatosrec, void*contenedor)
{
    size_t tampaquete;
    char *paq, *p1;

    tampaquete = tamestandar * tamdatosrec;

    if(tampaquete > 0)
    {
        if(!(((tcontenedor*)contenedor)->tam))
        {
            paq = malloc(tampaquete + 1);
            if(!paq)
                return NO_MEMORY;

            memcpy(paq, contenido, tampaquete);

            ((tcontenedor*)contenedor)->tam = tampaquete + 1;

            p1 = paq;

            *(p1 + ((tcontenedor*)contenedor)->tam) = '\0';
        }
        else
        {
            paq = malloc(tampaquete + ((tcontenedor*)contenedor)->tam);
            if(!paq)
                return NO_MEMORY;

            memcpy(paq, ((tcontenedor*)contenedor)->cadena_datos, ((tcontenedor*)contenedor)->tam);

            free(((tcontenedor*)contenedor)->cadena_datos);

            p1 = strrchr(paq, '\0');
            if(!p1)
                return CHAR_NOTFOUND;

            memcpy(p1, contenido, tampaquete);

            ((tcontenedor*)contenedor)->tam += tampaquete;

            *(p1 + tampaquete) = '\0';
        }

        ((tcontenedor*)contenedor)->cadena_datos = paq;
    }

    return tampaquete;
}
*/
//}

/*//funcion de configuracion
int datos_pedir(tcontenedor*contenedor)
{
    CURL*curl;
    CURLcode respuesta;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(!curl)
        return 0;

    ((tcontenedor*)contenedor)->tam = 0;

    curl_easy_setopt(curl, CURLOPT_URL, datos_URL);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, guardar_datos);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, contenedor);

    respuesta = curl_easy_perform(curl);

    if(respuesta != CURLE_OK)
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(respuesta));

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return OK;
}
*/
