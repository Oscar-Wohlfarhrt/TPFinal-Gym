#pragma onece
    #include "../Interfaces/interfaces.h"

    void PrintSede();
    
    void PrintSede(){
        int sindex = sizeIndex(acturn);
        int maxacti = maxAct(acti);
        for(int m=1; m<maxacti+1;  m++){
            for(int i =0;i<sindex;i++){
                ActTurno *temp = get_ActTurn(i,&acturn);
                Turnos *turno = GetTurn(temp->turno,turnos);
                Actividades *actividad = GetActividad(turno->actividad,acti);

                if(m == actividad ->sucursal){
                    Clientes *cliente = FindClient(temp->dni,clientes);
                    printf("%i.  %s\n",m,cliente->nombre);
                }
            }
        }
    }

#pragma endregion