#pragma once
//#include "clpHandler.h"
#include "Handlers.h"

void ReindexPagos(int index,ClientesPagos *pag);

void ReindexPagos(int index,ClientesPagos *pag)
{
    // = pagos;
    while (pag)
    {
        if (pag->actturn == index)
        {
            pag->actturn = -1;
        }
        else if (pag->actturn > index)
        {
            pag->actturn = pag->actturn - 1;
        }
        pag = pag->next;
    }
}