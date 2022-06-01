#pragma once
#include "../Handlers/ABBHandler.h"

void mostrarINORDEN(ABClientes *raiz);
int leerTec();
void deudoresPrintList();
int j = 0, page = 0;

void deudoresPrintList()
{
    cargarEnABB();
    int acum = 0, status = 0;
    char c;
    while (status != -1)
    {
        system("cls");
        printf("\e[48;5;233mDEUDORES:\e[K\e[0m\n\e[48;5;233m%-5s | %-20s | %-50s | %-20s \e[K\e[0m|", "", "DNI", "Nombre", "");
        printf("\n\e[48;5;233m%-5s | %-20s | %-50s | %-20s \e[K\e[0m|", "", "", "Apellido", "Telefono");
        mostrarINORDEN(root);
        acum = j;
        j ++;
        while (j < 10)
        {
            (j % 2) ? printf("\e[48;5;236m") : printf("\e[48;5;235m");
            printf("\n%-5i | %-20s | %-50s | %-20s |", j, "", "", "");
            printf("\n%-5s | %-20s | %-50s | %-20s |\e[K\e[0m", "", "", "", "");
            printf("\e[K\e[0m");
            j++; // fijarse que este puede ir antes de la condicion
        }
        printf("\n\n\e[48;5;236m/\\ - ARRIBA\e[0m|\e[48;5;236m\\/ - ABAJO\e[0m\n");
        status = leerTec();
        if (page > (acum - 10))
            page = acum - 10;
        if (page < 0)
            page = 0;
        j = 0;
    }
    root = borrarArbol(root);
}
int leerTec()
{
    short int KEY_DWN = 80;
    short int KEY_UP = 72;
    int i = 0;
    char c = '\0';
    fflush(stdin);
    printf("\n");
    c = getch();
    if (c == KEY_DWN)
    {
        page++;
    }
    else if (c == KEY_UP)
        page--;
    else if (c == 27)
        i = -1;
    return i;
}
void mostrarINORDEN(ABClientes *raiz)
{
    if (!raiz)
        return;
    mostrarINORDEN(raiz->izq);
    j++;
    if (j > (page) && j <= (page + 10))
    {
        (j % 2) ? printf("\e[48;5;236m") : printf("\e[48;5;235m");
        printf("\n%-5i | %-20li | %-50s | %-20s |", j, raiz->dni, raiz->nombre, "");
        printf("\n%-5s | %-20s | %-50s | %-20s |\e[K\e[0m", "", "", raiz->apellido, raiz->telefono);
        printf("\e[K\e[0m");
    }
    mostrarINORDEN(raiz->der);
}
#pragma endregion