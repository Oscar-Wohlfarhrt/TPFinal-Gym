#pragma once
//#include "../tpstructs.h"
#include "../Handlers/resHandler.h"

void EsperaPrintList(colaEspera *in,colaEspera *lista);
{
    const int entries = 10; // entradas por pagina

    // variables auxiliares
    int err = 1, page = 0;
    char op[20] = "";

    /*
     * err=0 salir
     * err=1 seguir
     * err=2 no hay mas registros en la lista
     */
    while (err)
    {
        system(cls);
        err = 1;

        // se obtiene el primer turno de la lista
        colaEspera *wait = Get(page * entries, turnos);

        printf("\e[48;5;237m");
        printf("Turnos: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-50s | %-50s | %-20s | %-20s\e[K\n", "Index", "ACTIVIDAD", "PROFESOR", "DIA", "HORA INICIO");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (turn)
            {
                // se genera la fecha de nacimiento
                char date1[17], date2[17];
                sprintf(date1,"%2i:%02i", turn->horarioInicio.tm_hour, turn->horarioInicio.tm_min);
                sprintf(date2,"%2i:%02i", turn->horarioFin.tm_hour, turn->horarioFin.tm_min);

                // se imprime la fila
                printf("%5i | %-50i | %-50i | %-20i | %-20s\e[K\n", index, turn->actividad, turn->prof, turn->dia, date1);
                printf("%5s | %-50s | %-50s | %-20i | %-20s\e[K\e[0m\n", "" , "", "",turn->cupo, date2);

                turn = turn->next;
            }
            else // si no existen mas registros
            {
                printf("%5i\e[K\n\e[K\e[0m\n", index);
                err = 2;
            }
        }

        printf("\e[48;5;237m\e[K\e[0m\n");

        if (page) // formato para el boton de retroceso
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        // boton salir
        printf("<- a\e[0m|\e[48;5;22m salir - s \e[0m|");
        printf("\e[48;5;22m editar - e [index] \e[0m|\e[48;5;22m anadir - w \e[0m|\e[48;5;22m eliminar - x [index] \e[0m|");

        if (err != 2) // formato para el boton de siguiente
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        printf("d ->\e[0m "); // se limpia el formato

        fgets(op, 20, stdin);      // se lee la opcion
        *strchr(op, '\n') = '\0';  // se elimina el salto de linea
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        strlwr(op);
        if (!strncmp(op, "a", 1) && page) // decremento de pagina
            page--;
        else if (!strncmp(op, "d", 1) && err != 2) // incremento de pagina
            page++;
        else if (!strncmp(op, "s", 1)) // salir
            err = 0;
        else if (!strncmp(op, "w", 1)) // anadir
        {
            int errout = 0;
            Turnos data = TurnPrompt(NULL, &errout);
            if (errout)
            {
                Turnos *newTurn = (Turnos *)malloc(sizeof(Turnos));
                *newTurn = data;
                InsertTurn(&newTurn, &turnos);
            }
        }
        else if (!strncmp(op, "e", 1)) // editar
        {
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            // se intenta convertir el indice a entero
            if (TryToInt32(ind, &editIndex))
            {
                Turnos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                if (editTurn = GetTurn(editIndex - 1, turnos))
                    TurnPrompt(editTurn, NULL);
            }
        }
        else if (!strncmp(op, "x", 1)) // eliminar
        {
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            // se intenta convertir el indice a entero
            if (TryToInt32(ind, &editIndex))
            {
                //Turnos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                //if (editTurn = GetTurn(editIndex - 1, turnos))
                
                BorrarTurn(editIndex - 1, &turnos);
            }
        }
    }
}

#pragma endregion