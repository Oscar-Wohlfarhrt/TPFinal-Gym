#pragma once
#include "../Interfaces/interfaces.h"
//se presupone que el cliente no debe un cuota anterior a una actual
//pagada
//importe de cuota 100$  con el 10%  110$

float Deuda(int now,int mont,int day,ClientesPagos * ini);

float Deuda(int now,int mont,int day,ClientesPagos * ini){
    float adedudado=0;
    while(ini!=NULL){
        if((long)now == ini->actturn){
            if(ini->fechaPago.tm_mday == 0){// pago o no
                if(ini->fechaEmision.tm_mon<mont){ //mes pasado
                    adedudado += (ini->monto*1.1);
                }else if(ini->fechaEmision.tm_mon=mont){// mes actual
                    if(ini->fechaEmision.tm_mday<=10)
                        adedudado += (ini->monto);
                    else 
                        adedudado += (ini->monto*1.1);
                }
            }
        }
        ini= ini->next;
    }
    return adedudado;
}
