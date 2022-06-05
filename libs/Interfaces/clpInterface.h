#pragma once

#include "../Handlers/clpHandler.h"

// interfaz
ClientesPagos PagosPrompt(ClientesPagos *client, int *errout);
void PagosPromptRestore(int index, ClientesPagos *client);
void PagosPrintList();

ClientesPagos PagosPrompt(ClientesPagos *client, int *errout)
{
    system(cls);
    int err = 1;

    ClientesPagos cli;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "Actividad-Turno",
        "Monto",
        "Emision",
        "Pago",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("ClientesPagos:\e[K\n\e[K\n");
    for (int i = 0; i < 4; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (client)
            PagosPromptRestore(i, client);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (client)
        cli = *client;
    else
        client = &cli;

    printf("\e[u"); // se resetea el cursor
    struct tm tm;
    struct tm tmaux;

    while (err)
    {
        err = 1;
        scanf("%c", &op);          // se lee la opcion
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
        int status = 1;
        if (cli.actturn > sizeIndex(acturn) || cli.actturn < 0)
            status = 0;
        
        tmaux=cli.fechaEmision;
        if (op == 'e' && status && validDate(tmaux))
        {
            err = 0;
            if (errout)
                *errout = 1;
        }
        else if (op == 'c' || (op == 'e' && !validDate(tmaux)))
        {
            if (!validDate(tmaux) && op == 'e')
            {
                SetCurPos(30, 0);
                printf("\a");
                printf("\e[48;5;52m     ERROR! "
                       "Fecha incorrecta      \e[0m\e[u");
                system("pause");
            }
            *client = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (!status && op == 'e')
        {
            SetCurPos(30, 0);
            printf("\a");
            printf("\e[48;5;52m     ERROR! "
                   "1"
                   ". Fuera de rango      \e[0m\e[u");
            system("pause");
            *client = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '4')
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

            if (strcmp(input, "c"))
            {
                if (index == 2 || index == 3)
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
                        TryToInt64(input, &client->actturn);
                        break;
                    case 1:
                        TryToFloat(input, &client->monto);
                        break;
                    case 2:
                        client->fechaEmision = tm;
                        break;
                    case 3:
                        client->fechaPago = tm;
                        break;
                    }
                }
            }
            PagosPromptRestore(index, client);
            printf("\e[u\e[0m\e[J");
        }
    }

    return *client;
}
void PagosPromptRestore(int index, ClientesPagos *client)
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
        printf("%i", client->actturn);
        break;
    case 1:
        printf("$%.02f", client->monto);
        break;
    case 2:
        printf("%02i/%02i/%04i", client->fechaEmision.tm_mday, client->fechaEmision.tm_mon + 1, client->fechaEmision.tm_year + 1900);
        break;
    case 3:
        printf("%02i/%02i/%04i", client->fechaPago.tm_mday, client->fechaPago.tm_mon + 1, client->fechaPago.tm_year + 1900);
        break;
    }
}
void PagosPrintList()
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
        ClientesPagos *client = GetPago(page * entries, pagos);

        /*  "Actividad",
            "Dia",
            "Hora de inicio",
            "hora de fin",
            "DNI Profesor",
            "Cupo Maximo",*/

        printf("\e[48;5;237m");
        printf("Pagos: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-50s | %-20s | %-20s\e[K\n", "Index", "ACT-TURNO", "MONTO", "EMISION");
        printf("%-5s | %-50s | %-20s | %-20s\e[K\n\e[0m", "", "", "RECARGO", "PAGO");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (client)
            {
                // se genera la fecha de nacimiento
                char date1[17], date2[17];
                sprintf(date1, "%02i/%02i/%04i", client->fechaEmision.tm_mday, client->fechaEmision.tm_mon + 1, client->fechaEmision.tm_year + 1900);
                sprintf(date2, "%02i/%02i/%04i", client->fechaPago.tm_mday, client->fechaPago.tm_mon + 1, client->fechaPago.tm_year + 1900);

                float monto = client->monto;
                if (((client->fechaPago.tm_mon >= client->fechaEmision.tm_mon) || (client->fechaPago.tm_year >= client->fechaEmision.tm_year)) && client->fechaPago.tm_mday > 10)
                    monto *= 1.1;

                // se imprime la fila
                printf("%5i | %-50i | $%-19.02f | %-20s\e[K\n", index, client->actturn, monto, date1);
                printf("%5s | %-50s | %-20s | %-20s\e[K\e[0m\n", "", "", monto > client->monto ? "Si" : "No", date2);

                client = client->next;
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
            ClientesPagos data = PagosPrompt(NULL, &errout);
            if (errout)
            {
                ClientesPagos *newTurn = (ClientesPagos *)malloc(sizeof(ClientesPagos));
                *newTurn = data;
                InsertPago(&newTurn, &pagos);
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
                ClientesPagos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                if (editTurn = GetPago(editIndex - 1, pagos))
                    PagosPrompt(editTurn, NULL);
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
                // ClientesPagos *editTurn = NULL;
                //  se verifica que el turno no sea NULL
                // if (editTurn = GetTurn(editIndex - 1, turnos))

                BorrarPago(editIndex - 1, &pagos);
            }
        }
    }
}
