#include "funciones.h"

int menu(const char *msj, int li, int ls)
{
    char opc;
    int priVez = 1;
    do{
        printf("%s\n%s", priVez ? priVez = 0, "" : "-----OPCION INVALIDA-----", msj);
        fflush(stdin);
        scanf("%c", &opc);
    }while((opc<li) || (opc>ls));
    return opc;
}

void wrapper_menuInicial()
{
    int estado;
    switch(menu(MSJ_MENU_INICIAL,LI_MENU_INICIAL,LS_MENU_INICIAL))
    {
        case 'A': estado = jugar();
        case 'B': estado = END;
    }
    if(estado == END)
        return;
}
int testVidasYTiempo()
{

char input[TAM_INPUT];
    int index = 0;
    int vidas_restantes = MAX_VIDAS;
    clock_t start = clock(); // Tiempo de inicio
    int continuar = 1; // Variable para controlar el bucle

    printf("Tienes %d vidas y %d segundos para ingresar una secuencia de caracteres:\n", MAX_VIDAS, TIEMPO_LIMITE);

    while (continuar && ((clock() - start) / CLOCKS_PER_SEC) < TIEMPO_LIMITE) {
        if (_kbhit()) { // Verifica si se presionó una tecla
            char c = _getch(); // Lee un carácter sin esperar Enter

            // Detecta si se presionó 'Enter'
            if (c == '\r') { // 'Enter' es representado por '\r'
                continuar = 0; // Cambia la variable para salir del bucle
            }

            // Detecta si se presionó 'Backspace'
            if (c == '\b') {
                if (index > 0) {
                    int vidas_a_usar = 0;
                    printf("\nCuántas vidas quieres usar para borrar? (Te quedan %d vidas): ", vidas_restantes);
                    scanf("%d", &vidas_a_usar);

                    // Validar la cantidad de vidas a usar
                    if (vidas_a_usar > 0 && vidas_a_usar <= vidas_restantes) {
                        vidas_restantes -= vidas_a_usar; // Reduce las vidas

                        // Borrar el número de caracteres según las vidas usadas
                        for (int i = 0; i < vidas_a_usar && index > 0; i++) {
                            index--; // Retrocede el índice para sobreescribir
                            printf("\b \b"); // Borra el último carácter en la pantalla
                        }

                        // Reinicia el temporizador
                        start = clock(); // Reinicia el tiempo
                        printf("\nPuedes seguir escribiendo. Te quedan %d vida(s).\n", vidas_restantes);

                    } else {
                        printf("Cantidad de vidas inválida.\n");
                    }
                } else {
                    printf("\nNo hay caracteres para borrar.\n");
                }
            }
            // Si no es 'Backspace' y hay espacio en el buffer
            else if (index < TAM_INPUT - 1) {
                input[index++] = c;  // Agrega el carácter al arreglo
                printf("%c", c);     // Muestra el carácter ingresado
            }
        }
    }

    input[index] = '\0'; // Termina la cadena de caracteres

    printf("\nTu entrada fue: %s\n", input);
    if (index == 0) {
        printf("No ingresaste ninguna secuencia.\n");
    }

    return 0;
}
int jugar(lista* pl)
{
    return 0;
}


















