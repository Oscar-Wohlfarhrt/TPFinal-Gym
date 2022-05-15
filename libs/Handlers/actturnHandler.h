#pragma once
#include "../tpstructs.h"
void load_ActTurn(ActTurno **p);
void save_ActTurn(ActTurno **p);
void insert_Turno(ActTurno **dato,ActTurno **top);//APILA
_Bool remove_ActTurn(int turno,ActTurno **p);
_Bool replace_ActTurn(int turno,ActTurno *new, ActTurno **top);
ActTurno *get_ActTurn(int index,ActTurno **top);
ActTurno *find_ActTurn(int turno,ActTurno **top);
void load_ActTrun(ActTurno **p){
    FILE *f = fopen("ActTurn.dat","rb");
    if(f){
        while(!feof(f)){
            ActTurno *aux = (ActTurno*)malloc(sizeof(ActTurno));
            if(!aux) break;
            fread(aux,sizeof(ActTurno),1,f);
            if(feof(f)){
                free(aux);
                break;
            }
            if(!*p){
                *p = aux;
                aux->next = NULL;
            }else{
                aux->next = *p;
                *p = aux;
            }
        }
    }
}
void save_ActTrun(ActTurno **p){
    FILE *f = fopen("ActTurn.dat","wb");
    if(f){
        ActTurno *aux = *p;
        while(aux){
            fwrite(aux,sizeof(ActTurno),1,f);
            aux = aux->next;
        }
    }
}
void insert_Turno(ActTurno **dato,ActTurno **top){//apila
    if(!*dato) return;
    (*dato)->next = *top;
    *top = *dato;
    *dato = NULL;
}
_Bool remove_ActTurn(int turno,ActTurno **top){
    ActTurno *aux = *top,*ant = NULL;
    while(aux){
        if(aux->turno == turno){
            (!ant) ? *top = aux->next : ant->next = aux->next;
            free(aux);
            return true;
        }
        ant = aux;
        aux = aux->next;
    }
    return false;
}
_Bool replace_ActTurn(int turno,ActTurno *new, ActTurno **top){
    ActTurno *aux = *top,ant = NULL;
    while(aux){
        if(turno == aux->turno){
            (!ant) ? *top = new : ant->next = new;
            new->next = aux->next;
            free(aux);
            return true;
        }
        ant = aux;
        aux = aux->next;
    }
    return false;
}
ActTurno *get_ActTurn(int index,ActTurno **top){
    ActTurno *aux = *top;
    if(!*top) return NULL;
    for(int i = 0; i <= index; i++){
        if(i == index) return aux;
        if(i <= index && !aux) return NULL;
        aux = aux->next;
    }
    return NULL;
}
ActTurno *find_ActTurn(int turno,ActTurno **top){
    ActTurno *aux = *top;
    while(aux){
        if(aux->turno == turno) return aux;
        aux = aux->next;
    }
    return NULL;
}
#pragma endregion