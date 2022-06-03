#pragma once
#include "../Handlers/ABBHandler.h"

void mostrarINORDEN(ABClientes *raiz);
int leerTec();
void deudoresPrintList();
int j = 0, paginas = 0;

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
        j++;
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
        if (paginas > (acum - 10))
            paginas = acum - 10;
        if (paginas < 0)
            paginas = 0;
        j = 0;
    }
    root = borrarArbol(root);
}
int leerTec()
{
    int key = getKeyCode();
    int i = 0;
    if (key == key_down)
    {
        paginas++;
    }
    else if (key == key_up)
    {
        paginas--;
    }
    else if (key == key_escape)
    {
        i = -1;
    }
    return i;
}
void mostrarINORDEN(ABClientes *raiz)
{
    if (!raiz)
        return;
    mostrarINORDEN(raiz->izq);
    j++;
    if (j > (paginas) && j <= (paginas + 10))
    {
        (j % 2) ? printf("\e[48;5;236m") : printf("\e[48;5;235m");
        if (raiz->nombre[0] >= 97 && raiz->nombre[0] <= 122)
            raiz->nombre[0] -= 32;
        if (raiz->apellido[0] >= 97 && raiz->apellido[0] <= 122)
            raiz->apellido[0] -= 32;
        printf("\n%-5i | %-20li | %-50s | %-20s |", j, raiz->dni, raiz->nombre, "");
        printf("\n%-5s | %-20s | %-50s | %-20s |\e[K\e[0m", "", "", raiz->apellido, raiz->telefono);
        printf("\e[K\e[0m");
    }
    mostrarINORDEN(raiz->der);
}
#pragma endregion