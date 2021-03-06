#pragma once

#include "../Interfaces/interfaces.h"

// interfaz
void PrintReservaList();
int PrintEntriReserva(long indice);
void printReservaMenu();

//void CopyList(AuxActividades * ini);

void PrintReservaList()
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
        printf("Seleccione la actividad:\e[K\n");
        
        printReservaMenu();//lista de actividades 

        printf("\e[48;5;237m\e[K\e[0m\n");
        // boton salir
        printf("|\e[48;5;22m salir - s \e[0m| $");

        printf("\e[0m "); // se limpia el formato
        //printf("\nHOLA ESTO ES UN TEST");

        fgets(op, 20, stdin);      // se lee la opcion
        *strchr(op, '\n') = '\0';  // se elimina el salto de linea
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
        strlwr(op);
        int option;
        if (!strncmp(op, "s", 1))
                err = 0;// salir 

        if(TryToInt32(op,&option)!= 0) {
             if(option<=maxActi(acti)+1 && option>=1){
                if(PrintEntriReserva(option-1)!=0){
                    system(cls);
                    printf("\e[48;5;237m");                
                    printf("%-5s | %-15s | %-5s | %-5s | %-30s | %-5s    %-30s %-30s\e[K\n", "Index", "ACTIVIDAD","SEDE","TURNO","PROFESOR", "CLIENTE:","NOMBRE","APELLIDO");
                    PrintEntriReserva(option-1);
                }else
                    printf("No hay clientes registrados para la actividad");
                system("pause");
                option = -1;
            } 
        }else
            printf("");      
    }
}

void printReservaMenu(){
    int maxacti = maxActi(acti);
    int index = 1;
    printf("%-5s  %-5s\e[K\n","Index","Actividad");
    for(int i = 0;i<=maxacti;i++){
        
        if (index % 2)              //formato
            printf("\e[48;5;236m"); //*
        else                        //*
            printf("\e[48;5;235m"); //formato

        Actividades *print= GetActividad(i,acti);
        printf("%-5i  %-5s\e[K\n",i+1,print->nombre);
        index++;//formato
    }
}

int PrintEntriReserva(long indice){
    int index = 1;//formato
    int flag = 0;
    int sindex = maxReserva(reservaInput);//cantidad de reservas

        for(int i =sindex;i>=0;i--){
            Reservas *temp = GetRes(i,reservaOutput);
            Turnos *turno = GetTurn(temp->turno,turnos);
                
            if(indice == turno ->actividad){
                    
                Actividades *actividad = GetActividad(turno->actividad,acti);
                Profesores *profesor = FindProf(turno->prof,profes);
                Clientes *cliente = FindClient(temp->dni,clientes);
                    
                if (index % 2)              //formato
                    printf("\e[48;5;236m"); //*
                else                        //*
                    printf("\e[48;5;235m"); //formato

                printf("%-5i | %-15s | %-5i | %-5i | %-30s |  %-5s       %-30s %-30s\e[K\n", index, actividad ->nombre,actividad ->sucursal,(temp->turno)+1,profesor ->apellido,"", cliente->nombre,cliente->apellido);
                
                flag = 1;
                index++;//formato
            }
        }
    return flag;
}


#pragma endregion