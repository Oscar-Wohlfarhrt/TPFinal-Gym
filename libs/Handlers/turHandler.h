#pragma once
#include "../tpstructs.h"

Turnos *turnos;

void InsertTurn(Turnos **node, Turnos **list);
Turnos *FindLastTurn(Turnos node, Turnos *list);
Turnos *FindTurn(Turnos tur, Turnos *list);
Turnos *GetTurn(int index, Turnos *list);
int BorrarTurn(Turnos value, Turnos **list);
void BuscarBorrarTurn(Turnos value, Turnos **bor, Turnos **ant);
int ReplaceTurn(Turnos tur, Turnos *newClient, Turnos *list);
void BorrarListaTurnos(Turnos **list);

// escritura y lecura del archivo
void LoadTurnos(Turnos **list);
void SaveTurnos(Turnos *list);


void InsertTurn(Turnos **node, Turnos **list)
{
    (*node)->next = NULL;
    if (*list)
    {
        Turnos *last = FindLastTurn(**node, *list);
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
Turnos *FindLastTurn(Turnos node, Turnos *list)
{
    Turnos *last = NULL;

    while (list)
    {
        if (list->dias > node.dias)
            list = NULL;
        else
        {
            last = list;
            list = list->next;
        }
    }

    return last;
}
Turnos *FindTurn(struct tm time, Turnos *list)
{
    Turnos *fNode = NULL;
    while (list)
    {
        if (list->dias & (1<<time.tm_wday) &&
            difftime(mktime(&time),mktime(&list->horarioInicio))>0 &&
            difftime(mktime(&time),mktime(&list->horarioFin))<0 )
        {
            fNode = list;
            list = NULL;
        }
        else
            list = list->next;
    }

    return fNode;
}
Turnos *GetTurn(int index, Turnos *list)
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
int BorrarTurn(Turnos value, Turnos **list)
{
    int err = 1;
    Turnos *ant = NULL, *bor = *list;
    BuscarBorrarTurn(value, &bor, &ant);

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
void BuscarBorrarTurn(Turnos value, Turnos **bor, Turnos **ant)
{
    int found = 0;
    while (bor && !found)
    {
        if (value.dias == (*bor)->dias && 
            !difftime( mktime( &value.horarioFin) , mktime( &(*bor)->horarioFin)) && 
            !difftime( mktime( &value.horarioInicio) , mktime( &(*bor)->horarioInicio)))
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
int ReplaceTurn(Turnos tur, Turnos *newClient, Turnos *list)
{
    int err = 1;
    if (!BorrarTurn(*newClient, &list))
    {
        InsertTurn(&newClient, &list);
        err = 0;
    }

    return err;
}
void BorrarListaTurnos(Turnos **list)
{
    Turnos *aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}

void LoadTurnos(Turnos **list)
{
    FILE *f;

    if (f = fopen("clientes.bin", "rb"))
    {
        Turnos *node = (Turnos*)malloc(sizeof(Turnos));
        fread(node, sizeof(Turnos), 1, f);
        while (!feof(f))
        {
            InsertTurn(&node, list);
            node = (Turnos*)malloc(sizeof(Turnos));
            fread(node, sizeof(Turnos), 1, f);
        }
        free(node);
        fclose(f);
    }
}
void SaveTurnos(Turnos *list)
{
    FILE *f;

    if (f = fopen("clientes.bin", "wb"))
    {
        while (list)
        {
            fwrite(list, sizeof(Turnos), 1, f);
            list = list->next;
        }
        fclose(f);
    }
}
