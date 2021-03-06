#pragma once
#include "../tpstructs.h"
#include "handlersUtils.h"
#include "Handlers.h"
// puntero a la lista de actturn
ActTurno *acturn = NULL;

void load_ActTurn(ActTurno **list);
void save_ActTurn(ActTurno *list);
void insert_ActTurno(ActTurno **dato, ActTurno **list);
int remove_ActTurn(int turno, ActTurno **list);
int replace_ActTurn(int turno, ActTurno *newe, ActTurno **list);
int BorrarActTurn(int index, ActTurno **list);
ActTurno *get_ActTurn(int index, ActTurno **list);
ActTurno *find_ActTurn(long turno, ActTurno **list);
ActTurno *FindLastActTurno(ActTurno *list);
ActTurno *getbyActTurnoDNI(long dni, ActTurno *list);
void BuscarBorrarActTurn(int index, ActTurno **bor, ActTurno **ant);
void borrarListaActTurn(ActTurno **list);
int sizeIndex(ActTurno *list);
int countCupo(int turnIndex, ActTurno *list);

void load_ActTurn(ActTurno **list)
{
    FILE *fichero;
    fichero = fopen("ActTurn.bin", "rb");
    if (fichero != NULL)
    {
        while (!feof(fichero))
        {
            ActTurno *aux = (ActTurno *)malloc(sizeof(ActTurno));
            fread(aux, sizeof(ActTurno), 1, fichero);
            if (feof(fichero))
            {
                fclose(fichero);
                break;
            }
            insert_ActTurno(&aux, &(*list));
        }
    }
    fclose(fichero);
}
void save_ActTurn(ActTurno *list)
{
    FILE *f = fopen("ActTurn.bin", "wb");
    if (f)
    {
        while (list)
        {
            fwrite(list, sizeof(ActTurno), 1, f);
            list = list->next;
        }
    }
}
void insert_ActTurno(ActTurno **node, ActTurno **list)
{
    (*node)->next = NULL;
    if (*list)
    {
        ActTurno *last = FindLastActTurno(*list);
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
ActTurno *FindLastActTurno(ActTurno *list)
{
    ActTurno *last = list;
    while (last->next)
        last = last->next;
    return last;
}
int remove_ActTurn(int turno, ActTurno **list)
{
    ActTurno *aux = *list, *ant = NULL;
    while (aux)
    {
        if (aux->turno == turno)
        {
            if (!ant)
            {
                *list = aux->next;
            }
            else
            {
                ant->next = aux->next;
            }
            free(aux);
            return 1;
        }
        ant = aux;
        aux = aux->next;
    }
    return 0;
}
int replace_ActTurn(int turno, ActTurno *newe, ActTurno **list)
{
    ActTurno *aux = *list, *ant = NULL;
    while (aux)
    {
        if (turno == aux->turno)
        {
            if (!ant)
            {
                *list = newe;
            }
            else
            {
                ant->next = newe;
            }
            newe->next = aux->next;
            free(aux);
            return true;
        }
        ant = aux;
        aux = aux->next;
    }
    return false;
}
ActTurno *get_ActTurn(int index, ActTurno **list)
{
    ActTurno *aux = *list;
    if (!*list)
        return NULL;
    for (int i = 0; i <= index; i++)
    {
        if (i == index)
            return aux;
        if (i <= index && !aux)
            break;
        aux = aux->next;
    }
    return NULL;
}
ActTurno *find_ActTurn(long turno, ActTurno **list)
{
    ActTurno *aux = *list;
    while (aux)
    {
        if (aux->turno == turno)
            return aux;
        aux = aux->next;
    }
    return NULL;
}
int BorrarActTurn(int index, ActTurno **list)
{
    int err = 1;
    if (index >= 0)
    {
        ActTurno *ant = NULL, *bor = *list;
        BuscarBorrarActTurn(index, &bor, &ant);

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
            ReindexPagos(index,pagos);
            err = 0;
        }
    }
    return err;
}
void BuscarBorrarActTurn(int index, ActTurno **bor, ActTurno **ant)
{
    while (*bor && index > 0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
void borrarListaActTurn(ActTurno **list)
{
    ActTurno *aux = NULL;
    while (*list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}
int sizeIndex(ActTurno *list)
{
    int cont = 0;
    while (list != NULL)
    {
        cont++;
        list = list->next;
    }
    return cont;
}
ActTurno *getbyActTurnoDNI(long dni, ActTurno *list)
{
    while (list && dni)
    {
        if (dni == list->dni)
            return list;
        list = list->next;
    }
    return NULL;
}

int countCupo(int turnIndex, ActTurno *list)
{
    int count = -1;

    if (list)
        count = 0;

    while (list)
    {
        if (list->turno == turnIndex)
            count++;

        list = list->next;
    }

    return count;
}
