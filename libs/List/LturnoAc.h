#pragma once

#include "../Interfaces/interfaces.h"

// interfaz
void TurnsActList();
int PrintTurnActL(int indice);
void printTurnActMenu();

int MaxTurns(Turnos*list);

//void CopyList(AuxActividades * ini);

void TurnsActList()
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
        
        printTurnActMenu();//lista de actividades disponible

        printf("\e[48;5;237m\e[K\e[0m\n");
        // boton salir
        printf("|\e[48;5;22m salir - s \e[0m| $");

        printf("\e[0m "); // se limpia el formato

        fgets(op, 20, stdin);      // se lee la opcion
        *strchr(op, '\n') = '\0';  // se elimina el salto de linea
        fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
        strlwr(op);
        int option;      //convierte char a int

        if (!strncmp(op, "s", 1))
             err = 0;// salir 
        
        if(TryToInt32(op,&option)!= 0) {
             if(option<=maxActi(acti)+1 && option>=1){
                if(PrintTurnActL(option-1)!=0){
                    system(cls);
                    printf("%-5s | %-15s | %-5s | %-5s \e[K\n", "Index", "ACTIVIDAD","TURNO","CUPO");
                    PrintTurnActL(option-1);
                }else
                    printf("No hay turnos registrados para la actividad");
                system("pause");
                option = -1;
            } 
        }else
            printf("");  
    }
}

void printTurnActMenu(){
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

int PrintTurnActL(int indice){
    int index = 1;//formato
    int flag = 0;
    int sindex = MaxTurns(turnos);//cantidad de TURNS

    printf("\e[48;5;237m");                
        for(int i =0;i<sindex;i++){
            Turnos *turno = GetTurn(i,turnos);
                
            if(indice == turno ->actividad){
                    
                Actividades *actividad = GetActividad(turno->actividad,acti); 
                if (index % 2)              //formato
                    printf("\e[48;5;236m"); //*
                else                        //*
                    printf("\e[48;5;235m"); //formato

                printf("%-5i | %-15s | %-5i | %-5i \e[K\n", index, actividad ->nombre,i,turno->cupo);
                
                flag = 1;
                index++;//formato
            }
        }
    return flag;
}


int MaxTurns(Turnos*list){
        int cont = -1;
        while (list != NULL){
            cont++;
            list = list ->next;
        } 
        return cont;
    }
//lk