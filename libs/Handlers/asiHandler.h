#pragma once
#include "../tpstructs.h"
#include "actturnHandler.h"
#include "cliHandler.h"

Asistencia *asist;

void InsertAsist(Asistencia **node, Asistencia **list);
Asistencia *FindLastAsist(Asistencia *list);
Asistencia *FindAsist(long act,struct tm time, Asistencia *list);
Asistencia *GetAsist(int index, Asistencia *list);
int BorrarAsist(int index, Asistencia **list);
void BuscarBorrarAsist(int index, Asistencia **bor, Asistencia **ant);
void BorrarListaAsist(Asistencia **list);
void UpdateClientDate(Asistencia,ActTurno *,Clientes *);

// escritura y lecura del archivo
void LoadAsist(Asistencia **list);
void SaveAsist(Asistencia *list);

void InsertAsist(Asistencia **node, Asistencia **list)
{
    (*node)->next = NULL;

    if (*list)
    {
        Asistencia *last = FindLastAsist(*list);
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
Asistencia *FindLastAsist(Asistencia *list)
{
    Asistencia *last = NULL;

    while (list)
    {
        last = list;
        list = list->next;
    }

    return last;
}
Asistencia *GetAsist(int index, Asistencia *list)
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
int BorrarAsist(int index, Asistencia **list)
{
    int err = 1;
    if(index>=0){
        Asistencia *ant = NULL, *bor = *list;
        BuscarBorrarAsist(index, &bor, &ant);

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
void BuscarBorrarAsist(int index, Asistencia **bor, Asistencia **ant)
{
    int found = 0;
    while (*bor && index>0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
void BorrarListaAsist(Asistencia **list)
{
    Asistencia *aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}
void UpdateClientDate(Asistencia node,ActTurno *actTurns,Clientes *clients){
    ActTurno *actturn = get_ActTurn(node.actturn, &actTurns);
    Clientes *client = NULL;
    if(actturn){
        client=FindClient(actturn->dni,clients);
        if(client){
            client->ultimaActividad = node.fecha;
        }
    }
}

void LoadAsist(Asistencia **list)
{
    FILE *f;

    if (f = fopen("asist.bin", "rb"))
    {
        Asistencia *node = (Asistencia*)malloc(sizeof(Asistencia));
        fread(node, sizeof(Asistencia), 1, f);
        while (!feof(f))
        {
            InsertAsist(&node, list);
            node = (Asistencia*)malloc(sizeof(Asistencia));
            fread(node, sizeof(Asistencia), 1, f);
        }
        free(node);
        fclose(f);
    }
}
void SaveAsist(Asistencia *list)
{
    FILE *f;

    if (f = fopen("asist.bin", "wb"))
    {
        while (list)
        {
            fwrite(list, sizeof(Asistencia), 1, f);
            list = list->next;
        }
        fclose(f);
    }
}
