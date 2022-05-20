#pragma once
#include "../tpstructs.h"

_Bool vacio(void **top);
_Bool remove_actividad(Actividades **dato, Actividades **e, Actividades **s);
Actividades *FindActividad(char *nombre, int suc, Actividades *s, Actividades *e);
Actividades *GetActividad(int index, Actividades *e, Actividades *s);

void enqueue_actividad(Actividades **p, Actividades **e, Actividades **s)
{
   if (!(*p))
      return;
   (*p)->next = NULL;
   if (!(*e))
   {
      *s = *p;
   }
   else
   {
      (*e)->next = *p;
   }
   *e = *p;
   *p = NULL;
}
void dequeue_actividad(Actividades **p, Actividades **e, Actividades **s)
{
    if (!p)
        return;
    *p = *s;
    if (!(*s)->next)
    {
        *s = NULL;
    }
    else
    {
        *s = (*s)->next;
    }
    (*p)->next = NULL;
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
void load_actividades(Actividades **e,Actividades **s)
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
            enqueue_actividad(&nodo, &(*e), &(*s));
        }
    }
    fclose(fichero);
}
void save_actividades(Actividades *e, Actividades *s)
{
    Actividades *aux = NULL;
    FILE *fichero;
    fichero = fopen("actividades.dat", "wb");
    if (!fichero || !s)
    {
        fclose(fichero);
        return;
    }
    while(s)
    {
        aux = s;
        s = s->next;
        fwrite(aux,sizeof(Actividades),1,fichero);
    }
    fclose(fichero);
}
Actividades *FindActividad(char *nombre, int suc, Actividades *s, Actividades *e)
{
    Actividades *aux = s;
    while (aux)
    {
        if (strcmp(nombre, aux->nombre) == 0 && suc == aux->sucursal)
            return aux;
        aux = aux->next;
    }
    return NULL;
}
Actividades *GetActividad(int index, Actividades *e, Actividades *s)
{
   for (int i = 0; i <= index; i++)
   {
      if (!s)
         return NULL;
      if (i == index)
      {
         return s;
      }
      s = s->next;
   }
   return NULL;
}
_Bool remove_actividad(Actividades **dato, Actividades **e, Actividades **s)
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
    while(aux){
        if(*dato == aux->next){
            aux->next = aux->next->next;
            free(*dato);
            return true;
        }
        aux = aux->next;
    }
}
#pragma endregion