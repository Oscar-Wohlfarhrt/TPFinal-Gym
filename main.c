#include <stdio.h>
#include <stdlib.h>
#include "libs/tpstructs.h"
#include "libs/Handlers/actHandler.h"
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

int main(int argc, char **args)
{
    Actividades *e=NULL, *s=NULL;
    ActiPrintList(e,s);
    printf("Trabajo en progreso...\n");
    printf("Primer commit");
    return 0;
}
