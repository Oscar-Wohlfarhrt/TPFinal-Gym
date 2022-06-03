#pragma once
#include "../tpstructs.h"
//Apunta a la lista de reservas
Reservas *reservaInput =NULL,*reservaOutput=NULL;

void ResEnqueue(Reservas **node,Reservas **input,Reservas **output);
void ResDequeue(Reservas **node,Reservas **input,Reservas **output);
void borrarListaReservas(Reservas **input,Reservas **output);
void load_Reservas(Reservas **input,Reservas **output);
void save_espera(Reservas **input,Reservas **output);
Reservas *getbyDNI(long dni, Reservas **list);
Reservas *FindReservas(long dni, char *actividad, Reservas *list);
Reservas *GetRes(long index, Reservas *list);

int remove_espera(Reservas **dato, Reservas **list);

void ResEnqueue(Reservas **node,Reservas **input,Reservas **output){
    (*node)->next=NULL;
    if(!*input)
        *output = *node;
    else
        (*input)->next = *node;

    *input=*node;
    *node=NULL;
}
void ResDequeue(Reservas **node,Reservas **input,Reservas **output){
    *node=*output;
    *output=(*output)->next;
    if(!*output)
        *input=NULL;
    (*node)->next=NULL;
}
void load_Reservas(Reservas **input,Reservas **output)
{
    FILE *f = fopen("espera.bin", "rb");
    if (f){
        Reservas *nuevo = (Reservas *)malloc(sizeof(Reservas));
        fread(nuevo, sizeof(Reservas), 1, f);
        while (!feof(f))
        {
            printf("load\n");
            ResEnqueue(&nuevo, input,output);
            nuevo = (Reservas *)malloc(sizeof(Reservas));
            fread(nuevo, sizeof(Reservas), 1, f);
        }
        free(nuevo);
        fclose(f);
    }
}
void save_espera(Reservas **input,Reservas **output)
{
    FILE *fichero;
    Reservas *node;

    if (fichero = fopen("espera.bin", "wb"))
    {
        while (*output)
        {
            ResDequeue(&node,input,output);
            fwrite(node, sizeof(Actividades), 1, fichero);
        }
        fclose(fichero);
    }
}
/*Reservas *GetRes(long index, Reservas **input,Reservas **output)
{
    Reservas *node,*binput,*boutput,*aux=NULL;
    while (*output && (index+1))
    {
        ResDequeue(&node,input,output);
        if(!index){
            aux=node;
        }
        ResEnqueue(&node,&binput,&boutput);
        index--;
    }
    while(*output){
        ResDequeue(&node,input,output);
        ResEnqueue(&node,&binput,&boutput);
    }
    while(boutput){
        ResDequeue(&node,&binput,&boutput);
        ResEnqueue(&node,input,output);
    }
    return aux;
}*/
Reservas *GetRes(long index, Reservas *output)
{
    if (index >= 0)
    {
        while (output && index > 0)
        {
            output = output->next;
            index--;
        }
    }
    else
        output = NULL;

    return output;
}
int ResRemove(long index, Reservas **input,Reservas **output)
{
    Reservas *node,*binput,*boutput,*aux=NULL;
    while (*output)
    {
        ResDequeue(&node,input,output);
        if(!index)
            ResEnqueue(&node,&binput,&boutput);
        index--;
    }
    while(boutput){
        ResDequeue(&node,&binput,&boutput);
        ResEnqueue(&node,input,output);
    }
    return 0;
}
void borrarListaReservas(Reservas **input,Reservas **output)
{
    Reservas *node;
    while (*output)
    {
        ResDequeue(&node,input,output);
        free(node);
    }
}
#pragma endregion