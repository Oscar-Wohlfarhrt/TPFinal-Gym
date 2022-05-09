#pragma once
#include "../tpstructs.h"

#define true 1
#define false 0

#define esc 27
#define enter 13
#define up 72
#define down 80
#define left 75
#define right 77


typedef struct actividad{
    char nombre[50];
    int cupo;
    int sucursal;
    Turnos turno;
    long profesorDNI;
    struct actividad *sgte;
}nActividad;
_Bool vacio(void **top);
_Bool isNumber(char *text);
_Bool eliminar_dato(nActividad **dato,nActividad **top);
nActividad *buscar_dato(nActividad **top,char *act);
nActividad *buscar_ant(nActividad **top,char *act);
int selector(int max, int acum);

/*void insertarActividad(nActividad **top){
    Actividades act;
    nActividad *n;
    struct tm horaInicio, horaFin;
    char diaIngresado[10], aux[5], *a,*b,*c;
    n = *top;
    fflush(stdin);
    scanf("%s", act.nombre);
    while((strcmp(act.nombre,(n)->nombre) != 0) && (n != NULL)){
        n = n->sgte; 
    }
    if(strcmp(act.nombre,(n)->nombre) == 0){
        //borrar
        system("cls");
        printf("\nActividad ya existente, puede modificarla pero no sobreescribirla\n");
        system("pause");
        return;
    }
    //borrar
    fflush(stdin);
    printf("\nIngrese el cupo: \n");
    scanf("%d", &act.cupo);
    fflush(stdin);
    printf("\nIngrese la sucursal: \n");
    scanf("%d", &act.sucursal);
    fflush(stdin);
    printf("\nPrimer turno:\n Dia:\n");
    fflush(stdin);
    scanf("%s", diaIngresado);
    fflush(stdin);
    tolower(&diaIngresado);
    while(strcmp(diaIngresado,"c") != 0){ //mientras no se ingrese un 0 en pantalla
        if(dia_a_num(diaIngresado) >= 0 && dia_a_num(diaIngresado) <= 6){
            printf("\nHorario de inicio(HH:MM): ");
            fflush(stdin);
            fgets(aux, sizeof(aux),stdin);
            a = strtok(aux,":");
            b = strtok(NULL, "");
            c = strtok(NULL, "");
            horaInicio.tm_hour = atoi(a);
            horaInicio.tm_min = atoi(b);
            printf("\nHorario de finalizado(HH:MM): ");
            fflush(stdin);
            fgets(aux, sizeof(aux),stdin);
            a = strtok(aux,":");
            b = strtok(NULL, "");
            c = strtok(NULL, "");
            horaFin.tm_hour = atoi(a);
            horaFin.tm_min = atoi(b);
            if(isNumber(&a) == false && isNumber(&b) == false) break;
            if(horaInicio.tm_hour >= horaFin.tm_hour){
                printf("\nHorario de inicio no puede ser mayor a horario de finalizacion\n");
                system("pause");
                continue;
            }
        }
        else{
            printf("\nDia invalido, ingrese un dia valido:\n");
        }
        //Turnos *FindTurn(struct tm time, Turnos *list); para pasarle el tiempo y la lista de turnos
        printf("\n");
        scanf("%s", diaIngresado);
    }
    if(strcmp(diaIngresado,"c") == 0 || 
    strcmp(aux,"c") == 0){
        return;
    }    
}*/
void insertar_actividad(nActividad **top){
    nActividad *nuevo;
    nuevo = (nActividad *)malloc(sizeof(nActividad));
    printf("Ingrese el nombre de la actividad: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre),stdin);
    strtok(nuevo->nombre,"\n");
    printf("\nIngrese el cupo: ");
    fflush(stdin);
    scanf("%d", &nuevo->cupo);
    printf("\nIngrese la sucursal: ");
    fflush(stdin);
    scanf("%d", &(nuevo->sucursal));
    if(nuevo->sucursal > 2) return;
    printf("\nHorario de ingreso: ");
}
void ABMACTA(){
    char menu[4][24] = {"ABM ACTIVIDADES\n",
    "  Insertar actividad\n",
    "  Eliminar actividad\n",
    "  Modificar actividad\n"},menucpy[4][24];
    char ch;
    int aux = 1,ant = 1;
    memcpy(&menucpy[0],&menu[0],sizeof(menu));
    while(1 == 1){
        system(cls);
        do{
            menu[aux][0] = '>';
            fputs(strcat(strcat(strcat(menu[0],menu[1]),menu[2]),menu[3]),stdout);
            ant = aux;
            aux = selector(3,aux);
            memcpy(&menu[0],&menucpy[0],sizeof(menu));
            fflush(stdout);
            system("cls");
            //printf("%i",aux);
        }while(aux != 4 && aux != -1);
        if(aux == -1) return;
        switch(ant){
            case 1:
                system(cls);
                printf("1");     
                system("pause");       
            break;

            case 2:
                system(cls);
                printf("2");    
                system("pause");
            break;

            case 3:
                system(cls);
                printf("3");
                system("pause");
            break;

            default:
                return;
            break;
        }
    }
}
void apilar2(nActividad **dato, nActividad **top){
    (*dato)->sgte = *top;
    *top = *dato;
    *dato = NULL;
}
void desapilar2(nActividad **dato, nActividad **top){
    *dato = *top;
    *top = (*top)->sgte;
}
_Bool vacio(void **top){
    if ((*top) == NULL){
        return true;
    }
    return false;
}
void pasaje(void **p, void *rc, size_t tam){
    nActividad *nuevo = (nActividad*)malloc(sizeof(nActividad));
    memcpy(nuevo,rc,tam);
    nuevo->sgte = NULL;
    *p = nuevo;
}
_Bool isNumber(char *text){
    int j;
    j = strlen(text);
    while(j--){
        if(text[j] >= '0' && text[j] <= '9') continue;
        return false;
    }
    return true;
}
int dia_a_num(char *texto){
    if(strcmp(texto,"domingo")==0) return 0;
    else if(strcmp(texto,"lunes")==0) return 1;
    else if(strcmp(texto,"martes")==0) return 2;
    else if(strcmp(texto,"miercoles")==0) return 3;
    else if(strcmp(texto,"jueves")==0) return 4;
    else if(strcmp(texto,"viernes")==0) return 5;
    else if(strcmp(texto,"sabado")==0) return 6;
    return -1;
}
void imprimir_actividades(nActividad **top){
    nActividad *aux;
    aux = *top;
    while(aux != NULL){
        printf("%s %i %i %i %i %i %i\n",aux->nombre,aux->cupo,aux->sucursal,aux->turno.horarioInicio.tm_hour,aux->turno.horarioInicio.tm_min,aux->turno.horarioFin.tm_hour,aux->turno.horarioFin.tm_min);
        aux = aux->sgte;
    }
}
void apilar_de_fichero(nActividad **top, size_t *tamano, char *nombre_fichero){
    FILE *fichero;
    fichero = fopen(nombre_fichero, "rb");
    if(fichero == NULL){
        while(!feof(fichero)){
            nActividad  *nodo = (nActividad  *)malloc(sizeof(nActividad));
            fread(nodo, (size_t)tamano, 1, fichero);
            if(feof(fichero))break;
            nodo->sgte = *top;
            *top = nodo;
            nodo = NULL;
        }
    }
    fclose(fichero);
}
void escribir_en_fichero(nActividad **top, size_t *tamano, char *nombre_fichero){
    nActividad *aux = NULL,*tp2 = NULL,*tope = *top;
    FILE *fichero;
    fichero = fopen(nombre_fichero, "wb");
    if(fichero == NULL){
        fclose(fichero);
        return;
    }
    while(!vacio(&tope)){
        desapilar2(&aux,&tope);
        apilar2(&aux,&tp2);
    }
    while(!vacio(&tp2)){
        desapilar2(&aux,&tp2);
        fwrite(aux, (size_t)tamano, 1, fichero);
        apilar2(&aux,&tope);
    }
    fclose(fichero);
}
nActividad *buscar_dato(nActividad **top,char *act){
    nActividad *aux = *top;
    while(aux != NULL){
        if(strcmp(aux->nombre,act)==0) return aux;
        aux = aux->sgte;
    }
    return NULL;
}
nActividad *buscar_ant(nActividad **top,char *act){
    nActividad *aux = *top,*ant;
    while(aux != NULL){
        if(strcmp(aux->nombre,act)==0) return ant;
        ant = aux;
        aux = aux->sgte;
    }
    return NULL;
}
_Bool eliminar_dato(nActividad **dato,nActividad **top){
    nActividad *aux = *top,*ant = NULL;
    while(vacio(&aux) != true){
        if(*dato == *top && aux == *top && ant == NULL){
            *top = aux->sgte;
            free(aux);
            return true;
        }
        else if(aux == *dato){
            ant->sgte = aux->sgte;
            free(aux);
            return true;
        }
        ant = aux;
        aux = aux->sgte;
    }
    return false;
}
int selector(int max, int acum){
    int i = acum;
    fflush(stdin);
    _sleep(10);
    switch(getch()){
        case up:
            i--;
        break;
        case down:
            i++;
        break;
        case enter:
            return (max+1);
        break;
        case esc:
            return -1;
        break;
    }
    if(i == 0) i = max;
    if(i > max) i = 1;
    return i;
}
#pragma endregion