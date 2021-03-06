#pragma once
#include "../tpstructs.h"
#include "ABBHandler.h"
#include "Handlers.h"
//#include "../Interfaces/interfaces.h"


void InsertPago(ClientesPagos **node, ClientesPagos **list);
ClientesPagos *FindLastPago(ClientesPagos *list);
void FindINPago(int year, int mes);
ClientesPagos *GetPago(int index, ClientesPagos *list);
ClientesPagos *GetPagobyACTT(long actt, ClientesPagos *list);
int BorrarPago(int index, ClientesPagos **list);
void BuscarBorrarPago(int index, ClientesPagos **bor, ClientesPagos **ant);
void BorrarListaPago(ClientesPagos **list);

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
    if (index >= 0)
    {
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
    while (*bor && index > 0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
void BorrarListaPago(ClientesPagos **list)
{
    ClientesPagos *aux = NULL;
    while (*list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}

void LoadPagos(ClientesPagos **list)
{
    FILE *f;

    if (f = fopen("pagos.bin", "rb"))
    {
        ClientesPagos *node = (ClientesPagos *)malloc(sizeof(ClientesPagos));
        fread(node, sizeof(ClientesPagos), 1, f);
        while (!feof(f))
        {
            InsertPago(&node, list);
            node = (ClientesPagos *)malloc(sizeof(ClientesPagos));
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
ClientesPagos *GetPagobyACTT(long actt, ClientesPagos *list)
{
    if (!actt)
    {
        while (list)
        {
            if (list->actturn == actt)
                return list;
            list = list->next;
        }
    }
    return NULL;
}
void FindINPago(int year, int mes)
{
    ClientesPagos *list = pagos;
    ActTurno *actividad_turno = NULL;
    Clientes *cliente = NULL;
    while (list)
    {
        if (list->fechaEmision.tm_mon == mes && list->fechaEmision.tm_year == year &&
            (list->fechaPago.tm_mon != mes && list->fechaPago.tm_year != year))
        {
            actividad_turno = get_ActTurn((int)list->actturn, &acturn);
            if (actividad_turno)
            {
                cliente = FindClient(actividad_turno->dni, clientes);
                if (cliente)
                {
                    cargarEnABB(cliente);
                }
            }
        }
        list = list->next;
    }
}
