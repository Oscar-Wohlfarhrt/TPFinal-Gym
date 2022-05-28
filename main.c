#include <stdio.h>
#include <stdlib.h>
#include "libs/advmenu.h"
#include <signal.h>
#include "libs/tpstructs.h"

#include "libs/interfaces/interfaces.h"


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
    "\e[1m\e[4m\e[38;5;15mTP Final\e[0m\n\n"
    "<o>ABMs</o>\n"
    "<o>Asistencia</o>\n"
    "<o>Cuotas</o>\n"
    "<o>Reservas</o>\n"
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
    "<o>Salir</o>\n",
};

#pragma region SubMenusPrototipes

void ABMs();
void Listas();

//Funcion para opciones no implementadas
void EmptyFunction(){}

#pragma endregion

#pragma region ArchivosPrototipos

void LoadAllFiles();
void SaveAllFiles();

#pragma endregion

void forcedExit(){
    SaveAllFiles();
    printf("\e[0mSalida Forzada");
}

int main(int argc, char **args)
{
    signal(SIGINT,forcedExit);
    LoadAllFiles();
    getKeyCode(); //debug

    setAdvMenus(menus);
    setAdvFormats("| ","\e[1m\e[38;5;136m|-< ",
               ""," > \e[0m");
    
    void (*mainMenu[])(void)={
        ABMs,
        AsistPrintList,
        PagosPrintList,
        EmptyFunction,
        Listas,
    };

    advMenu(0,mainMenu,5);

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
    SaveAllFiles();

    return 0;
}

#pragma region SubMenus

void ABMs(){
    void (*ABMsMenu[])(void)={
        ClientesPrintList,
        ProfPrintList,
        ActiPrintListVoid,
        TurnsPrintList,
        ActTurnsPrintList,
    };

    advMenu(1,ABMsMenu,5);
}
void Listas(){
    void (*ListasMenu[])(void)={
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
        EmptyFunction,
    };

    advMenu(2,ListasMenu,5);
}

#pragma endregion


#pragma region Archivos

void LoadAllFiles(){
    LoadClientes(&clientes);
    LoadProf(&profes);
    load_actividades(&acti);
    LoadTurnos(&turnos);
    load_ActTurn(&acturn);
    LoadPagos(&pagos);
    LoadAsist(&asist);
}
void SaveAllFiles(){
    SaveClientes(clientes);
    SaveProf(profes);
    save_actividades(acti);
    SaveTurnos(turnos);
    save_ActTurn(acturn);
    SavePagos(pagos);
    SaveAsist(asist);
}

#pragma endregion