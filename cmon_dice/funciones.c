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

int jugar()
{
    return 0;
}


















