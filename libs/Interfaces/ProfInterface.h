#pragma once

#include "../Handlers/profHandler.h"

// interfaz
Profesores ProfPrompt(Profesores *prof, int *errout);
void ProfPromptRestore(int index, Profesores *prof);
void ProfPrintList();

Profesores ProfPrompt(Profesores *prof, int *errout)
{
    system(cls);
    int err = 1;

    Profesores pro;


    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "DNI",
        "Nombre",
        "Apellido",
        "Telefono",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Profesores:\e[K\n\e[K\n");
    for (int i = 0; i < 4; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (prof)
            ProfPromptRestore(i, prof);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (prof)  pro = *prof;
    else prof = &pro;

    printf("\e[u"); // se resetea el cursor

    while (err)
    {
        err = 1;
        scanf("%c%*c", &op);          // se lee la opcion
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        if (op == 'e')
        {
            err = 0;
            if (errout)
                *errout = 1;
        }
        else if (op == 'c')
        {
            *prof = pro;
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
                /*if (index > 3) // para fecha
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
                }*/

                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        TryToInt64(input, &prof->dni);
                        break;
                    case 1:
                        strcpy(prof->nombre, input);
                        break;
                    case 2:
                        strcpy(prof->apellido, input);
                        break;
                    case 3:
                        strcpy(prof->telefono, input);
                        break;
                }
            }
            ProfPromptRestore(index, prof);
            printf("\e[u\e[0m\e[J");
            }
        }
    }
    return *prof;
}
void ProfPromptRestore(int index, Profesores *prof)
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
        printf("%li", prof->dni);
        break;
    case 1:
        printf("%s", prof->nombre);
        break;
    case 2:
        printf("%s", prof->apellido);
        break;
    case 3:
        printf("%s", prof->telefono);
        break;
    }
}
void ProfPrintList()
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
        Profesores *pro = GetProf(page * entries, profes);

        printf("\e[48;5;237m");
        printf("Profesores: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-50s | %-20s\e[K\n", "Index", "DNI", "NOMBRE", "TELEFONO");
        printf("%-5s | %-10s | %-50s | %-20s\e[K\n\e[0m", "", "", "APELLIDO","");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (pro)
            {
                /*// se genera la fecha de nacimiento
                {char date1[17], date2[17], date3[17];
                sprintf(date1, "%02i/%02i/%04i", pro->fechaNacimiento.tm_mday, pro->fechaNacimiento.tm_mon + 1, pro->fechaNacimiento.tm_year + 1900);
                sprintf(date2, "%02i/%02i/%04i", pro->ultimaActividad.tm_mday, pro->ultimaActividad.tm_mon + 1, pro->ultimaActividad.tm_year + 1900);
                sprintf(date3, "%02i/%02i/%04i", pro->fechaBaja.tm_mday, pro->fechaBaja.tm_mon + 1, pro->fechaBaja.tm_year + 1900);}*/

                // se imprime la fila
                printf("%5i | %-10li | %-50s | %-20s\e[K\n", index, pro->dni, pro->nombre, pro->telefono);
                printf("%5s | %-10s | %-50s | %-20s\e[K\e[0m\n", "", "", pro->apellido,"");

                pro = pro->next;
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
        else if (!strncmp(op, "s", 1))
            err = 0;// salir
        else if (!strncmp(op, "w", 1)) // anadir
        {
            int errout = 0;
            Profesores data = ProfPrompt(NULL, &errout);
            if (errout)
            {
                Profesores *newProf = (Profesores *)malloc(sizeof(Profesores));
                *newProf = data;
                InsertP(&newProf, &profes);
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
                Profesores *editProf = NULL;
                // se verifica que el cliente no sea NULL
                if (editProf = GetProf(editIndex - 1, profes))
                    ProfPrompt(editProf, NULL);
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
                Profesores *editProf = NULL;
                // se verifica que el cliente no sea NULL
                if (editProf = GetProf(editIndex - 1, profes))
                    RemoveP(*editProf, &profes);
            }
        }
    }
}
