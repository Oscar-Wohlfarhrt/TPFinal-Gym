#pragma once
#include "../tpstructs.h"


Reservas *getbyDNI(long dni, Reservas **list);
Reservas *FindReservas(long dni, char *actividad, Reservas *list);
Reservas *GetRes(int index, Reservas *list);
_Bool remove_espera(Reservas **dato, Reservas **list);
_Bool remove_espera(Reservas **dato, Reservas **list);

void insertReservas(Reservas **list, Reservas *new){
    Reservas *aux = *list;
    if(!aux){
        *list = new;
        return;
    }
    while(aux->next){
        aux = aux->next;
    }
    new->next = NULL;
    aux->next = new;
}
void load_Reservas(Reservas **list)
{
    FILE *f = fopen("espera.bin", "rb");
    if (!f)
        return;
    while (!feof(f))
    {
        Reservas *nuevo = (Reservas *)malloc(sizeof(Reservas));
        fread(nuevo, sizeof(Reservas), 1, f);
        insertReservas(&(*list), nuevo);
    }
    fclose(f);
}
void save_espera(Reservas *list)
{
    FILE *fichero;
    fichero = fopen("espera.bin", "wb");
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
Reservas *getbyDNI(long dni, Reservas **list)
{
    Reservas *p = *list;
    while (p)
    {
        if (p->dni == dni)
            return p;
        p = p->next;
    }
    return NULL;
}
Reservas *FindReservas(long dni, char *actividad, Reservas *list)
{
    Reservas *Nodo = NULL;
    while (list)
    {
        if(list->dni == dni && !(strcmp(list->actividad, actividad))){
            Nodo = list;
            break;
        }
        else
            list = list->next;
    }
    return Nodo;
}
_Bool remove_espera(Reservas **dato, Reservas **list)
{
    Reservas *aux = *list;
    if (!(*dato))
        return false;
    if ((*dato) == (*list))
    {
        (*list) = (*list)->next;
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
Reservas *GetRes(int index, Reservas *list)
{
    for (int i = 0; i <= index; i++)
    {
        if (!list)
            return NULL;
        if (i == index)
        {
            return list;
        }
        list = list->next;
    }
    return NULL;
}
void borrarListaReservas(Reservas **list)
{
    Reservas *aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}
#pragma endregion