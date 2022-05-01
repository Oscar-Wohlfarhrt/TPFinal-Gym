#pragma once
#include <string.h>
#include "../tpstructs.h"

//Lista de clientes
Clientes *clientes;

/*
* Protoripos
*/
#pragma region Prototipos
void InsertClient(Clientes **node, Clientes **list);
Clientes *FindLastClient(Clientes node, Clientes *list);
Clientes *FindClient(int dni, Clientes *list);
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
        if (list->dni == dni){
            fNode=list;
            list = NULL;
        }
        else
            list = list->next;
    }

    return fNode;
}

Clientes *GetClient(int index, Clientes *list)
{
    while (list && index > 0)
    {
        list = list->next;
        index--;
    }

    return list;
}


void BuscarBorrarCliente(Clientes value, Clientes** bor, Clientes** ant);
int BorrarCliente(Clientes value, Clientes** list)
{
    int err = 1;
    Clientes* ant = NULL, * bor = *list;
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
void BuscarBorrarCliente(Clientes value, Clientes** bor, Clientes** ant)
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

int ReplaceClient(int dni,Clientes *newClient,Clientes *list){
    int err = 1;
    if(!BorrarCliente(*newClient,&list)){
        InsertClient(&newClient,&list);
        err=0;
    }

    return err;
}
