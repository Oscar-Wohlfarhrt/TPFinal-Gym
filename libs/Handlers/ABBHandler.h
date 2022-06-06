#pragma once
#include "../tpstructs.h"
// raiz del arbol binario
ABClientes *root = NULL;
ABClientes *insert(ABClientes *raiz, ABClientes *nodo);
ABClientes *borrarArbol(ABClientes *raiz);
void cargarEnABB(Clientes *cli);

ABClientes *insert(ABClientes *raiz, ABClientes *nodo)
{
    if (!raiz)
        return nodo;
    if (strcmp(nodo->nombre, raiz->nombre) <= 0 && strcmp(nodo->apellido, raiz->apellido) < 0)
        raiz->izq = insert(raiz->izq, nodo);
    else if (strcmp(nodo->nombre, raiz->nombre) > 0 && strcmp(nodo->apellido, raiz->apellido) > 0)
        raiz->der = insert(raiz->der, nodo);
    else
        raiz->izq = insert(raiz->izq, nodo);
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