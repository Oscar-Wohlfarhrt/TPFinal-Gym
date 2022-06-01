#pragma once
#include "../tpstructs.h"
// raiz del arbol binario
ABClientes *root = NULL;
ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo);
ABClientes *insert(ABClientes *raiz, ABClientes **nodo);
ABClientes *borrar(ABClientes *borrar);
ABClientes *borrarArbol(ABClientes *raiz);
ABClientes *GetAB(char *nombre, char *apellido, ABClientes *raiz);
void cargarEnABB();

ABClientes *insert(ABClientes *raiz, ABClientes **nodo)
{
    if (raiz)
    {
        if (strcmp((*nodo)->nombre, raiz->nombre) < 0 && strcmp((*nodo)->apellido, raiz->apellido) < 0)
            raiz->izq = insert(raiz->izq, &*nodo);
        else
            raiz->der = insert(raiz->der, &*nodo);
    }
    else
    {
        raiz = *nodo;
    }
    return raiz;
}
void cargarEnABB()
{
    ClientesPagos *pg = pagos;
    Clientes *cli = NULL;
    ABClientes *aux = NULL;
    while (pg)
    {
        cli = FindClient(pg->actturn, clientes);
        if (!pg->fechaPago.tm_mon && !cli->fechaBaja.tm_mon)//verificar esta condicion para las personas que no estan en baja y no pagaron
        {

            aux = (ABClientes *)malloc(sizeof(ABClientes));
            aux->dni = pg->actturn;
            strcpy(aux->apellido, cli->apellido);
            strcpy(aux->nombre, cli->nombre);
            strcpy(aux->telefono, cli->telefono);
            aux->der = NULL;
            aux->izq = NULL;
            root = insert(root, &aux);
        }
        pg = pg->next;
    }
}
ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo)
{
    short int sel;
    if (!raiz)
        return NULL;
    if (sel = (strcmp((nodo)->nombre, raiz->nombre)+strcmp((nodo)->apellido, raiz->apellido)))
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