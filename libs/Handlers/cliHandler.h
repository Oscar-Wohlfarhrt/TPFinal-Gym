#pragma once

/* --- IMPORTANTE ---
 * esta libreria utiliza codigos ANSI para el formato.
 * para mas informacion visitar: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */

#include <string.h>
#include "../tpstructs.h"

// Lista de clientes
Clientes *clientes = NULL;

/*
 * Protoripos
 */
#pragma region Prototipos
// manejo de la lista
void InsertClient(Clientes **node, Clientes **list);
Clientes *FindLastClient(Clientes node, Clientes *list);
Clientes *FindClient(int dni, Clientes *list);
Clientes *GetClient(int index, Clientes *list);
int BorrarCliente(Clientes value, Clientes **list);
void BuscarBorrarCliente(Clientes value, Clientes **bor, Clientes **ant);
int ReplaceClient(int dni, Clientes *newClient, Clientes *list);
void BorrarListaClientes(Clientes **list);

// escritura y lecura del archivo
void LoadClientes(Clientes **list);
void SaveClientes(Clientes *list);

// interfaz
Clientes ClientesPrompt(Clientes *client);
void ClientesPromptRestore(Clientes *client);
void ClientesPrintList();
#pragma endregion

void InsertClient(Clientes **node, Clientes **list)
{
    (*node)->next = NULL;
    if (*list)
    {
        Clientes *last = FindLastClient(**node, *list);
        if (last)
        {
            (*node)->next = last->next;
            last->next = *node;
        }
        else
        {
            (*node)->next = *list;
            *list = *node;
        }
    }
    else
    {
        *list = *node;
    }
    *node = NULL;
}
Clientes *FindLastClient(Clientes node, Clientes *list)
{
    Clientes *last = NULL;

    while (list)
    {
        if (list->dni > node.dni)
            list = NULL;
        else
        {
            last = list;
            list = list->next;
        }
    }

    return last;
}
Clientes *FindClient(int dni, Clientes *list)
{
    Clientes *fNode = NULL;

    while (list)
    {
        if (list->dni == dni)
        {
            fNode = list;
            list = NULL;
        }
        else
            list = list->next;
    }

    return fNode;
}
Clientes *GetClient(int index, Clientes *list)
{
    if (index >= 0)
    {
        while (list && index > 0)
        {
            list = list->next;
            index--;
        }
    }
    else
        list = NULL;

    return list;
}
int BorrarCliente(Clientes value, Clientes **list)
{
    int err = 1;
    Clientes *ant = NULL, *bor = *list;
    BuscarBorrarCliente(value, &bor, &ant);

    if (bor)
    {
        if (ant)
        {
            ant->next = bor->next;
        }
        else
        {
            *list = (*list)->next;
        }
        bor->next = NULL;
        free(bor);
        err = 0;
    }
    return err;
}
void BuscarBorrarCliente(Clientes value, Clientes **bor, Clientes **ant)
{
    int found = 0;
    while (bor && !found)
    {
        if (value.dni == (*bor)->dni)
        {
            found = 1;
        }
        else
        {
            *ant = *bor;
            *bor = (*bor)->next;
        }
    }
}
int ReplaceClient(int dni, Clientes *newClient, Clientes *list)
{
    int err = 1;
    if (!BorrarCliente(*newClient, &list))
    {
        InsertClient(&newClient, &list);
        err = 0;
    }

    return err;
}
void BorrarListaClientes(Clientes **list)
{
    Clientes *aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}

void LoadClientes(Clientes **list)
{
    FILE *f;

    if (f = fopen("clientes.bin", "rb"))
    {
        //BorrarListaClientes(&clientes);
        //*list = NULL;
        while (!feof(f))
        {
            Clientes *node = malloc(sizeof(Clientes));
            fread(node, sizeof(Clientes), 1, f);
            //printf("%p\n", node);
            InsertClient(&node, list);
        }
        fclose(f);
    }
}
void SaveClientes(Clientes *list)
{
    FILE *f;

    if (f = fopen("clientes.bin", "wb"))
    {
        while (list)
        {
            fwrite(list, sizeof(Clientes), 1, f);
            list = list->next;
        }
        fclose(f);
    }
}

Clientes ClientesPrompt(Clientes *client)
{
    system(cls);
    int err = 1;

    Clientes cli;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "DNI",
        "Nombre",
        "Apellido",
        "Telefono",
        "Fecha de nacimiento",
        "Fecha de ultima actividad",
        "Fecha de baja",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Clientes:\e[K\n\e[K\n");
    for (int i = 0; i < 7; i++)
    {
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");

        printf("%i. %25s: \e[K\e[0m\n", i + 1, options[i]);
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (client)
        ClientesPromptRestore(client);
    else
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
                        if (!TryToInt64(input, &client->dni))
                            ;
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
            ClientesPromptRestore(client);
            printf("\e[u\e[K\e[0m");
        }
    }

    return *client;
}
void ClientesPromptRestore(Clientes *client)
{
    for (int i = 0; i < 7; i++)
    {
        SetCurPos(30, i + 2);
        if (i % 2)
            printf("\e[48;5;236m");
        else
            printf("\e[48;5;235m");
        printf("\e[K");
        switch (i)
        {
        case 0:
            printf("%i", client->dni);
            break;
        case 1:
            printf("%s", client->nombre);
            break;
        case 2:
            printf("%s", client->apellido);
            break;
        case 3:
            printf("%s", client->telefono);
            break;
        case 4:
            printf("%02i/%02i/%04i", client->fechaNacimiento.tm_mday, client->fechaNacimiento.tm_mon + 1, client->fechaNacimiento.tm_year + 1900);
            break;
        case 5:
            printf("%02i/%02i/%04i", client->ultimaActividad.tm_mday, client->ultimaActividad.tm_mon + 1, client->ultimaActividad.tm_year + 1900);
            break;
        case 6:
            printf("%02i/%02i/%04i", client->fechaBaja.tm_mday, client->fechaBaja.tm_mon + 1, client->fechaBaja.tm_year + 1900);
            break;
        }
    }
}

void ClientesPrintList()
{
    const int entries = 10; // entradas por pagina

    // variables auxiliares
    int err = 1, page = 0;
    char op[20] = "";

    while (err)
    {
        system(cls);
        err = 1;

        // se obtiene el primer cliente de la lista
        Clientes *cli = GetClient(page * entries, clientes);
        printf("%p\n", cli);

        printf("\e[48;5;237m");
        printf("Clientes: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-50s | %-50s | %-20s | %-15s\e[K\n\e[0m", "Index", "DNI", "NOMBRE", "APELLIDO", "TELEFONO", "FECHA NACIMIENTO");
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
                char date[17];
                sprintf(date, "%02i/%02i/%04i", cli->fechaNacimiento.tm_mday, cli->fechaNacimiento.tm_mon + 1, cli->fechaNacimiento.tm_year + 1900);

                // se imprime la fila
                printf("%5i | %-10i | %-50s | %-50s | %-20s | %-15s\e[K\e[0m\n", index, cli->dni, cli->nombre, cli->apellido, cli->telefono, date);

                cli = cli->next;
            }
            else // si no existen mas registros
            {
                printf("%5i\e[K\e[0m\n", index);
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
        if (!strncmp(op, "a", 1) && page) //decremento de pagina
            page--;
        else if (!strncmp(op, "d", 1) && err != 2) //incremento de pagina
            page++;
        else if (!strncmp(op, "s", 1)) //salir
            err = 0;
        else if (!strncmp(op, "w", 1)) //anadir
        {
            Clientes *newCli = malloc(sizeof(Clientes));
            *newCli = ClientesPrompt(NULL);
            newCli->next = NULL;
            InsertClient(&newCli, &clientes);
        }
        else if (!strncmp(op, "e", 1)) //editar
        {
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            if (TryToInt32(ind, &editIndex))
            {
                Clientes *editCli=NULL;
                if(editCli=GetClient(editIndex - 1, clientes))
                    ClientesPrompt(editCli);
            }
        }
        else if (!strncmp(op, "x", 1)) //eliminar
        {
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            if (TryToInt32(ind, &editIndex))
            {
                BorrarCliente(*GetClient(editIndex - 1, clientes), &clientes);
            }
        }
    }
}
