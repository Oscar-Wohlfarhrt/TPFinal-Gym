#pragma once
//#include "../tpstructs.h"
#include "../Handlers/reservaHandler.h"
void ResevPrintList();

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
        Reservas *wait = GetRes(page * entries, reservaOutput);
        // Clientes *cli = GetClient(wait->dni, clientes);
        // ActTurno *act = GetActTurno(page *entries, actT);

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
                printf("%-5i | %-10li | %-10i\e[K\n", index, wait->dni, wait->turno);
                wait = wait->next;
                // cli = cli->next;
                // act = act->next;
            }
            else // si no existen mas registros
            {
                printf("%-5i | %-10s | %-50s\e[K\n", index, "", "");
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
        ;

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
    }
}
#pragma endregion