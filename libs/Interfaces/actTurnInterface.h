#pragma once

#include "../Handlers/actturnHandler.h"

// interfaz
ActTurno ActTurnPrompt(ActTurno *ActTurn, int *errout);
void ActTurnPromptRestore(int index, ActTurno *ActTurn);
void ActTurnsPrintList();

ActTurno ActTurnPrompt(ActTurno *ActTurn, int *errout)
{
    system(cls);
    int err = 1;

    ActTurno actt;

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
    printf("ActTurno:\e[K\n\e[K\n");
    for (int i = 0; i < 4; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (ActTurn)
            ActTurnPromptRestore(i, ActTurn);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (ActTurn)
        actt = *ActTurn;
    else
        ActTurn = &actt;

    printf("\e[u"); // se resetea el cursor

    while (err)
    {
        Turnos *turn = GetTurn(ActTurn->turno, turnos);
        int cCount = countCupo(ActTurn->turno, acturn);
        //printf("%i | %i | %p\n",ActTurn->turno,cCount,turn);
        if (turn && cCount >= 0)
        {
            if (turn->cupo > cCount)
            {
                printf("Cupos restantes: %i\n", turn->cupo - cCount);
            }
            else
            {
                printf("No hay cupos, se anadira a lista de espera\n");
            }
        }
        else
        {
            printf("No existe el turno\n");
        }

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
            *ActTurn = actt;
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
                        TryToInt64(input, &ActTurn->dni);
                        break;
                    case 1:
                        TryToInt32(input, &ActTurn->turno);
                        break;
                    }
                }
            }
            ActTurnPromptRestore(index, ActTurn);
            if (index == 0)
            {
                ActTurnPromptRestore(2, ActTurn);
                ActTurnPromptRestore(3, ActTurn);
            }
            printf("\e[u\e[0m\e[J");
        }
    }
    return *ActTurn;
}
void ActTurnPromptRestore(int index, ActTurno *ActTurn)
{
    Clientes *client = FindClient(ActTurn->dni, clientes);
    SetCurPos(30, index + 2);
    if (index % 2)
        printf("\e[48;5;236m");
    else
        printf("\e[48;5;235m");
    printf("\e[K");
    switch (index)
    {
    case 0:
        printf("%ld", ActTurn->dni);
        break;
    case 1:
        printf("%i", ActTurn->turno);
        break;
    case 2:
        printf("%s", client ? client->nombre : "NULL");
        break;
    case 3:
        printf("%s", client ? client->apellido : "NULL");
        break;
    }
}
void ActTurnsPrintList()
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
        ActTurno *ActTurn = get_ActTurn(page * entries, &acturn);
        Clientes *client = NULL;

        printf("\e[48;5;237m");
        printf("ActTurno: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-5s | %-50s | \e[K\n", "Index", "DNI", "TURNO", "NOMBRE");
        printf("%-5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "", "APELLIDO");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (ActTurn)
            {
                client = FindClient(ActTurn->dni, clientes);
                // se imprime la fila
                // printf("%-5s | %-20s | %-5s | %-50s | %-50s  \e[K\e[0m\n", "Index","DNI", "TURNO","NOMBRE", "APELLIDO");
                printf("%5i | %-10li | %-5i | %-50s |\e[K\n", index, ActTurn->dni, ActTurn->turno, client ? client->nombre : "NULL");
                printf("%5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "", client ? client->apellido : "NULL");
                ActTurn = ActTurn->next;
            }
            else // si no existen mas registros
            {
                printf("%5i | %-10s | %-5s | %-50s |\e[K\n", index, "", "", "");
                printf("%5s | %-10s | %-5s | %-50s | \e[K\e[0m\n", "", "", "", "");
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
            ActTurno data = ActTurnPrompt(NULL, &errout);
            if (errout)
            {
                Turnos *turn = GetTurn(data.turno, turnos);
                int cCount = countCupo(data.turno, acturn);
                if (turn && turn->cupo <= cCount)
                {
                    Reservas *newReserva = (Reservas *)malloc(sizeof(Reservas));
                    newReserva->dni = data.dni;
                    newReserva->turno = data.turno;
                    ResEnqueue(&newReserva, &reservaInput, &reservaOutput);
                }
                else
                {
                    ActTurno *newActTurn = (ActTurno *)malloc(sizeof(ActTurno));
                    *newActTurn = data;
                    insert_ActTurno(&newActTurn, &acturn);
                }
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
                ActTurno *editActTurn = NULL;
                if (editActTurn = get_ActTurn(editIndex - 1, &acturn))
                    ActTurnPrompt(editActTurn, NULL);
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
                BorrarActTurn(editIndex - 1, &acturn);
            }
        }
    }
}
#pragma endregion