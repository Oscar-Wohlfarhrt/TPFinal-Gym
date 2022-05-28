#pragma once

#include "../Handlers/turHandler.h"

// interfaz
Turnos TurnPrompt(Turnos *client, int *errout);
void TurnPromptRestore(int index, Turnos *client);
void TurnsPrintList();

Turnos TurnPrompt(Turnos *turn, int *errout)
{
    system(cls);
    int err = 1;

    Turnos cli;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "Actividad",
        "Dia",
        "Hora de inicio",
        "hora de fin",
        "DNI Profesor",
        "Cupo Maximo",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Turnos:\e[K\n\e[K\n");
    for (int i = 0; i < 6; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (turn)
            TurnPromptRestore(i, turn);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (turn)
        cli = *turn;
    else
        turn = &cli;

    printf("\e[u"); // se resetea el cursor

    while (err)
    {
        err = 1;
        scanf("%c", &op);          // se lee la opcion
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        if (op == 'e')
        {
            err = 0;
            if (errout)
                *errout = 1;
        }
        else if (op == 'c')
        {
            *turn = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '6')
        {
            index = op - '1';

            SetCurPos(30, index + 2);
            if (index % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");
            printf("\e[K");

            char input[50];
            fgets(input, 50, stdin);
            fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
            *strchr(input, '\n') = '\0';

            struct tm tm;

            if (strcmp(input, "c"))
            {
                if (index == 2 || index == 3)
                {
                    char *hour = strtok(input, ":");
                    char *min = strtok(NULL, ":");

                    if (!TryToInt32(hour, &tm.tm_hour))
                        err = 2;
                    if (!TryToInt32(min, &tm.tm_min))
                        err = 2;
                }

                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        TryToInt64(input, &turn->actividad);
                        break;
                    case 1:
                        TryToInt32(input, &turn->dia);
                        break;
                    case 2:
                        turn->horarioInicio = tm;
                        break;
                    case 3:
                        turn->horarioFin = tm;
                        break;
                    case 4:
                        TryToInt64(input, &turn->prof);
                        break;
                    case 5:
                        TryToInt32(input, &turn->cupo);
                        break;
                    }
                }
            }
            TurnPromptRestore(index, turn);
            printf("\e[u\e[0m\e[J");
        }
    }

    return *turn;
}
void TurnPromptRestore(int index, Turnos *turn)
{
    SetCurPos(30, index + 2);
    if (index % 2)
        printf("\e[48;5;236m");
    else
        printf("\e[48;5;235m");
    printf("\e[K");
    switch (index)
    {
    case 0:
        printf("%i", turn->actividad);
        break;
    case 1:
        printf("%i", turn->dia);
        break;
    case 2:
        printf("%2i:%02i", turn->horarioInicio.tm_hour, turn->horarioInicio.tm_min);
        break;
    case 3:
        printf("%2i:%02i", turn->horarioFin.tm_hour, turn->horarioFin.tm_min);
        break;
    case 4:
        printf("%i", turn->prof);
        break;
    case 5:
        printf("%i", turn->cupo);
        break;
    }
}
void TurnsPrintList()
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
        Turnos *turn = GetTurn(page * entries, turnos);

    /*  "Actividad",
        "Dia",
        "Hora de inicio",
        "hora de fin",
        "DNI Profesor",
        "Cupo Maximo",*/

        printf("\e[48;5;237m");
        printf("Turnos: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-50s | %-50s | %-20s | %-20s\e[K\n", "Index", "ACTIVIDAD", "PROFESOR", "DIA", "HORA INICIO");
        printf("%-5s | %-50s | %-50s | %-20s | %-20s\e[K\n\e[0m", "", "", "", "CUPO", "HORA FIN");
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

                Profesores *prof = FindProf(turn->prof,profes);
                Actividades *act = GetActividad(turn->actividad, acti);
                // se imprime la fila
                printf("%5i | %-50i | %-50i | %-20i | %-20s\e[K\n", index, turn->actividad, turn->prof, turn->dia, date1);
                printf("%5s | %-50s | %-50s | %-20i | %-20s\e[K\e[0m\n", "" , act?act->nombre:"NULL",prof?prof->nombre:"NULL",turn->cupo, date2);

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
