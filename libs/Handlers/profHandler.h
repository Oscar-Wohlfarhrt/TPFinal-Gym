#pragma once
#include "../tpstructs.h"

/*
	typedef struct Profesores{
	    char nombre[50];
	    char apellido[50];
	    long dni;
	    char telefono[20];
	    struct Profesores *next;
	}Profesores;
*/
Profesores insterProf(Profesores**node,Profesores**ini);

Profesores insterProf(Profesores**node,Profesores**ini){
	Profesores *ant;
	ant = *ini;
	int flag = 0;
	while(ant!=NULL && flag == 0) {
		if(((ant)->next )== NULL){
			flag =1;
		}
		else{
			ant = (ant)->next;
		}
	}

	if(ant == NULL){
		*ini = *node;
		(*ini)->next =NULL;
	}
	else{
		(ant)->next = *node;
		(ant)->next->next =NULL;
	}
	*node = NULL;
}
