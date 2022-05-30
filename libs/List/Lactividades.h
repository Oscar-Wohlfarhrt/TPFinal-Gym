#pragma once

#include "../Interfaces/interfaces.h"

// interfaz
void LActividadPrintList();
Actividades *rturnCompare();
int PrintActL();
int maxActi(Actividades *list);

void LActividadPrintList()
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
        printf("%-5s | %-15s | %-5s | %-5s | %-30s | %-5s    %-30s %-30s | %-5s\e[K\n", "Index", "ACTIVIDAD","SEDE","TURNO","PROFESOR", "CLIENTE:","NOMBRE","APELLIDO","DEUDA");
        
        PrintActL();

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

Actividades *rturnCompare(){
        printf("in Progress");
    }

    int PrintActL(){
        int index = 1;//formato

        int sindex = sizeIndex(acturn);
        int maxacti = maxActi(acti);
        
        for(int m=0; m<=maxacti;  m++){
            
            for(int i =0;i<sindex;i++){
                ActTurno *temp = get_ActTurn(i,&acturn);
                Turnos *turno = GetTurn(temp->turno,turnos);
                
                if(m == turno ->actividad){
                    
                    Actividades *actividad = GetActividad(turno->actividad,acti);
                    Profesores *profesor = FindProf(turno->prof,profes);
                    Clientes *cliente = FindClient(temp->dni,clientes);
                    
                    if (index % 2)              //formato
                        printf("\e[48;5;236m"); //*
                    else                        //*
                        printf("\e[48;5;235m"); //formato

                    printf("%-5i | %-15s | %-5i | %-5i | %-30s |  %-5s       %-30s %-30s| %-5s\e[K\n", index, actividad ->nombre,actividad ->sucursal,(temp->turno)+1,profesor ->apellido,"", cliente->nombre,cliente->apellido,".");
                    
                    index++;//formato
                }
            }
        }

        int maxActi(Actividades *list){
            int cont = -1;
            while (list != NULL){
                cont++;
                list = list ->next;
            } 
            return cont;
        }
    }
