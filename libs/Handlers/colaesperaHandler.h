#pragma once
#include "../tpstructs.h"

void enqueue_espera(colaEspera **p, colaEspera **e, colaEspera **s)
{
    (*p)->next = NULL;
    (!*s && !*e) ? *s = *p : *e->next = *p;
    *e = *p;
    *p = NULL;
}
void dequeue_espera(colaEspera **p, colaEspera **e, colaEspera **s)
{
    *p = *s;
    (!(*s)->next) ? *s = NULL : *s = (*s)->next;
    (*p)->next = NULL;
}
#pragma endregion