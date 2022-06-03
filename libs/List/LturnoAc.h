#pragma once

#include "../Interfaces/interfaces.h"

// interfaz
void TurnsActList();
int PrintTurnActL(int indice);
void printTurnActMenu();
int maxTActi(Actividades *list);

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
        int option = atoi(op);      //convierte char a int

        if (!strncmp(op, "s", 1))
             err = 0;// salir 
        else if(option<=maxTActi(acti) && option>=0){
            if(PrintTurnActL(option)!=0){
                system(cls);
                PrintTurnActL(option);
            }else
                printf("No hay turnos registrados para la actividad");
            option = -1;
            system("pause");
        }       
    }
}

void printTurnActMenu(){
    int maxacti = maxTActi(acti);
    int index = 1;
    printf("%-5s  %-5s\e[K\n","Index","Actividad");
    for(int i = 0;i<=maxacti;i++){
        
        if (index % 2)              //formato
            printf("\e[48;5;236m"); //*
        else                        //*
            printf("\e[48;5;235m"); //formato

        Actividades *print= GetActividad(i,acti);
        printf("%-5i  %-5s\e[K\n",i,print->nombre);
        index++;//formato
    }
}

int PrintTurnActL(int indice){
    int index = 1;//formato
    int flag = 0;
    int sindex = MaxTurns(turnos);//cantidad de TURNS

    printf("\e[48;5;237m");                
    printf("%-5s | %-15s | %-5s | %-5s \e[K\n", "Index", "ACTIVIDAD","TURNO","CUPO");
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

    int maxTActi(Actividades *list){
            int cont = -1;
            while (list != NULL){
                cont++;
                list = list ->next;
            } 
            return cont;
        }
int MaxTurns(Turnos*list){
        int cont = -1;
        while (list != NULL){
            cont++;
            list = list ->next;
        } 
        return cont;
    }
