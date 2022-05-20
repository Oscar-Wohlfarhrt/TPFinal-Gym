#pragma once
#include "../tpstructs.h"

colaEspera *getbyName(char *array, colaEspera **e, colaEspera **s);
colaEspera *getbyDNI(long dni, colaEspera **e, colaEspera **s);

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
    if (!(*p) || !(*s))
        return;
    *p = *s;
    *s = (*s)->next;
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
        enqueue_espera(*p, *e, *s);
    }
    fclose(f);
}
colaEspera *getbyName(char *array, colaEspera **e, colaEspera **s){
    colaEspera *p = *s;
    while (p)
    {
        if (!strcmp(p->nombre, array))
            return p;
        p = p->next;
    }
    return NULL;
}
colaEspera *getbyDNI(long dni, colaEspera **e, colaEspera **s){
    colaEspera *p = *s;
    while (p)
    {
        if (p->dni == dni)
            return p;
        p = p->next;
    }
    return NULL;
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
_Bool remove_espera(colaEspera **p, colaEspera **e, colaEspera **s)
{
    colaEspera *p2 = *s;
    if (!(*p))
        return false;
    if (!(*e))
    {
        *s = NULL;
        return false;
    }
    if ((*p) == (p2))
    {
        *e = NULL;
        *s = NULL;
        return true;
    }
    while (p2->next != (*p))
        p2 = p2->next;
    p2->next = (*p)->next;
    free(*p);
    *p = NULL;
    return true;
}
#pragma endregion