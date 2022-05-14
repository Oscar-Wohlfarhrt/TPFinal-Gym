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
Profesores insterProf(Profesores**node,Profesores**ini);//Inster at the end
void PrintList(Profesores*ini);//aux text
Profesores ModificarProf(long dato,Profesores **ini);
Profesores *buscarAnterior(long dato,Profesores *ini);	
Profesores elminarProf(long dato,Profesores **ini);


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

void PrintList(Profesores*ini){
	while (ini!=NULL)
	{
		printf("-----------------------------------------\n");
		printf("%s %s\n",(ini)->nombre,(ini)-> apellido);
		printf("%i %s\n",(ini)->dni,(ini)-> telefono);
		printf("-----------------------------------------\n");
		ini = (ini)->next;
	}
	
}

Profesores ModificarProf(long dato,Profesores **ini){
	while((*ini) != NULL){
		if(((*ini)->dni) == dato){
			printf("procesar texto");
			break;
		}	
		else{		
			*ini = (*ini) -> next;
		}
	}
}

Profesores *buscarAnterior(long dato,Profesores *ini){
	Profesores *anterior = NULL;
	while(ini != NULL){
		if(((ini)->dni) == dato){
			break;
		}	
		else{
			anterior = ini;
			ini = (ini) -> next;
		}
	}
	return anterior;
}

Profesores elminarProf(long dato,Profesores **ini){
	Profesores *anterior= buscarAnterior(dato,(*ini));
	if(anterior != NULL){
		*ini = anterior->next;
		anterior -> next = (*ini )-> next;
		(*ini) -> next = NULL;
		free(*ini);
	}
	else{
		free(*ini);
	}
}