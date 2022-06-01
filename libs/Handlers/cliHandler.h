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
Clientes *FindClient(long dni, Clientes *list);
Clientes *GetClient(int index, Clientes *list);
int BorrarCliente(Clientes value, Clientes **list);
void BuscarBorrarCliente(Clientes value, Clientes **bor, Clientes **ant);
int ReplaceClient(int dni, Clientes *newClient, Clientes *list);
void BorrarListaClientes(Clientes **list);
void UpdateClientBaja(Clientes *list);

// escritura y lecura del archivo
void LoadClientes(Clientes **list);
void SaveClientes(Clientes *list);

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
Clientes *FindClient(long dni, Clientes *list)
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
    while (*bor && !found)
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
void UpdateClientBaja(Clientes *list){
    time_t nowt=time(NULL);
    struct tm now=*localtime(&nowt);
    while(list){
        if(dayDifftime(now,list->ultimaActividad)>30)//2592000
            list->fechaBaja=now;

        list=list->next;
    }
}

void LoadClientes(Clientes **list)
{
    FILE *f;

    if (f = fopen("clientes.bin", "rb"))
    {
        Clientes *node = (Clientes *)malloc(sizeof(Clientes));
        fread(node, sizeof(Clientes), 1, f);
        while (!feof(f))
        {
            InsertClient(&node, list);
            node = (Clientes *)malloc(sizeof(Clientes));
            fread(node, sizeof(Clientes), 1, f);
        }
        free(node);
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
