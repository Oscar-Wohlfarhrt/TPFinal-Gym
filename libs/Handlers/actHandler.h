#pragma once
#include "../tpstructs.h"

Actividades *acti;

bool remove_actividad(Actividades **dato, Actividades **s);
bool BorrarAct(int index, Actividades **list);
bool existeActividad(char *nombre, int sede);
bool ReplaceAct(int index, Actividades **node, Actividades **list);
Actividades *FindActividad(char *nombre, int suc, Actividades *list);
Actividades *GetActividad(long index, Actividades *list);
Actividades *FindLastAct(Actividades *list);
void InsertActividad(Actividades **node, Actividades **list);
void load_actividades(Actividades **list);
void save_actividades(Actividades *list);
void BuscarBorrarAct(int index, Actividades **bor, Actividades **ant);
void borrarListaActividades(Actividades **list);
int maxActi(Actividades *list);

void InsertActividad(Actividades **node, Actividades **list)
{
    //bool status = false;
    (*node)->next = NULL;
    if (*list)
    {
        Actividades *last = FindLastAct(*list);
        //status = existeActividad((*node)->nombre, (*node)->sucursal);
        if (last) //&& !status)
        {
            (*node)->next = last->next;
            last->next = *node;
        }
    }
    else
    {
        *list = *node;
    }
    *node = NULL;
}
Actividades *FindLastAct(Actividades *list)
{
    Actividades *last = list;
    while (last->next)
        last = last->next;
    return last;
}
void load_actividades(Actividades **list)
{
    FILE *fichero;
    fichero = fopen("actividades.bin", "rb");
    if (fichero != NULL)
    {
        while (!feof(fichero))
        {
            Actividades *nodo = (Actividades *)malloc(sizeof(Actividades));
            fread(nodo, sizeof(Actividades), 1, fichero);
            if (feof(fichero))
            {
                fclose(fichero);
                break;
            }
            InsertActividad(&nodo, &(*list));
        }
    }
    fclose(fichero);
}
void save_actividades(Actividades *list)
{
    FILE *fichero;
    fichero = fopen("actividades.bin", "wb");
    if (!fichero || !list)
    {
        fclose(fichero);
        return;
    }
    while (list)
    {
        fwrite(list, sizeof(Actividades), 1, fichero);
        list = list->next;
    }
    fclose(fichero);
}
Actividades *FindActividad(char *nombre, int suc, Actividades *list)
{
    Actividades *aux = list;
    while (aux)
    {
        if (strcmp(nombre, aux->nombre) == 0 && suc == aux->sucursal)
            return aux;
        aux = aux->next;
    }
    return NULL;
}
Actividades *GetActividad(long index, Actividades *list)
{
    if (!list)
        return NULL;
    for (long i = 0; i <= index; i++)
    {
        if (i == index)
        {
            return list;
        }
        list = list->next;
    }
    return NULL;
}
bool remove_actividad(Actividades **dato, Actividades **s)
{
    Actividades *aux = *s;
    if (!(*dato))
        return false;
    if ((*dato) == (*s))
    {
        (*s) = (*s)->next;
        free(aux);
        return true;
    }
    while (aux)
    {
        if (*dato == aux->next)
        {
            aux->next = aux->next->next;
            free(*dato);
            return true;
        }
        aux = aux->next;
    }
}
bool BorrarAct(int index, Actividades **list)
{
    Actividades *ant = NULL, *bor = *list;
    if (index >= 0)
    {
        BuscarBorrarAct(index, &bor, &ant);
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
            return true;
        }
    }
    return false;
}
void BuscarBorrarAct(int index, Actividades **bor, Actividades **ant)
{
    while (*bor && index > 0)
    {
        *ant = *bor;
        *bor = (*bor)->next;
        index--;
    }
}
bool ReplaceAct(int index, Actividades **node, Actividades **list)
{
    Actividades *aux = *list;
    if (!index || !*node || !*list)
        return false;
    for (int i = 0; i < index; i++)
    {
        if (!aux)
            return false;
        aux = aux->next;
    }
    if (aux)
    {
        (*node)->next = aux->next;
        aux->next = *node;
        return true;
    }
}
void borrarListaActividades(Actividades **list)
{
    Actividades *aux = NULL;
    while (*list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}
bool existeActividad(char *nombre, int sede)
{
    if (acti && nombre && sede)
    {
        Actividades *lista = acti;
        while (lista)
        {
            if(strcmp(nombre,lista->nombre) == 0 &&
            lista->sucursal == sede){
                return true;
            }
            lista = lista->next;
        }
    }
    return false;
}

int maxActi(Actividades *list){
            int cont = -1;
            while (list != NULL){
                cont++;
                list = list ->next;
            } 
            return cont;
        }
#pragma endregion