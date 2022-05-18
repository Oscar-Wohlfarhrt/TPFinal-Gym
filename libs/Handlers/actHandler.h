#pragma once
#include "../tpstructs.h"

_Bool vacio(void **top);
_Bool isNumber(char *text);
_Bool remove_actividad(Actividades **dato, Actividades **top);
Actividades *FindActividad(Actividades **dato, Actividades **top);
Actividades *FindActividad_ant(Actividades **dato, Actividades **top);
Actividades *GetActividad(int index, Actividades *list);

void apilar(Actividades **dato, Actividades **top)
{
    if (!*dato)
        return;
    (*dato)->next = *top;
    *top = *dato;
    *dato = NULL;
}
void desapilar(Actividades **dato, Actividades **top)
{
    *dato = *top;
    *top = (*top)->next;
}
_Bool vacio(void **top)
{
    if ((*top) == NULL)
    {
        return true;
    }
    return false;
}
_Bool isNumber(char *text)
{
    int j;
    j = strlen(text);
    while (j--)
    {
        if (text[j] >= '0' && text[j] <= '9')
            continue;
        return false;
    }
    return true;
}
int dia_a_num(char *texto)
{
    if (strcmp(texto, "domingo") == 0)
        return 0;
    else if (strcmp(texto, "lunes") == 0)
        return 1;
    else if (strcmp(texto, "martes") == 0)
        return 2;
    else if (strcmp(texto, "miercoles") == 0)
        return 3;
    else if (strcmp(texto, "jueves") == 0)
        return 4;
    else if (strcmp(texto, "viernes") == 0)
        return 5;
    else if (strcmp(texto, "sabado") == 0)
        return 6;
    return -1;
}
void load_actividades(Actividades **top)
{
    FILE *fichero;
    fichero = fopen("actividades.dat", "rb");
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
            nodo->next = *top;
            *top = nodo;
            nodo = NULL;
        }
    }
    fclose(fichero);
}
void save_actividades(Actividades **top)
{
    Actividades *aux = NULL, *tp2 = NULL, *tope = *top;
    FILE *fichero;
    fichero = fopen("actividades.dat", "wb");
    if (fichero == NULL || *top == NULL)
    {
        fclose(fichero);
        return;
    }
    while (!vacio(&tope))
    {
        desapilar(&aux, &tope);
        apilar(&aux, &tp2);
    }
    while (!vacio(&tp2))
    {
        desapilar(&aux, &tp2);
        fwrite(aux, sizeof(Actividades), 1, fichero);
        apilar(&aux, &tope);
    }
    fclose(fichero);
}
Actividades *FindActividad(Actividades **dato, Actividades **top)
{
    Actividades *aux = *top;
    while (!vacio(&aux))
    {
        if (strcmp((*dato)->nombre, aux->nombre) == 0 && (*dato)->sucursal == aux->sucursal)
            return aux;
        aux = aux->next;
    }
    return NULL;
}
Actividades *FindActividad_ant(Actividades **dato, Actividades **top)
{
    Actividades *aux = *top, *ant;
    while (!vacio(&aux))
    {
        if (strcmp((*dato)->nombre, aux->nombre) == 0 && (*dato)->sucursal == aux->sucursal)
            return ant;
        ant = aux;
        aux = aux->next;
    }
    return NULL;
}
Actividades *GetActividad(int index, Actividades *list)
{
    if (!list)
        return NULL;
    for (int i = 0; i <= index; i++)
    {
        if (i == index)
            return list;
        if (i <= index && !list)
            return NULL;
        list = list->next;
    }
    return NULL;
}
_Bool remove_actividad(Actividades **dato, Actividades **top)
{
    Actividades *aux = *top, *ant = NULL;
    while (!vacio(&aux))
    {
        if (strcmp(aux->nombre, (*dato)->nombre) == 0 && aux->sucursal == (*dato)->sucursal && aux == *top)
        {
            *top = (*top)->next;
            (*top)->next = NULL;
            free(aux);
            return true;
        }
        else if (strcmp(aux->nombre, (*dato)->nombre) == 0 && aux->sucursal == (*dato)->sucursal && aux != *top)
        {
            ant->next = aux->next;
            aux->next = NULL;
            free(aux);
            return true;
        }
        ant = aux;
        aux = aux->next;
    }
    return false;
}
#pragma endregion