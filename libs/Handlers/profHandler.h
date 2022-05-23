#pragma once
#include "../tpstructs.h"
#include "sim.h"

Profesores *profes = NULL;

/*
	typedef struct Profesores{
	    char nombre[50];
	    char apellido[50];
	    long dni;
	    char telefono[20];
	    struct Profesores *next;
	}Profesores;
*/

void SaveProf(Profesores *ini);
void LoadProf(Profesores **ini);
void PrintMenu();
Profesores *Find(long dato,Profesores *ini);
Profesores InsertP(Profesores**node,Profesores**ini);//Inster at the end
Profesores  *standarAdd();
void PrintList(Profesores*ini);//aux text
int ReplaceP(Profesores **node,Profesores **ini);
Profesores *buscarAnterior(long dato,Profesores *ini);
int flagRemove(long dato,Profesores *ini);
int RemoveP(Profesores node,Profesores **ini);
Profesores *GetProf(int index, Profesores *ini);

void PrintMenu(){
	int a;
	Profesores *start=NULL,*nodeNew=NULL;
	do{
		system("pause");
		system("cls");
		printf("1.Insert at end\n");
		printf("2.Remove Node\n");
		printf("3.Print List Prof\n");
		printf("4.Replace\n");
		printf("5.Find Prof\n");
		printf("6.Load\n");
		printf("7.Save\n");
		printf("11.Random add\n");
		printf("0.Exit\n");
		scanf("%d",&a);
		fflush(stdin);
		switch (a)
		{
		case 1:
				nodeNew = standarAdd();
				system("cls");
				InsertP(&nodeNew,&start);
			break;
		case 2:
			printf("hola mundo");
			break;
		case 3:
			PrintList(start);
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			
			break;
		case 7:
			
			break;
		case 0:
			
			break;
		case 11:
			for(int i =0 ;i<4;i++){ //generate a random values
				nodeNew = (struct Profesores*)malloc(sizeof(struct Profesores));
				ranstr(10,(nodeNew)->nombre);
				ranstr(10,(nodeNew)-> apellido);
				(nodeNew)->dni = (long)aran(10,200);
				ranstr(10,(nodeNew)-> telefono);
				InsertP(&nodeNew,&start);
				free(nodeNew);
			}
			break;
		default:
			printf("Try again\n");
			break;
		}	
	}while(a > 1);
}

Profesores *Find(long dato,Profesores *ini){
	while (ini != NULL){
		if(ini->dni == dato){
			PrintList(ini);
			break;
		}
		else{
			ini=ini->next;
		}
	}
	return ini;
}

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
	printf("Ingrese dni: \n");
	scanf("%ld",&nodeNew->dni);
		fflush(stdin);
	printf("Ingrese nombre: \n");
	fgets(nodeNew->nombre, 50, stdin);
		fflush(stdin);
	printf("Ingrese apellido: \n");
	fgets(nodeNew->apellido, 50, stdin);
		fflush(stdin);
	printf("Ingrese telefono: \n");
	fgets(nodeNew->telefono, 50, stdin);
		fflush(stdin);
	return nodeNew;
	printf("si");
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

int RemoveP(Profesores node,Profesores **ini){
	long dato=node.dni;
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
		printf("No se ha encontrado el node a borrar\n");
	}
	return flag;
}

void SaveProf(Profesores *ini){
	FILE*f;
	if((f = fopen("profRecords.bin","wb") )!=NULL){
		while (ini != NULL){
			fread(ini,sizeof(Profesores),1,f);
			ini = ini-> next;
		}
		fclose(f);
	}
}

void LoadProf(Profesores **ini){
	FILE*f;
	if((f = fopen("profRecords.bin","rb"))!=NULL){
		Profesores *temp=(Profesores*)malloc(sizeof(Profesores));
		fread(temp,sizeof(Profesores),1,f);
	
		while (!feof(f)){
			InsertP(&temp,ini);
			Profesores *temp=(Profesores*)malloc(sizeof(Profesores));
			fread(temp,sizeof(Profesores),1,f);
		}
		free(temp);
		fclose(f);
	}
}

Profesores *GetProf(int index, Profesores *ini){
    if (index >= 0){
        while (ini != NULL && index > 0){
            ini = ini->next;
            index--;
        }
    }
    else
        ini = NULL;

    return ini;
}