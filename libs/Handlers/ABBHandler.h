#pragma once
#include "../tpstructs.h"

ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo);
ABClientes *insert(ABClientes *raiz,ABClientes *nodo);
ABClientes *borrar(ABClientes *borrar);
short int cmp(char *str1, char *str2);
_Bool borrarArbol(ABClientes *root);
ABClientes *insert(ABClientes *raiz, ABClientes *nodo)
{
    int sel;
    if (!raiz)
        return nodo;
    else
    {
        if (sel = cmp(strcat(nodo->nombre, nodo->apellido), strcat(raiz->nombre, raiz->apellido)))
        {
            if (sel == 1)
                raiz->izq = insert(raiz->izq, nodo);
            if (sel == 2)
                raiz->der = insert(raiz->der, nodo);
        }
    }
    return nodo;
}
ABClientes *eliminar(ABClientes *raiz, ABClientes *nodo)
{
    short int sel;
    if (!raiz)
        return NULL;
    if (sel = cmp(strcat(nodo->nombre, nodo->apellido), strcat(raiz->nombre, raiz->apellido)))
    {
        if (sel == 1)
            raiz->izq = eliminar(raiz->izq, nodo);
        if (sel == 2)
            raiz->der = eliminar(raiz->der, nodo);
        if (!sel)
            raiz = borrar(raiz);
    }
    return (raiz);
}
ABClientes *borrar(ABClientes *borrar)
{
    ABClientes *ant, *r;
    ant = NULL;
    r = borrar->izq;
    if (r != NULL)
    {
        while (r->der != NULL)
        {
            ant = r;
            r = r->der;
        }
        r->der = borrar->der;
        if (ant != NULL)
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
_Bool cargarABClientes(ABClientes *root)
{
    ABClientes *nodo;
    FILE *f = fopen("ABClientes.bin", "rb");
    if(!f){
        fclose(f);
        return false;
    }
    if (f)
    {
        while (fread(&nodo, sizeof(ABClientes), 1, f))
        {
            nodo = (ABClientes *)malloc(sizeof(ABClientes))
            insert(&root, &nodo);
        }
    }
    return true;
}
ABClientes *borrarArbol(ABClientes *root){
    if(root){
        root->izq = borrarArbol(root->izq);
        root->der = borrarArbol(root->der);
    }
    if(!root->izq && !root->der){
        free(root);
        return NULL;
    } 
    return root;
}
short int cmp(char *str1, char *str2)
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
#pragma endregion