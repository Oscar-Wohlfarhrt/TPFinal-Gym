#include <stdio.h>
#include <stdlib.h>
#include "libs/advmenu.h"
#include <signal.h>
#include "libs/tpstructs.h"
//#include "libs/Handlers/actHandler.h"
//#include "libs/interfaces/actInterface.h"
//#include "libs/Handlers/turHandler.h"

/*
//si se busca por mas de una variable
//reemplazar [tipo] por [struct]

[struct] es el tipo del struct (Clientes, Turnos, etc)
[tipo] es un tipo de variable (int, long, etc)

void Load([struct] **list)
void Save([struct] *list)
void Insert([struct] **node, [struct] **list)
int Remove([tipo] value, [struct] **list)
[struct] *Find([tipo] value,[struct] *list)
int Replace([tipo] value,[struct] *new,[struct] **list)
[struct] *GetByIndex(int index,[struct] *list)


*/

char *title="_________  _____      ______  ___  ___ ___    ___    ___\n"
            "|__   __|  |  _ \\     |  __|  | |  |  \\| |   / _ \\   | |\n"
            "   | |     | |_| |    | |_    | |  | \\ \\ |  / /_\\ \\  | |\n"
            "   | |     |  __/     |  _|   | |  | |\\  |  | ___ |  | |__\n"
            "   |_|     |_|        |_|     |_|  |_| \\_|  |_| |_|  |____|\n";

char *menus[]={
    "TP Final\n\n"
    "<o>ABMs</o>\n"
    "<o>Asistencia</o>\n"
    "<o>Cuotas</o>\n"
    "<o>Listas</o>\n|\n"
    "<o>Salir</o>\n",
    "--- ABMs ---\n\n"
    "<o>Clientes</o>\n"
    "<o>Profesores</o>\n"
    "<o>Actividades</o>\n"
    "<o>Turnos</o>\n"
    "<o>Act-Turno</o>\n|\n"
    "<o>Salir</o>\n",
    "--- Listas ---\n\n"
    "<o>Clientes por Sede</o>\n"
    "<o>Clientes por Actividad</o>\n"
    "<o>Clientes por Turno</o>\n|\n"
    "<o>Turnos por Actividad</o>\n"
    "<o>Turnos por Sede</o>\n|\n"
    "<o>Reservas</o>\n|\n"
    "<o>Salir</o>\n",
};

#pragma region SubMenusPrototipes

void ABMs();
void Asistencias();
void Cuotas();
void Listas();

//Funcion para opciones no implementadas
void EmptyFunction();

#pragma endregion

void forcedExit(){
    printf("Salida Forzada");
}

int main(int argc, char **args)
{
    signal(SIGINT,forcedExit);

    setAdvMenus(menus);
    setAdvFormats("| ","\e[48;5;25m|-< ",
               ""," >\e[0m");
    
    void (*mainMenu[])(void)={
        ABMs,
        Asistencias,
        Cuotas,
        Listas,
    };

    advMenu(0,mainMenu,4);

    //printf("%s",title);

    /*Actividades *s=NULL;
    ActiPrintList(&s);
    printf("Trabajo en progreso...\n");
    printf("Primer commit");
    if(s) printf("Tiene algo");
    if(!s) printf("No hay nada");
    while(s){
        printf("%-50s | %-10i\e[K\e[0m\n", s->nombre, s->sucursal);
        s=s->next;
    }*/
    return 0;
}

#pragma region SubMenus

void ABMs(){
    void (*ABMsMenu[])(void)={
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
    };

    advMenu(1,ABMsMenu,5);
}
void Asistencias(){

}
void Cuotas(){

}
void Listas(){
    void (*ListasMenu[])(void)={
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
    };

    advMenu(2,ListasMenu,6);
}
void EmptyFunction(){

}

#pragma endregion