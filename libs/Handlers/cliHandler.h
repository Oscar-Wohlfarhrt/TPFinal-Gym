#pragma once
#include <string.h>
#include "../tpstructs.h"

Clientes *FindLastClient(Clientes node, Clientes *list);
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

int ReplaceClient(int dni,Clientes newClient,Clientes *list){
    Clientes *cli=FindClient(dni,list);

    cli->dni=newClient.dni;
    strcpy(cli->nombre,newClient.nombre);
    strcpy(cli->apellido,newClient.apellido);
    strcpy(cli->telefono,newClient.telefono);
    cli->fechaNacimiento=newClient.fechaNacimiento;
    cli->ultimaActividad=newClient.ultimaActividad;
    cli->fechaBaja=newClient.fechaBaja;
}
