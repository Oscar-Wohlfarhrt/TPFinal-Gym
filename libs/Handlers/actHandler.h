#pragma once
#include "../tpstructs.h"

_Bool remove_actividad(Actividades **dato, Actividades **e, Actividades **s);
Actividades *FindActividad(char *nombre, int suc, Actividades *s, Actividades *e);
Actividades *GetActividad(int index, Actividades *e, Actividades *s);

//interfaz
Actividades ActividadesPrompt(Actividades *e, Actividades *s, int *errout);

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
Actividades ActividadesPrompt(Actividades *e, Actividades *s, int *errout){
    system(cls);
    int err = 1;

    Actividades act;

    if (s)
        act = *s;

    char op = '\0';
    int index = 0;

    // opciones para el menu
    char *options[] = {
        "Actividad",
        "Dia",
        "Hora de inicio",
        "hora de fin",
        "DNI Profesor",
        "Cupo Maximo",
    };

    // se muestra la interfaz
    printf("\e[48;5;237m");
    printf("Turnos:\e[K\n\e[K\n");
    for (int i = 0; i < 6; i++)
    {
        (i % 2)?printf("\e[48;5;236m"):printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (turn)
            TurnPromptRestore(i, turn);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (!turn)
        turn = &cli;

    printf("\e[u"); // se resetea el cursor

    while (err)
    {
        err = 1;
        scanf("%c", &op);          // se lee la opcion
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        if (op == 'e')
        {
            err = 0;
            if (errout)
                *errout = 1;
        }
        else if (op == 'c')
        {
            *turn = cli;
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '6')
        {
            index = op - '1';

            SetCurPos(30, index + 2);
            if (index % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");
            printf("\e[K");

            char input[50];
            fgets(input, 50, stdin);
            fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
            *strchr(input, '\n') = '\0';

            struct tm tm;

            if (strcmp(input, "c"))
            {
                if (index == 2 || index == 3)
                {
                    char *hour = strtok(input, ":");
                    char *min = strtok(NULL, ":");

                    if (!TryToInt32(hour, &tm.tm_hour))
                        err = 2;
                    if (!TryToInt32(min, &tm.tm_min))
                        err = 2;
                }

                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        TryToInt64(input, &turn->actividad);
                        break;
                    case 1:
                        TryToInt32(input, &turn->dia);
                        break;
                    case 2:
                        turn->horarioInicio = tm;
                        break;
                    case 3:
                        turn->horarioFin = tm;
                        break;
                    case 4:
                        TryToInt64(input, &turn->prof);
                        break;
                    case 5:
                        TryToInt32(input, &turn->cupo);
                        break;
                    }
                }
            }
            TurnPromptRestore(index, turn);
            printf("\e[u\e[J\e[0m");
        }
    }

    return *turn;
}
#pragma endregion