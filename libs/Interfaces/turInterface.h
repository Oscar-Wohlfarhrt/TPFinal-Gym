#pragma once

#include "../Handlers/turHandler.h"

// interfaz
Turnos TurnPrompt(Turnos *client, int *errout);
void TurnPromptRestore(int index, Turnos *client);
void TurnsPrintList();

Turnos TurnPrompt(Turnos *client, int *errout)
{
    system(cls);
    int err = 1;

    Turnos cli;

    if (client)
        cli = *client;

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
        if (client)
            TurnPromptRestore(i, client);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (!client)
        client = &cli;

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
            *client = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '7')
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
                if (index > 3)
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
                        TryToInt64(input, &client->dni);
                        break;
                    case 1:
                        strcpy(client->nombre, input);
                        break;
                    case 2:
                        strcpy(client->apellido, input);
                        break;
                    case 3:
                        strcpy(client->telefono, input);
                        break;
                    case 4:
                        client->fechaNacimiento = tm;
                        break;
                    case 5:
                        client->ultimaActividad = tm;
                        break;
                    case 6:
                        client->fechaBaja = tm;
                    }
                }
            }
            TurnPromptRestore(index, client);
            printf("\e[u\e[J\e[0m");
        }
    }

    return *client;
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
        printf("%s", turn->nombre);
        break;
    case 2:
        printf("%s", turn->apellido);
        break;
    case 3:
        printf("%s", turn->telefono);
        break;
    case 4:
        printf("%02i/%02i/%04i", turn->fechaNacimiento.tm_mday, turn->fechaNacimiento.tm_mon + 1, turn->fechaNacimiento.tm_year + 1900);
        break;
    case 5:
        printf("%02i/%02i/%04i", turn->ultimaActividad.tm_mday, turn->ultimaActividad.tm_mon + 1, turn->ultimaActividad.tm_year + 1900);
        break;
    case 6:
        printf("%02i/%02i/%04i", turn->fechaBaja.tm_mday, turn->fechaBaja.tm_mon + 1, turn->fechaBaja.tm_year + 1900);
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

        // se obtiene el primer cliente de la lista
        Turnos *cli = GetClient(page * entries, clientes);

        printf("\e[48;5;237m");
        printf("Turnos: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-50s | %-20s | %-20s\e[K\n", "Index", "DNI", "NOMBRE", "TELEFONO", "ULTIMA ACTIVIDAD");
        printf("%-5s | %-10s | %-50s | %-20s | %-20s\e[K\n\e[0m", "", "", "APELLIDO", "FECHA NACIMIENTO", "FECHA DE BAJA");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (cli)
            {
                // se genera la fecha de nacimiento
                char date1[17], date2[17], date3[17];
                sprintf(date1, "%02i/%02i/%04i", cli->fechaNacimiento.tm_mday, cli->fechaNacimiento.tm_mon + 1, cli->fechaNacimiento.tm_year + 1900);
                sprintf(date2, "%02i/%02i/%04i", cli->ultimaActividad.tm_mday, cli->ultimaActividad.tm_mon + 1, cli->ultimaActividad.tm_year + 1900);
                sprintf(date3, "%02i/%02i/%04i", cli->fechaBaja.tm_mday, cli->fechaBaja.tm_mon + 1, cli->fechaBaja.tm_year + 1900);

                // se imprime la fila
                printf("%5i | %-10i | %-50s | %-20s | %-20s\e[K\n", index, cli->dni, cli->nombre, cli->telefono, date2);
                printf("%5s | %-10s | %-50s | %-20s | %-20s\e[K\e[0m\n", "", "", cli->apellido, date1, date3);

                cli = cli->next;
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
                Turnos *newCli = (Turnos *)malloc(sizeof(Turnos));
                *newCli = data;
                InsertClient(&newCli, &clientes);
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
                Turnos *editCli = NULL;
                // se verifica que el cliente no sea NULL
                if (editCli = GetClient(editIndex - 1, clientes))
                    TurnPrompt(editCli, NULL);
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
                Turnos *editCli = NULL;
                // se verifica que el cliente no sea NULL
                if (editCli = GetClient(editIndex - 1, clientes))
                    BorrarCliente(*editCli, &clientes);
            }
        }
    }
}
