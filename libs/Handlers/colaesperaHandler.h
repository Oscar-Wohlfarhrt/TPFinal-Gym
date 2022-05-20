#pragma once
#include "../tpstructs.h"

typedef int _Bool;

colaEspera *getbyDNI(long dni, colaEspera **e, colaEspera **s);
_Bool remove_espera(colaEspera **dato, colaEspera **e, colaEspera **s);

void enqueue_espera(colaEspera **p, colaEspera **e, colaEspera **s)
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
void dequeue_espera(colaEspera **p, colaEspera **e, colaEspera **s)
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
void load_espera(colaEspera **p, colaEspera **e, colaEspera **s)
{
    FILE *f = fopen("espera.dat", "rb");
    if (!f)
        return;
    while (!feof(f))
    {
        colaEspera *nuevo = (colaEspera *)malloc(sizeof(colaEspera));
        fread(nuevo, sizeof(colaEspera), 1, f);
        enqueue_espera(&(*p), &(*e), &(*s));
    }
    fclose(f);
}
void save_espera(colaEspera **p, colaEspera **e, colaEspera **s)
{
    colaEspera *p2 = *s;
    FILE *f = fopen("espera.dat", "wb");
    if (!f)
        return;
    while (p2)
    {
        fwrite(p2, sizeof(colaEspera), 1, f);
        p2 = p2->next;
    }
    fclose(f);
}
colaEspera *getbyDNI(long dni, colaEspera **e, colaEspera **s)
{
    colaEspera *p = *s;
    while (p)
    {
        if (p->dni == dni)
            return p;
        p = p->next;
    }
    return NULL;
}
_Bool remove_espera(colaEspera **dato, colaEspera **e, colaEspera **s)
{
    colaEspera *aux = *s;
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
#pragma endregion