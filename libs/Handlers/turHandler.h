#pragma once
#include "../tpstructs.h"

Turnos *turnos;

void InsertTurn(Turnos **node, Turnos **list);
Turnos *FindLastTurn(Turnos *list);
Turnos *FindTurn(long act,struct tm time, Turnos *list);
Turnos *GetTurn(int index, Turnos *list);
int BorrarTurn(int index, Turnos **list);
void BuscarBorrarTurn(int index, Turnos **bor, Turnos **ant);
void BorrarListaTurnos(Turnos **list);

// escritura y lecura del archivo
void LoadTurnos(Turnos **list);
void SaveTurnos(Turnos *list);

void InsertTurn(Turnos **node, Turnos **list)
{
    (*node)->next = NULL;

    if (*list)
    {
        Turnos *last = FindLastTurn(*list);
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
Turnos *FindLastTurn(Turnos *list)
{
    Turnos *last = NULL;

    while (list)
    {
        last = list;
        list = list->next;
    }

    return last;
}
Turnos *FindTurn(long act,struct tm time, Turnos *list)
{
    Turnos *fNode = NULL;

    while (list)
    {
        if ((list->actividad == act) &&
            (list->horarioInicio.tm_hour<=time.tm_hour) && (list->horarioFin.tm_hour>=time.tm_hour) &&
            (list->horarioInicio.tm_min<=time.tm_min) && (list->horarioFin.tm_min>=time.tm_min))
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
int BorrarTurn(int index, Turnos **list)
{
    int err = 1;
    if(index>=0){
        Turnos *ant = NULL, *bor = *list;
        BuscarBorrarTurn(index, &bor, &ant);

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
    }
    return err;
}
void BuscarBorrarTurn(int index, Turnos **bor, Turnos **ant)
{
    int found = 0;
    while (*bor && index>0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
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

    if (f = fopen("turnos.bin", "rb"))
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

    if (f = fopen("turnos.bin", "wb"))
    {
        while (list)
        {
            fwrite(list, sizeof(Turnos), 1, f);
            list = list->next;
        }
        fclose(f);
    }
}
