#pragma once
#include "../tpstructs.h"
// raiz del arbol binario
ABClientes *root = NULL;
ABClientes *insert(ABClientes *raiz, ABClientes *nodo);
ABClientes *borrarArbol(ABClientes *raiz);
void cargarEnABB(Clientes *cli);
short cmp(char *str1, char *str2);

ABClientes *insert(ABClientes *raiz, ABClientes *nodo)
{
    if (!raiz)
        return nodo;
    if((strcmp(nodo->nombre, raiz->nombre)<0 || strcmp(nodo->apellido, raiz->apellido)<0)){
        raiz->izq = insert(raiz->izq, nodo);
    }
    else if((strcmp(nodo->nombre, raiz->nombre)>0 || strcmp(nodo->apellido, raiz->apellido)>0)){
        raiz->der = insert(raiz->der, nodo);
    }
    /*if (strcmp(nodo->nombre, raiz->nombre) <= 0 && strcmp(nodo->apellido, raiz->apellido) <= 0)
        raiz->izq = insert(raiz->izq, nodo);
    else if (strcmp(nodo->nombre, raiz->nombre) >= 0 && strcmp(nodo->apellido, raiz->apellido) > 0)
        raiz->der = insert(raiz->der, nodo);
    else
        raiz->der = insert(raiz->der, nodo);*/
    return raiz;
}
void cargarEnABB(Clientes *cli)
{
    ABClientes *aux = (ABClientes *)malloc(sizeof(ABClientes));
    aux->dni = cli->dni;
    strcpy(aux->apellido, cli->apellido);
    strcpy(aux->nombre, cli->nombre);
    strcpy(aux->telefono, cli->telefono);
    aux->der = NULL;
    aux->izq = NULL;
    strlwr(aux->nombre);
    strlwr(aux->apellido);
    root = insert(root, aux);
}
ABClientes *borrarArbol(ABClientes *raiz)
{
    if (raiz)
    {
        raiz->izq = borrarArbol(raiz->izq);
        raiz->der = borrarArbol(raiz->der);
        free(raiz);
        return NULL;
    }
    return raiz;
}
short cmp(char *str1, char *str2)
// aca se comparan los nombres y apellidos, para eso se deben concatenar el nombre y apellido y pasarlos por parametro
{
    /*
    0 = las strings son iguales
    1 = la string 1 es mas chica
    2 = la string 2 es mas chica
    */
    strlwr(str1);
    strlwr(str2);
    short int sel = 0;
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] < str2[i])
        {
            sel = 1;
            break;
        }
        else if (str1[i] > str2[i])
        {
            sel = 2;
            break;
        }
    }
    return sel;
}