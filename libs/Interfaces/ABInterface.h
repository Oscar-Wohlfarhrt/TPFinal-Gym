#pragma once
#include "../Handlers/ABBHandler.h"

int *viewAB(ABClientes *raiz);
int i = 0;
void deudoresPrintList()
{
    char in;
    while (in != 'c')
    {
        system(cls);
        printf("\e[48;5;237m");
        printf("Deudores:\e[K\n");
        printf("%-5s | %-50s | %-50s | %-20s |\e[K\e[0m\n", "DNI", "NOMBRE", "APELLIDO", "TELEFONO");
        if (viewAB(root) == EXIT_FAILURE)
            printf("\e[48;5;236m\t\t\tVACIO\e[K\e[0m\n");
        printf("<- a\e[0m|\e[48;5;22m salir - s \e[0m|");
        fflsuh(stdin);
        in = getch();
    }
}

int *viewAB(ABClientes *raiz)
{
    Clientes *cli = FindClient(raiz->dni, clientes);
    ClientesPagos *pag = GetbyDNIPago(raiz->dni, pagos);
    if (!raiz)
        return EXIT_FAILURE;
    viewAB(raiz->izq);
    if (raiz->dni == cli->dni && pag->actturn == raiz->dni &&
        !(pag->fechaPago.tm_year) && !(cli->fechaBaja.tm_year))
    {
        (i % 2) ? printf("\e[48;5;236m") : printf("\e[48;5;235m");
        i++;
        printf("%-5i | %-50s | %-50s | %-20li\e[K\e[0m\n", i, raiz->dni, raiz->nombre, raiz->apellido, cli->telefono);
    }
    viewAB(raiz->der);
    return EXIT_SUCCESS;
}

#pragma endregion