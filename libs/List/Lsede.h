#pragma once

 #include "../Interfaces/interfaces.h"

// interfaz
int maxSucursales(Actividades *list);
void SedePrintList();
int PrintSede();

void SedePrintList()
{
    // variables auxiliares
    int err = 1;
    char op[20] = "";

    /*
     * err=0 salir
     */
    while (err)
    {
        system(cls);
        err = 1;

        // se obtiene el primer cliente de la lista

        printf("\e[48;5;237m");
        printf("Clientes por Sede:\e[K\n");
        printf("%-5s | %-5s | %-15s | %-5s | %-30s | %-5s    %-30s %-30s | %-5s\e[K\n", "Index", "SEDE","ACTIVIDAD","TURNO","PROFESOR", "CLIENTE:","NOMBRE","APELLIDO","DEUDA");
       if((sizeIndex(acturn))>0){
            PrintSede();
       }
        else{
            for(int i =0;i<10;i++){
                if (i % 2)              //formato
                printf("\e[48;5;236m"); //*
                else                        //*
                printf("\e[48;5;235m"); //formato
                
                printf("%-5i\e[K\n\e[K\e[0m\n",i);
            }
        }

        printf("\e[48;5;237m\e[K\e[0m\n");
        // boton salir
        printf("|\e[48;5;22m salir - s \e[0m| $");

        printf("\e[0m "); // se limpia el formato

        fgets(op, 20, stdin);      // se lee la opcion
        *strchr(op, '\n') = '\0';  // se elimina el salto de linea
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada

        strlwr(op);
         if (!strncmp(op, "s", 1))
             err = 0;// salir
    }
}

int PrintSede(){
        int index = 1;//formato

        int sindex = sizeIndex(acturn);
        int maxsede = maxSucursales(acti);//maximo de sucurdales
        
        for(int m=1; m<maxsede+1;  m++){
            
            for(int i =0;i<sindex;i++){
                ActTurno *temp = get_ActTurn(i,&acturn);
                Turnos *turno = GetTurn(temp->turno,turnos);
                Actividades *actividad = GetActividad(turno->actividad,acti);
                
                if(m == actividad ->sucursal){
                    
                    Profesores *profesor = FindProf(turno->prof,profes);
                    Clientes *cliente = FindClient(temp->dni,clientes);
                    
                    if (index % 2)              //formato
                        printf("\e[48;5;236m"); //*
                    else                        //*
                        printf("\e[48;5;235m"); //formato

                    printf("%-5i | %-5i | %-15s | %-5i | %-30s |  %-5s       %-30s %-30s| %-5s\e[K\n", index,actividad ->sucursal, actividad ->nombre,(temp->turno)+1,profesor ->apellido,"", cliente->nombre,cliente->apellido,".");
                    
                    index++;//formato
                }
            }
        }

    }

    int maxSucursales(Actividades *list){
    int cont = 0;
    while (list != NULL){
        if(list->sucursal>cont) cont = list->sucursal;
        list = list ->next;
    } 
    return cont;
}

#pragma enderegion