#pragma once

 #include "../Interfaces/interfaces.h"
 #include "AdeudadoAfecha.h"

// interfaz
int maxSucursales(Actividades *list);
void SedePrintList();
int PrintSede(int day,int mont);

void SedePrintList()
{
    // variables auxiliares
    int err = 1;
    char op[20] = "";
    int day,month;
    int flag =0;
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
         if(flag == 0){
            printf("\e[0m "); // se limpia el formato
            printf("|\e[48;5;22m Ingrese una fecha (dd / mm)\e[0m| $");
            printf("\e[0m "); // se limpia el formato
            scanf("%i",&day);
            printf(" / ");
            scanf("%i",&month);
            month--;
            flag = 1;
        }else{ 
            printf("%-5s | %-5s | %-15s | %-5s | %-30s | %-5s    %-30s %-30s | %-5s\e[K\n", "Index", "SEDE","ACTIVIDAD","TURNO","PROFESOR", "CLIENTE:","NOMBRE","APELLIDO","DEUDA");

                PrintSede(day,month);

            //linea de separacion
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
}

int PrintSede(int day,int mont){
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
                    float dedudor = Deuda(i,mont,day,pagos);
                    if (index % 2)              //formato
                        printf("\e[48;5;236m"); //*
                    else                        //*
                        printf("\e[48;5;235m"); //formato

                    printf("%-5i | %-5i | %-15s | %-5i | %-30s |  %-5s       %-30s %-30s| %-5.2f\e[K\n", index,actividad ->sucursal, actividad ->nombre,(temp->turno)+1,profesor ->apellido,"", cliente->nombre,cliente->apellido,dedudor);
                    
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