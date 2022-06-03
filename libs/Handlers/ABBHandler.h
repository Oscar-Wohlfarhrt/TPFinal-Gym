#pragma once
#include "../tpstructs.h"
// raiz del arbol binario
ABClientes *root = NULL;
ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo);
ABClientes *insert(ABClientes *raiz, ABClientes *nodo);
ABClientes *borrar(ABClientes *borrar);
ABClientes *borrarArbol(ABClientes *raiz);
ABClientes *GetAB(char *nombre, char *apellido, ABClientes *raiz);
void cargarEnABB();

ABClientes *insert(ABClientes *raiz, ABClientes *nodo)
{
    if (!raiz)
        return nodo;
    if (strcmp(nodo->nombre,raiz->nombre) <= 0 && strcmp(nodo->apellido,raiz->apellido) < 0)
        raiz->izq = insert(raiz->izq, nodo);
    else if (strcmp(nodo->nombre,raiz->nombre) > 0 && strcmp(nodo->apellido,raiz->apellido) > 0)
        raiz->der = insert(raiz->der, nodo);
    else 
        raiz->izq = insert(raiz->izq, nodo);
    return raiz;
}
void cargarEnABB()
{
    ClientesPagos *pg = pagos;
    Clientes *cli = clientes;
    ABClientes *aux = NULL;
    ActTurno *turn = NULL;
    while (cli)
    {
        turn = getbyActTurnoDNI(cli->dni, acturn);
        if (turn)
        {
            pg = GetPagobyACTT(turn->turno, pagos);
            if (!pg)
            {
                aux = (ABClientes *)malloc(sizeof(ABClientes));
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
        }
        cli = cli->next;
    }
}
ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo)
{
    short int sel;
    if (!raiz)
        return NULL;
    if (sel = (strcmp((nodo)->nombre, raiz->nombre) + strcmp((nodo)->apellido, raiz->apellido)))
    {
        if (sel > 0)
            raiz->izq = eliminar(raiz->izq, nodo);
        else
            raiz->der = eliminar(raiz->der, nodo);
    }
    else
        raiz = borrar(raiz);
    return (raiz);
}
ABClientes *borrar(ABClientes *borrar)
{
    ABClientes *ant, *r;
    ant = NULL;
    r = borrar->izq;
    if (r)
    {
        while (r->der)
        {
            ant = r;
            r = r->der;
        }
        r->der = borrar->der;
        if (ant)
        {
            ant->der = r->izq;
            r->izq = borrar->izq;
        }
    }
    else
    {
        r = borrar->der;
    }
    free(borrar);
    return (r);
}
/*
int cargarABClientes(ABClientes *raiz)
{
    ABClientes *nodo;
    FILE *f = fopen("ABClientes.bin", "rb");
    if (!f)
    {
        fclose(f);
        return false;
    }
    if (f)
    {
        while (fread(&nodo, sizeof(ABClientes), 1, f))
        {
            nodo = (ABClientes *)malloc(sizeof(ABClientes));
            insert(raiz, &nodo);
        }
    }
    return true;
}*/
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
ABClientes *GetAB(char *nombre, char *apellido, ABClientes *raiz)
{
    short int sel = strcmp(strcat(nombre, apellido), strcat(raiz->nombre, raiz->apellido));
    if (raiz)
    {
        if (sel == 0)
            return raiz;
        else if (sel > 0)
            raiz->der = GetAB(nombre, apellido, raiz->der);
        else
            raiz->izq = GetAB(nombre, apellido, raiz->izq);
    }
    return raiz;
}
#pragma endregion