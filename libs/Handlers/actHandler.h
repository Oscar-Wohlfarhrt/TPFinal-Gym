#pragma once
#include "../tpstructs.h"

_Bool remove_actividad(Actividades **dato, Actividades **e, Actividades **s);
Actividades *FindActividad(char *nombre, int suc, Actividades *s, Actividades *e);
Actividades *GetActividad(int index, Actividades *e, Actividades *s);

//interfaz
Actividades ActPrompt(Actividades *s, int *errout);

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
void ActiPrintList(Actividades *e,Actividades *s)
{
    const int entries = 10; // entradas por pagina
    // variables auxiliares
    int err = 1, page = 0;
    char op[20] = "";
    /*
     * err=0 salir
     * err=1 seguir
     * err=2 no hay mas registros en la lista
     */
    while (err)
    {
        system(cls);
        err = 1;

        // se obtiene la primera actividad de la lista
        Actividades *act = GetActividad(page * entries, e, s);
    /*  "Actividad",
        "Dia",
        "Hora de inicio",
        "hora de fin",
        "DNI Profesor",
        "Cupo Maximo",*/
        printf("\e[48;5;237m");
        printf("ACTIVIDADES: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-50s | %-20s\e[K\n", "Index", "ACTIVIDAD", "SUCURSAL");
        for (int i = 0; i < entries; i++)
        {
            int index = i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (act)
            {
                // se imprime la fila
                printf("%5i | %-50s | %-10i\e[K\e[0m\n", index, act->nombre, act->sucursal);

                act = act->next;
            }
            else // si no existen mas registros
            {
                printf("%5i\e[K\n\e[K\e[0m\n", index);
                err = 2;
            }
        }

        printf("\e[48;5;237m\e[K\e[0m\n");

        if (page) // formato para el boton de retroceso
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        // boton salir
        printf("<- a\e[0m|\e[48;5;22m salir - s \e[0m|");
        printf("\e[48;5;22m editar - e [index] \e[0m|\e[48;5;22m anadir - w \e[0m|\e[48;5;22m eliminar - x [index] \e[0m|");

        if (err != 2) // formato para el boton de siguiente
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        printf("d ->\e[0m "); // se limpia el formato

        fgets(op, 20, stdin);      // se lee la opcion
        *strchr(op, '\n') = '\0';  // se elimina el salto de linea
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        strlwr(op);
        if (!strncmp(op, "a", 1) && page) // decremento de pagina
            page--;
        else if (!strncmp(op, "d", 1) && err != 2) // incremento de pagina
            page++;
        else if (!strncmp(op, "s", 1)) // salir
            err = 0;
        else if (!strncmp(op, "w", 1)) // anadir
        {
            int errout = 0;
            Actividades data = ActPrompt(NULL, &errout);
            if (errout)
            {
                Actividades *newAct = (Actividades *)malloc(sizeof(Actividades));
                *newAct = data;
                enqueue_actividad(&newAct, &e, &s);
            }
        }
        else if (!strncmp(op, "e", 1)) // editar
        {/*
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            // se intenta convertir el indice a entero
            if (TryToInt32(ind, &editIndex))
            {
                Turnos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                if (editTurn = GetTurn(editIndex - 1, turnos))
                    TurnPrompt(editTurn, NULL);
            }*/
        }
        else if (!strncmp(op, "x", 1)) // eliminar
        {/*
            strtok(op, " ");
            char *ind = strtok(NULL, " ");
            int editIndex = 0;
            // se intenta convertir el indice a entero
            if (TryToInt32(ind, &editIndex))
            {
                //Turnos *editTurn = NULL;
                // se verifica que el turno no sea NULL
                //if (editTurn = GetTurn(editIndex - 1, turnos))
                
                BorrarTurn(editIndex - 1, &turnos);
            }*/
        }
    }
}
Actividades ActPrompt(Actividades *s, int *errout){
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
        "Sucursal",
    };

    // se muestra la interfaz y se imprime los items a modificar
    printf("\e[48;5;237m");
    printf("Actividades:\e[K\n\e[K\n");
    for (int i = 0; i < 2; i++)
    {
        (i % 2)?printf("\e[48;5;236m"):printf("\e[48;5;235m");

        printf("%i. %25s: ", i + 1, options[i]);
        if (s) ActPromptRestore(i, &s);
        printf("\e[K\e[0m\n");
    }
    printf("\e[48;5;237mcancelar edicion - c | finalizar edicion - e\e[K\e[0m\n");
    printf("\e[s"); // se guarda el cursor

    if (!s)
        s = &act;

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
            memcpy(&act,s,sizeof(Actividades));
            err = 0;
            if (errout)
                *errout = 0;
        }
        else if (op >= '1' && op <= '2')
        {
            index = op - '1';//se resta 49, por lo tanto el numero queda en entero - 1
            SetCurPos(30, index + 2);
            if (index % 2)//se imprime el color de fondo
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");
            printf("\e[K");//se limpia la linea

            char input[50];
            fgets(input, 50, stdin);
            fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
            input[strlen(input) - 1] = '\0';//se limpia el salto de linea

            if (strcmp(input, "c"))
            {
                if (err == 1)
                {
                    switch (index)
                    {
                    case 0:
                        strcpy(act.nombre, input);
                        break;
                    case 1:
                        TryToInt32(input, &act.sucursal);
                        break;
                    }
                }
            }
            ActPromptRestore(index, &act);
            printf("\e[u\e[J\e[0m");
        }
    }
    return act;
}
void ActPromptRestore(int index, Actividades *p)
{
    SetCurPos(30, index + 2);
    if (index % 2)//se escribe con este formato porque el color de fondo es el default
        printf("\e[48;5;236m");
    else
        printf("\e[48;5;235m");
    printf("\e[K");
    switch (index)
    {
    case 0:
        printf("%s", p->nombre);
        break;
    case 1:
        printf("%i", p->sucursal);
        break;
    }
}
#pragma endregion