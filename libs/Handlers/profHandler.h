#pragma once
#include "../tpstructs.h"
//#include "sim.h"

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
//debug tool
void PrintList(Profesores*ini);//aux text

//functions
void SaveProf(Profesores *ini);
void LoadProf(Profesores **ini);
void BorrarListaProfesores(Profesores **list);
Profesores *FindProf(long node,Profesores *ini);//R
Profesores InsertP(Profesores**node,Profesores**ini);//R
int ReplaceP(Profesores **node,Profesores **ini);
int RemoveP(Profesores node,Profesores **ini);//R
Profesores *GetProf(int index, Profesores *ini);
Profesores *FindLastProf(Profesores node, Profesores *ini);


Profesores *FindProf(long node,Profesores *ini){
	if(ini){
		if(ini->dni != node){
			ini=FindProf(node,ini->next);
		}
	}
    return ini;
}

Profesores InsertP(Profesores**node,Profesores**ini){
	(*node)-> next = NULL;
	if(*ini == NULL) {
		*ini = *node;
	}
	else if((*ini)->next == NULL){ 
		(*ini)->next = *node;	
	}
	else InsertP(node,&(*ini)->next);

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

int RemoveP(Profesores node,Profesores **ini){
	int flag=0;
	if(*ini != NULL){
		if(node.dni == (*ini)->dni){
			Profesores *aux = *ini;
			*ini = (*ini)->next;
			aux = NULL;
			free(aux);
			flag=1;
		}else if(node.dni == (*ini)->next->dni){
			Profesores *aux = (*ini)->next;
			(*ini)->next = (*ini)->next->next;
			aux->next = NULL;
			free(aux);
			flag=1;
		}else{
			RemoveP(node,&(*ini)->next);
		}
	}
	return flag;
}

void SaveProf(Profesores *ini){
	FILE *f;
    if (f = fopen("profRecords.bin", "wb")){
        while (ini){
            fwrite(ini, sizeof(Profesores), 1, f);
            ini = ini->next;
        }
        fclose(f);
    }
}

void LoadProf(Profesores **ini){
	FILE *f;
    if (f = fopen("profRecords.bin", "rb")) {
        Profesores *node = (Profesores *)malloc(sizeof(Profesores));
        fread(node, sizeof(Profesores), 1, f);
        while (!feof(f)){
            InsertP(&node, ini);
            node = (Profesores *)malloc(sizeof(Profesores));
            fread(node, sizeof(Profesores), 1, f);
        }
        free(node);
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
    else ini = NULL;

    return ini;
}
void BorrarListaProfesores(Profesores **list)
{
    Profesores *aux = NULL;
    while (*list)
    {
        aux = *list;
        *list = (*list)->next;
        aux->next = NULL;
        free(aux);
    }
}