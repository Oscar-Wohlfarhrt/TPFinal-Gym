#pragma once
#include "../Handlers/ABBHandler.h"

void mostrarINORDEN(ABClientes *raiz);
int leerTec();
void deudoresPrintList();
int j = 0, paginas = 0, year = 0, month = -2; // si el mes es -2 no se muestra nada
char entrada[50] = "";

void deudoresPrintList()
{
    //ReindexActTurnos();
    FindINPago(122,5);
    int acum = 0, status = 0;
    char c; //, *date1,*date2;
    while (status != -1)
    {
        system("cls");
        printf("\e[48;5;233mDEUDORES[%d/%d]:\e[K\e[0m\n\e[48;5;233m%-5s | %-20s | %-50s | %-20s \e[K\e[0m|",(month!=-2)?month+1:00,(month!=-2)?year+1900:00,"Index", "DNI", "Nombre", "Telefono");
        printf("\n\e[48;5;233m%-5s | %-20s | %-50s | %-20s \e[K\e[0m|", "", "", "Apellido", "");
        mostrarINORDEN(root);
        acum = j;
        j++;
        while (j <= 10)
        {
            (j % 2) ? printf("\e[48;5;236m") : printf("\e[48;5;235m");
            printf("\n%-5i | %-20s | %-50s | %-20s |", j, "", "", "");
            printf("\n%-5s | %-20s | %-50s | %-20s |\e[K\e[0m", "", "", "", "");
            printf("\e[K\e[0m");
            j++; // fijarse que este puede ir antes de la condicion
        }
        printf("\n>Filtrar(mm/yyyy): ");
        printf("\n\n|\e[48;5;22m ^ - Arriba \e[0m|\e[48;5;22m ESC/S - Salir \e[0m|\e[48;5;22m C - Cancelar \e[0m|\e[48;5;52m v - Abajo \e[0m|");
        SetCurPos(18,23);
        status = leerTec();
        if (paginas > (acum - 10))
            paginas = acum - 10;
        if (paginas < 0)
            paginas = 0;
        j = 0;
        if (status == -2)
        {
            if (!strncmp(entrada,"s",1))
                break;
            fflush(stdin);
            fgets(entrada, 20, stdin);
            entrada[strlen(entrada) - 1] = '\0';
            if (!strncmp(entrada,"s",1))
                break;
            if (strncmp(entrada,"c",1))
            {
                char *date1 = strtok(entrada, "/");
                char *date2 = strtok(NULL, "/");
                if (TryToInt32(date1, &month))
                {
                    month = month - 1;
                    if (month >= 0 && month <= 11 && TryToInt32(date2, &year))
                    {
                        year = year - 1900;
                    }
                    else
                    {
                        month = -2;
                    }
                }
            }
        }
        root = borrarArbol(root);
        FindINPago(year,month);
    }
    month = -2;
    root = borrarArbol(root);
}
int leerTec()
{
    int key = getKeyCode();
    int i = 0;
    switch (key)
    {
    case key_down:
        paginas++;
        break;

    case key_up:
        paginas--;
        break;

    case key_escape: // salir
        i = -1;
        break;

    default:
        entrada[0] = key;
        i = -2;
        break;
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
        if (raiz->nombre[0] >= 97 && raiz->nombre[0] <= 122) // pone en mayuscula la primera letra
            raiz->nombre[0] -= 32;
        if (raiz->apellido[0] >= 97 && raiz->apellido[0] <= 122) // solo si es una letra dentro del abecedario
            raiz->apellido[0] -= 32;
        printf("\n%-5i | %-20li | %-50s | %-20s |", j, raiz->dni, raiz->nombre, "");
        printf("\n%-5s | %-20s | %-50s | %-20s |\e[K\e[0m", "", "", raiz->apellido, raiz->telefono);
        printf("\e[K\e[0m");
    }
    mostrarINORDEN(raiz->der);
}