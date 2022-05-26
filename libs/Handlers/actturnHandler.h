#pragma once
#include "../tpstructs.h"

void load_ActTurn(ActTurno **list);
void save_ActTurn(ActTurno *list);
void insert_ActTurno(ActTurno **dato, ActTurno **list);
_Bool remove_ActTurn(int turno, ActTurno **list);
_Bool replace_ActTurn(int turno, ActTurno *new, ActTurno **list);
int BorrarActTurn(int index, ActTurno **list);
ActTurno *get_ActTurn(int index, ActTurno **list);
ActTurno *find_ActTurn(int turno, ActTurno **list);
ActTurno *FindLastActTurno(ActTurno *list);

void load_ActTrun(ActTurno **list)
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
            InsertActividad(&aux, &(*list));
        }
    }
    fclose(fichero);
}
void save_ActTrun(ActTurno *list)
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
_Bool remove_ActTurn(int turno, ActTurno **list)
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
            return true;
        }
        ant = aux;
        aux = aux->next;
    }
    return false;
}
_Bool replace_ActTurn(int turno, ActTurno *new, ActTurno **list)
{
    ActTurno *aux = *list, *ant = NULL;
    while (aux)
    {
        if (turno == aux->turno)
        {
            if (!ant)
            {
                *list = new;
            }
            else
            {
                ant->next = new;
            }
            new->next = aux->next;
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
            return NULL;
        aux = aux->next;
    }
    return NULL;
}
ActTurno *find_ActTurn(int turno, ActTurno **list)
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
            err = 0;
        }
    }
    return err;
}
void BuscarBorrarActTurn(int index, ActTurno **bor, ActTurno **ant)
{
    int found = 0;
    while (*bor && index > 0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
void borrarListaActTurn(ActTurno **list)
{
    ActTurno *aux = *list;
    while (aux)
    {
        *list = (*list)->next;
        free(aux);
        aux = *list;
    }
}
#pragma endregion