#include "TP.h"

////Situacion presentada
//Tras volver a leer el PDF del TP, me di cuenta que el orden en que solicita las acciones a realizar es el
//siguiente: seleccionar JUGAR -> ingresar jugadores -> seleccionar dificultad
//Habiendo determinado que tenemos la posibilidad de limitar el numero de caracteres por secuencia, tome la decision
//de representar dicho limite al determinar una cantidad segun la dificultad, esta ultima siendo evaluada por la funcion
//y concatenando la URL para realizar el pedido a la API.
//Debido al orden en las acciones propuesto por el TP, los pedidos deberian hacerse luego de ingresar la dificultad y, por
//lo tanto, se necesitaria el numero total de jugadores al terminar de ingresarlos. Dicho numero es facil de conseguir y realizar
//esta accion de solicitar las secuencias luego no incide en el numero de instancias en que se hacen los pedidos ya que 'n'
//secuencias pedidas para 'n' jugadores antes van a seguir siendo la misma 'n' si se realizan luego. Ademas, las unicas
//modificaciones significativas que deberian hacerse al estado actual de la funcion es agregar un ciclo while para que
//haga pedidos para esa 'n' cantidad de jugadores y una lista como parametro para guardar las secuencias.
//La unica desventaja es la imposibilidad de no poder guardar tanto al jugador como su correspondiente secuencia en una misma
//instancia al realizar el pedido al mismo tiempo que se ingresa un nombre.
//Dicho esto, esto representa solo una propuesta y la funcion es aun modificable.
int main()
{
    int dificultad;

    dificultad = 1;

    funcion_general(dificultad);

    return 0;
}
