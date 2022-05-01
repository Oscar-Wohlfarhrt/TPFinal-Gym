#pragma once

/* --- IMPORTANTE ---
* esta libreria utiliza codigos ANSI para el formato.
* para mas informacion visitar: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
*/

#include <string.h>
#include "../tpstructs.h"

//Lista de clientes
Clientes *clientes;

/*
* Protoripos
*/
#pragma region Prototipos
//manejo de la lista
void InsertClient(Clientes **node, Clientes **list);
Clientes *FindLastClient(Clientes node, Clientes *list);
Clientes *FindClient(int dni, Clientes *list);
int BorrarCliente(Clientes value, Clientes** list);
void BuscarBorrarCliente(Clientes value, Clientes** bor, Clientes** ant);
int ReplaceClient(int dni,Clientes *newClient,Clientes *list);
void BorrarListaClientes(Clientes **list);

//escritura y lecura del archivo
void LoadClientes(Clientes **list);
void SaveClientes(Clientes *list);

//interfaz
Clientes ClientesPrompt(Clientes *client);
void ClientesPrintList();
#pragma endregion

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
Clientes *GetClient(int index, Clientes *list)
{
    while (list && index > 0)
    {
        list = list->next;
        index--;
    }

    return list;
}
void BuscarBorrarCliente(Clientes value, Clientes** bor, Clientes** ant);
int BorrarCliente(Clientes value, Clientes** list)
{
    int err = 1;
    Clientes* ant = NULL, * bor = *list;
    BuscarBorrarCliente(value, &bor, &ant);

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
        err = 0;
    }
    return err;
}
void BuscarBorrarCliente(Clientes value, Clientes** bor, Clientes** ant)
{
    int found = 0;
    while (bor && !found)
    {
        if (value.dni == (*bor)->dni)
        {
            found = 1;
        }
        else
        {
            *ant = *bor;
            *bor = (*bor)->next;
        }
    }
}
int ReplaceClient(int dni,Clientes *newClient,Clientes *list)
{
    int err = 1;
    if(!BorrarCliente(*newClient,&list)){
        InsertClient(&newClient,&list);
        err=0;
    }

    return err;
}
void BorrarListaClientes(Clientes **list)
{
    Clientes* aux = NULL;
    while (list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}

void LoadClientes(Clientes **list)
{
    FILE *f;

    if(f=fopen("clientes.bin","rb")){
        while(!feof(f)){
            Clientes *node = malloc(sizeof(Clientes));
            fread(node,sizeof(Clientes),1,f);
            InsertClient(&node,list);
        }
        fclose(f);
    }
}
void SaveClientes(Clientes *list)
{
    FILE *f;

    if(f=fopen("clientes.bin","wb")){
        while(list){
            fwrite(list,sizeof(Clientes),1,f);
            list = list->next;
        }
        fclose(f);
    }
}

Clientes ClientesPrompt(Clientes *client){

}
void ClientesPrintList(){
    const int entries = 10; //entradas por pagina

    //variables auxiliares
    int err = 1, page = 0; 
    char op = '\0';

    while (err)
    {
        system(cls);
        err = 1;

        //se obtiene el primer cliente de la lista
        Clientes *cli = GetClient(page*entries, clientes);

        printf("\e[48;5;237m");
        printf("Clientes: Pagina %i\e[K\n", page + 1);
        printf("%-5s | %-10s | %-50s | %-50s | %-20s | %-15s\e[K\n\e[0m", "Index", "DNI", "NOMBRE", "APELLIDO", "TELEFONO", "FECHA NACIMIENTO");
        for (int i = 0; i < entries; i++)
        {
            int index=i + 1 + (page * entries);
            if (i % 2)
                printf("\e[48;5;236m");
            else
                printf("\e[48;5;235m");

            if (cli)
            {
                //se genera la fecha de nacimiento
                char date[17];
                sprintf(date, "%02i/%02i/%04i", cli->fechaNacimiento.tm_mday, cli->fechaNacimiento.tm_mon, cli->fechaNacimiento.tm_year + 1900);

                //se imprime la fila
                printf("%5i | %-10i | %-50s | %-50s | %-20s | %-15s\e[K\e[0m\n", index, cli->dni, cli->nombre, cli->apellido, cli->telefono, date);

                cli = cli->next;
            }
            else //si no existen mas registros
            {
                printf("%5i\e[K\e[0m\n", index);
                err = 2;
            }
        }

        printf("\e[48;5;237m\e[K\e[0m\n");

        if (page) //formato para el boton de retroceso
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        //boton salir
        printf("<- a\e[0m|\e[48;5;22m salir - s \e[0m|");

        if (err != 2) //formato para el boton de siguiente
            printf("\e[48;5;22m");
        else
            printf("\e[48;5;52m");

        printf("d ->\e[0m "); //se limpia el formato

        scanf("%c", &op);           //se lee la opcion 
        fseek (stdin, 0, SEEK_END); //se limpia el buffer de entrada

        tolower(op);
        if (op == 'a' && page)
            page--;
        if (op == 'd' && err != 2)
            page++;
        if (op == 's')
            err = 0;
    }
}
