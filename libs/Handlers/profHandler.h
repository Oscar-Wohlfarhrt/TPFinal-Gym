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

void SaveProf(Profesores *ini);
void LoadProf(Profesores **ini);
Profesores *Find(long dato,Profesores *ini);
Profesores InsertP(Profesores**node,Profesores**ini);//Inster at the end
void PrintList(Profesores*ini);//debug tool
int ReplaceP(Profesores **node,Profesores **ini);
Profesores *buscarAnterior(long dato,Profesores *ini);
int flagRemove(long dato,Profesores *ini);
int RemoveP(Profesores node,Profesores **ini);
Profesores *GetProf(int index, Profesores *ini);
Profesores *FindLastProf(Profesores node, Profesores *ini);



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
    else
        ini = NULL;

    return ini;
}