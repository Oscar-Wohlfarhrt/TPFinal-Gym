#pragma once
#include "../tpstructs.h"

FILE *f;

#define true 1
#define false 0

char cabeceras[5][16] = {"Actividad", "Cupo", "Sucursal", "Turno", "Profesor"};


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

void insertarActividad(nActividad **top){
    Actividades act;
    nActividad *n;
    struct tm horaInicio, horaFin;
    int i;
    char dias[7][10] = {
    "domingo",
    "lunes",
    "martes",
    "miercoles",
    "jueves",
    "viernes",
    "sabado"};
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
    tolower(diaIngresado);
    while(strcmp(diaIngresado,"c") != 0){ //mientras no se ingrese un 0 en pantalla
        if(strcmp(diaIngresado,dias[0])==0 || 
        strcmp(diaIngresado,dias[1])==0 || 
        strcmp(diaIngresado,dias[2])==0 || 
        strcmp(diaIngresado,dias[3])==0 || 
        strcmp(diaIngresado,dias[4])==0 || 
        strcmp(diaIngresado,dias[5])==0 || 
        strcmp(diaIngresado,dias[6])==0){
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

}

/*void cargarAct(){
    Actividades act;
    int i = 0;
    char actividades[4][16] = {"Complementos", "Ciclismo int.", "Funcional", "Crossfit"};
    f = fopen("actividades.dat", "ab");
    if(f != NULL){


    }
    fclose(f);
    printf("terminado");
}*/

/*void altaAct(Clientes usuario, Actividades actividad){
    Actividades act;
    nActividad *p,*aux,*aux2;
    f = fopen("actividades.dat", "rb");
    if(f != NULL){
        fread(&act, sizeof(Actividades), 1, f);
        pasaje(&p, &act,sizeof(act));
        apilar(&p,&aux);
    }else{
        system("cls");
        system("color 04");
        printf("ERROR.NO SE ENCUENTRA EL ARCHIVO\n\n");
        system("pause");
        system("color F");
        fclose(f);
        return;
    }
    if(ftell(f) == 0) return;
    fclose(f);
    while(vacio(aux) != true){
        desapilar2(&p,&aux);
        if(strcmp(p->nombre,actividad.nombre)==0 && p->sucursal == actividad.sucursal && p->turno == actividad.turno && p->cupo > 0){
            f = fopen("clientActTurn.dat", "rb+");
            if(f != NULL){
                fread(&act, sizeof(Actividades), 1, f);
                pasaje(&p, &act,sizeof(act));
                apilar(&p,&aux2);
            }
        }
        apilar2(&p,&aux2);
    }
    fclose(f);
}*/

void ABMACTA(){
    int in;
    while(1 == 1){
        system("cls");
        printf("Configurar las actividades\n");//Aca tendria que estar la parte de la interfaz grafica;
        printf("1. Modificar actividad\n");
        printf("2. Ver actividades\n");
        printf("3. Volver\n");
        fflush(stdin);
        scanf("%d",&in);
        switch(in){
            case 1:
                //modificarAct();
            break;

            case 2:
                verAct();
            break;

            default:
                return;
            break;
        }
    }
    printf("\nSe salio de la ejecucion del programa");
}

void verAct(){
    _Bool empty;
    nActividad *p,*aux;
    int select = 0,iC = 0;
    Actividades act;
    p = NULL;
    aux = NULL;
    empty = false;
    system("cls");
    f = fopen("actividades.dat","rb+");
    printf("\e[48;5;237m\t\t\t ACTIVIDADES\e\n");//Esto hay que sacar
    if(f != NULL){
        printf(" %.12s|%.5s|%.8s|%.5s|%.10s\n", cabeceras[0], cabeceras[1], cabeceras[2], cabeceras[3], cabeceras[4]);//esto hay que sacar
        while(!feof(f)){
            fread(&act, sizeof(Actividades), 1, f);
            if(feof(f)) break;
            if(ftell(f)==0) empty = true;
            (iC%2==0)?printf("\e[48;5;236m"):printf("\e[48;5;235m");
            if(empty == false){
                pasaje(&p,&act,sizeof(Actividades));
                apilar2(&p,&aux);
                printf("%.12s|%i|%1i|%1i|%ld\n",aux->nombre, aux->cupo, aux->sucursal,aux->turno,aux->profesorDNI);
                iC = iC + 1;
            }
        }
        printf("\e[0m");
    }else{
        printf("No se pudo abrir el archivo\n");
        system("pause");
        return;
    }
    desapilar2(&p,&aux);
    printf("%.12s|%i|%1i|%1i|%ld\n",p->nombre, p->cupo, p->sucursal,p->turno,p->profesorDNI);
    desapilar2(&p,&aux);
    printf("%.12s|%i|%1i|%1i|%ld\n",p->nombre, p->cupo, p->sucursal,p->turno,p->profesorDNI);
    system("pause");
}


void apilar2(nActividad **dato, nActividad **top){
    (*dato)->sgte = *top;
    *top = *dato;
}

void desapilar2(nActividad **top, nActividad **dato){
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
    int ndia;
    if(strcmp(texto,"domingo")==0) ndia = 0;
    else if(strcmp(texto,"lunes")==0) ndia = 1;
    else if(strcmp(texto,"martes")==0) ndia = 2;
    else if(strcmp(texto,"miercoles")==0) ndia = 3;
    else if(strcmp(texto,"jueves")==0) ndia = 4;
    else if(strcmp(texto,"viernes")==0) ndia = 5;
    else if(strcmp(texto,"sabado")==0) ndia = 6;
    return ndia;
}


#pragma endregion