#pragma once
#include "../tpstructs.h"


ClientesPagos *pagos;

void InsertPago(ClientesPagos **node, ClientesPagos **list);
ClientesPagos *FindLastPago(ClientesPagos *list);
ClientesPagos *FindPago(long act,struct tm time, ClientesPagos *list);
ClientesPagos *GetPago(int index, ClientesPagos *list);
int BorrarPago(int index, ClientesPagos **list);
void BuscarBorrarPago(int index, ClientesPagos **bor, ClientesPagos **ant);
void BorrarListaPago(ClientesPagos **list);
void ReindexPagos(int index, ClientesPagos *list);

// escritura y lecura del archivo
void LoadPagos(ClientesPagos **list);
void SavePagos(ClientesPagos *list);

void InsertPago(ClientesPagos **node, ClientesPagos **list)
{
    (*node)->next = NULL;

    if (*list)
    {
        ClientesPagos *last = FindLastPago(*list);
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
ClientesPagos *FindLastPago(ClientesPagos *list)
{
    ClientesPagos *last = NULL;

    while (list)
    {
        last = list;
        list = list->next;
    }

    return last;
}
ClientesPagos *GetPago(int index, ClientesPagos *list)
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
int BorrarPago(int index, ClientesPagos **list)
{
    int err = 1;
    if(index>=0){
        ClientesPagos *ant = NULL, *bor = *list;
        BuscarBorrarPago(index, &bor, &ant);

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
void BuscarBorrarPago(int index, ClientesPagos **bor, ClientesPagos **ant)
{
    int found = 0;
    while (*bor && index>0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
void BorrarListaPago(ClientesPagos **list)
{
    ClientesPagos *aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}

void ReindexPagos(int index, ClientesPagos *list){
    
}

void LoadPagos(ClientesPagos **list)
{
    FILE *f;

    if (f = fopen("pagos.bin", "rb"))
    {
        ClientesPagos *node = (ClientesPagos*)malloc(sizeof(ClientesPagos));
        fread(node, sizeof(ClientesPagos), 1, f);
        while (!feof(f))
        {
            InsertPago(&node, list);
            node = (ClientesPagos*)malloc(sizeof(ClientesPagos));
            fread(node, sizeof(ClientesPagos), 1, f);
        }
        free(node);
        fclose(f);
    }
}
void SavePagos(ClientesPagos *list)
{
    FILE *f;

    if (f = fopen("pagos.bin", "wb"))
    {
        while (list)
        {
            fwrite(list, sizeof(ClientesPagos), 1, f);
            list = list->next;
        }
        fclose(f);
    }
}
