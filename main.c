#include <stdio.h>
#include <stdlib.h>
#include "libs/tpstructs.h"

int main(int argc, char **args)
{
<<<<<<< Updated upstream
=======

    signal(SIGINT, forcedExit);
    LoadAllFiles();

    getKeyCode(); // debug

    // actualiza la fecha de baja de los clientes de ser necesario
    UpdateClientBaja(clientes);

    setAdvMenus(menus);
    setAdvFormats("| ", "\e[1m\e[38;5;136m|-< ",
                  "", " > \e[0m");

    void (*mainMenu[])(void) = {
        ABMs,
        AsistPrintList,
        PagosPrintList,
        ReservaPrintList,
        Listas,
    };

    advMenu(0, mainMenu, 5);

    // printf("%s",title);

    /*Actividades *s=NULL;
    ActiPrintList(&s);
>>>>>>> Stashed changes
    printf("Trabajo en progreso...\n");
    printf("Primer commit");
    return 0;
}
<<<<<<< Updated upstream
=======

#pragma region SubMenus

void ABMs()
{
    void (*ABMsMenu[])(void) = {
        ClientesPrintList,
        ProfPrintList,
        ActiPrintListVoid,
        TurnsPrintList,
        ActTurnsPrintList,
    };

    advMenu(1, ABMsMenu, 5);
}
void Listas()
{
    void (*ListasMenu[])(void) = {
        SedePrintList,
        EmptyFunction,
        TurnPrintList,
        EmptyFunction,
        EmptyFunction,
        deudoresPrintList,
    };

    advMenu(2, ListasMenu, 6);
}

#pragma endregion

#pragma region Archivos

void LoadAllFiles()
{
    LoadClientes(&clientes);
    LoadProf(&profes);
    load_actividades(&acti);
    LoadTurnos(&turnos);
    load_ActTurn(&acturn);
    LoadPagos(&pagos);
    LoadAsist(&asist);
    load_Reservas(&reservaInput,&reservaOutput);
}
void SaveAllFiles()
{
    SaveClientes(clientes);
    SaveProf(profes);
    save_actividades(acti);
    SaveTurnos(turnos);
    save_ActTurn(acturn);
    SavePagos(pagos);
    SaveAsist(asist);
    save_espera(&reservaInput,&reservaOutput);
}

#pragma endregion
>>>>>>> Stashed changes
