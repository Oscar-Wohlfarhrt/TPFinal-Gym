#pragma once

#include "../Handlers/asiHandler.h"

// interfaz
Asistencia AsistPrompt(Asistencia *client, int *errout);
void AsistPromptRestore(int index, Asistencia *client);
void AsistPrintList();

Asistencia AsistPrompt(Asistencia *asis, int *errout)
{
    system(cls);
    int err = 1;

    Asistencia cli;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "Actividad-Turno",
        "Dia",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Asistencia:\e[K\n\e[K\n");
    for (int i = 0; i < 2; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (asis)
            AsistPromptRestore(i, asis);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (asis)
        cli = *asis;
    else
        asis = &cli;

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
            *asis = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '2')
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
                if (index == 1)
                {
                    char *day = strtok(input, "/");
                    char *month = strtok(NULL, "/");
                    char *year = strtok(NULL, "/");

                    if (!TryToInt32(day, &tm.tm_mday))
                        err = 2;
                    if (!TryToInt32(month, &tm.tm_mon))
                        err = 2;
                    else
                        tm.tm_mon -= 1;
                    if (!TryToInt32(year, &tm.tm_year))
                        err = 2;
                    else
                        tm.tm_year -= 1900;
                }

                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        TryToInt64(input, &asis->actturn);
                        break;
                    case 1:
                        asis->fecha = tm;
                        break;
                    }
                }
            }
            AsistPromptRestore(index, asis);
            printf("\e[u\e[0m\e[J");
        }
    }

    return *asis;
}
void AsistPromptRestore(int index, Asistencia *asis)
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
        printf("%i", asis->actturn);
        break;
    case 1:
        printf("%02i/%02i/%04i", asis->fecha.tm_mday, asis->fecha.tm_mon + 1, asis->fecha.tm_year + 1900);
        break;
    }
}
void AsistPrintList()
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

        // se obtiene el primer elemento de la lista
        Asistencia *asis = GetAsist(page * entries, asist);

    /*  "Actividad",
        "Dia",
        "Hora de inicio",
        "hora de fin",
        "DNI Profesor",
        "Cupo Maximo",*/

        printf("\e[48;5;237m");
        printf("Asistencias: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-50s | %-20s\e[K\n", "Index", "ACT-TURNO", "FECHA");
        printf("%-5s | %-50s | %-20s\e[K\n\e[0m", "", "", "");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (asis)
            {
                // se genera la fecha de nacimiento
                char date1[17];
sprintf(date1, "%02i/%02i/%04i", asis->fecha.tm_mday, asis->fecha.tm_mon + 1, asis->fecha.tm_year + 1900);
                
                // se imprime la fila
                printf("%5i | %-50i | %-20s\e[K\n", index, asis->actturn, date1);
                printf("%5s | %-50s | %-20s\e[K\e[0m\n", "" , "", "");

                asis = asis->next;
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
            Asistencia data = AsistPrompt(NULL, &errout);
            if (errout)
            {
                Asistencia *newTurn = (Asistencia *)malloc(sizeof(Asistencia));
                *newTurn = data;
                UpdateClientDate(*newTurn,acturn,clientes);
                InsertAsist(&newTurn, &asist);
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
                int errout=0;
                Asistencia *editTurn = NULL;
                // se verifica que el turno no sea NULL
                if (editTurn = GetAsist(editIndex - 1, asist))
                    AsistPrompt(editTurn, &errout);

                if(errout)
                    UpdateClientDate(*editTurn,acturn,clientes);
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
                //Asistencia *editTurn = NULL;
                // se verifica que el turno no sea NULL
                //if (editTurn = GetTurn(editIndex - 1, turnos))
                
                BorrarAsist(editIndex - 1, &asist);
            }
        }
    }
}
