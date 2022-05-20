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

void LoadP();
Profesores InsertP(Profesores**node,Profesores**ini);//Inster at the end
Profesores  *standarAdd();
void PrintList(Profesores*ini);//aux text
int ReplaceP(Profesores **node,Profesores **ini);
Profesores *buscarAnterior(long dato,Profesores *ini);
int flagRemove(long dato,Profesores *ini);
int RemoveP(long dato,Profesores **ini);


Profesores InsertP(Profesores**node,Profesores**ini){
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

Profesores *standarAdd(){
	Profesores *nodeNew = (struct Profesores*)malloc(sizeof(struct Profesores));

	printf("Ingrese nombre: \n");
	gets(nodeNew->nombre);
	printf("Ingrese apellido: \n");
	gets(nodeNew->apellido);
	printf("Ingrese telefono: \n");
	gets(nodeNew->telefono);
	printf("Ingrese dni: \n");
	scanf("%ld",&nodeNew->dni);

	return nodeNew;
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

int ReplaceP(Profesores **node,Profesores **ini){
	int flag=0;
	while((*ini) != NULL){
		if((*ini)->dni == (*node)->dni){
			printf("procesar texto");//funcion de procesar
			flag=1;
			break;
		}
		else{
			*ini = (*ini) -> next;
		}
	}
	return flag;
}

int flagRemove(long dato,Profesores *ini){
	int flag = 0;
	while(ini != NULL){
		if(((ini)->dni) == dato){
			flag = 1;
			break;
		}
		else{
			anterior = ini;
			ini = (ini) -> next;
		}
	}
	return flag;
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

int RemoveP(long dato,Profesores **ini){
	Profesores *anterior= buscarAnterior(dato,(*ini));
	Profesores *bor = *ini;
	int flag = flagRemove(dato,(*ini));
	if(flag != 0){
		if(anterior != NULL){
			bor = anterior->next;
			anterior -> next = bor-> next;
			bor -> next = NULL;
			free(bor);
		}
		else{
			free(bor);
		}
	}
	else{
		printf("No se ha encontrado el node a borrar");
	}
	return flag;
}

