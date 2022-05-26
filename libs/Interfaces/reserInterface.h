#pragma once
//#include "../tpstructs.h"
#include "../Handlers/reservaHandler.h"
Reservas ReservPrompt(Reservas *res, int *errout);
void ReservPromptRestore(int index, Reservas *res);
void ResevPrintList(Reservas *lista);

void ReservaPrintList(Reservas *lista) //,Clientes *clientes, ActTurno *actT)
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
        Reservas *wait = GetRes(page *entries, lista);
        //Clientes *cli = GetClient(wait->dni, clientes);
        //ActTurno *act = GetActTurno(page *entries, actT);

        printf("\e[48;5;237m");
        printf("Reservas: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-50s \e[K\n", "Index", "DNI", "ACTIVIDAD");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (wait)
            {
                
                // se genera la fecha de nacimiento
                /*char date1[17], date2[17];
                sprintf(date1,"%2i:%02i", turn->horarioInicio.tm_hour, turn->horarioInicio.tm_min);
                sprintf(date2,"%2i:%02i", turn->horarioFin.tm_hour, turn->horarioFin.tm_min);*/
                // se imprime la fila
                printf("%-5i | %-10li | %-50s\e[K\n", index, wait->dni, wait->actividad);
                wait = wait->next;
                //cli = cli->next;
                //act = act->next;
            }
            else // si no existen mas registros
            {
                printf("%-5i\e[K\n\e[K\e[0m\n", index);
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
        op[strlen(op) - 1] = '\0'; // se elimina el salto de linea
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
            Reservas data = ReservPrompt(NULL, &errout);
            if (errout)
            {
                Reservas *newRes = (Reservas *)malloc(sizeof(Reservas));
                *newRes = data;
                insertReservas(&lista,newRes);
            }
        }
        else if (!strncmp(op, "e", 1)) // editar
        {/*
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
            }*/
        }
        else if (!strncmp(op, "x", 1)) // eliminar
        {/*
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            // se intenta convertir el indice a entero
            if (TryToInt32(ind, &editIndex))
            {
                //Turnos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                //if (editTurn = GetTurn(editIndex - 1, turnos))
                
                BorrarTurn(editIndex - 1, &turnos);*/
        }
    }
}
Reservas ReservPrompt(Reservas *res, int *errout)
{
    system(cls);
    int err = 1;
    Reservas reser;
    char op = '\0';
    int index = 0;
    // opciones para el menu
    char *options[] = {
        "DNI",
        "ACTIVIDAD",
    };
    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Reservas:\e[K\n\e[K\n");
    for (int i = 0; i < 2; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        
        if (res)
            ReservPromptRestore(i, res);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (res)
        reser = *res;
    else
        res = &reser;
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
            memcpy(res,&reser,sizeof(Reservas));
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
            input[strlen(input) - 1] = '\0';
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
                        strcpy(res->actividad, input);
                        break;
                    }
                }
            }
            ReservPromptRestore(index, res);
            printf("\e[u\e[0m\e[J");
        }
    }
    return *res;
}
void ReservPromptRestore(int index, Reservas *res)
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
        printf("%li", res->dni);
        break;
    case 1:
        printf("%s", res->actividad);
        break;
    }
}
#pragma endregion