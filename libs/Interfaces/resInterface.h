#pragma once

#include "../Handlers/reservaHandler.h"
#include "../Handlers/cliHandler.h"

// interfaz
Reservas ReservaPrompt(Reservas *ActTurn, int *errout);
void ReservaPromptRestore(int index, Reservas *ActTurn);
void ReservaPrintList();

Reservas ReservaPrompt(Reservas *res, int *errout)
{
    system(cls);
    int err = 1;

    Reservas actt;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "DNI",
        "TURNO",
        "NOMBRE",
        "APELLIDO",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Reservas:\e[K\n\e[K\n");
    for (int i = 0; i < 4; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (res)
            ReservaPromptRestore(i, res);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (res)
        actt = *res;
    else
        res = &actt;

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
            *res = actt;
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

            if (strcmp(input, "c"))
            {
                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        TryToInt64(input, &res->dni);
                        break;
                    case 1:
                        TryToInt32(input, &res->turno);
                        break;
                    }
                }
            }
            ReservaPromptRestore(index, res);
            if (index == 0)
            {
                ReservaPromptRestore(2, res);
                ReservaPromptRestore(3, res);
            }
            printf("\e[u\e[0m\e[J");
        }
    }
    return *res;
}
void ReservaPromptRestore(int index, Reservas *res)
{
    Clientes *client = FindClient(res->dni, clientes);
    SetCurPos(30, index + 2);
    if (index % 2)
        printf("\e[48;5;236m");
    else
        printf("\e[48;5;235m");
    printf("\e[K");
    switch (index)
    {
    case 0:
        printf("%ld", res->dni);
        break;
    case 1:
        printf("%i", res->turno);
        break;
    case 2:
        printf("%s", client ? client->nombre : "NULL");
        break;
    case 3:
        printf("%s", client ? client->apellido : "NULL");
        break;
    }
}
void ReservaPrintList()
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
        Reservas *res = GetRes(page * entries, reservaOutput);
        Clientes *client = NULL;

        printf("\e[48;5;237m");
        printf("Reservas: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-5s | %-50s | \e[K\n", "Index", "DNI", "TURNO", "NOMBRE");
        printf("%-5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "", "APELLIDO");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (res)
            {
                client = FindClient(res->dni, clientes);
                // se imprime la fila
                // printf("%-5s | %-20s | %-5s | %-50s | %-50s  \e[K\e[0m\n", "Index","DNI", "TURNO","NOMBRE", "APELLIDO");
                printf("%5i | %-10li | %-5i | %-50s |\e[K\n", index, res->dni, res->turno, client ? client->nombre : "NULL");
                printf("%5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "", client ? client->apellido : "NULL");
                res = res->next;
            }
            else // si no existen mas registros
            {
                printf("%5i | %-10s | %-5s | %-50s |\e[K\n", index, "", "", "");
                printf("%5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "","");
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
            Reservas data = ReservaPrompt(NULL, &errout);
            if (errout)
            {
                Reservas *newRes = (Reservas *)malloc(sizeof(Reservas));
                *newRes = data;
                ResEnqueue(&newRes, &reservaInput,&reservaOutput);
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
                Reservas *editActTurn = NULL;
                if (editActTurn = GetRes(editIndex - 1, reservaOutput))
                    ReservaPrompt(editActTurn, NULL);
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
                ResRemove(editIndex - 1, &reservaInput , &reservaOutput);
            }
        }
    }
}
#pragma endregion