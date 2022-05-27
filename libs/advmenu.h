#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define key_escape 27
#define key_enter 13
#define key_up 327
#define key_left 330
#define key_right 332
#define key_down 335

#ifdef __unix__
    #define cls "clear"
#else
    #define cls "cls"
#endif

char **_menus,*_defFormat,*_opFormat,*_defFormatEnd,*_opFormatEnd;

short getKeyCode();
void setAdvMenus(char **menus);
void setAdvFormats(char *defFormat,char *opFormat,char *defFormatEnd,char *opFormatEnd);
void advMenu(int menuIndex,void (*userFuncs[])(void),int opCount);
void printAdvMenu(char *fmenu,int op);

short getKeyCode(){
    short c = getch();

    if (c==224){
        char c2 = getch();
        c=255+c2;
    }
    return c;
}
void setAdvMenus(char **menus)
{
    _menus=menus;
}
void setAdvFormats(char *defFormat,char *opFormat,char *defFormatEnd,char *opFormatEnd){
    _defFormat=defFormat;
    _opFormat=opFormat;
    _defFormatEnd=defFormatEnd;
    _opFormatEnd=opFormatEnd;
}
void advMenu(int menuIndex,void (*userFuncs[])(void),int opCount){
    int err=1,op=0;
    while(err){
        printf("\e[?25l");//esconde el cursor
        system(cls);

        printAdvMenu(_menus[menuIndex],op);
        int key=getKeyCode();
        
        if( key == key_up && op){
            op--;
        }
        else if(key==key_down && op<opCount){
            op++;
        }
        else if(key==key_enter && op<opCount){
            printf("\e[?25h");//muestra el cursor
            userFuncs[op]();
        }
        else if(key==key_enter && op==opCount){
            err=0;
        }
        else if(key==key_escape){
            err=0;
        }
    }
    printf("\e[?25h");//muestra el cursor
}
void printAdvMenu(char *fmenu,int op){
    char *pos = fmenu,*end;

    end=strstr(fmenu,"<o>");

    while(pos<end){
        printf("%c",*pos);
        pos++;
    }

    pos=strstr(fmenu,"<o>");
    if(pos){
        pos+=3;
        end=strstr(pos,"</o>");
    }
    
    while(pos && end){
        if(!op)
            printf(_opFormat);
        else
            printf(_defFormat);

        while(pos<end){
            printf("%c",*pos);
            pos++;
        }

        if(!op)
            printf(_opFormatEnd);
        else
            printf(_defFormatEnd);

        op--;

        pos=strstr(end,"<o>");
        if(pos){
            end+=4;
            while(end<pos){
                printf("%c",*end);
                end++;
            }
            pos+=3;
            end=strstr(pos,"</o>");
        }
    }

    if(pos){
        while(pos<fmenu+strlen(fmenu)){
            printf("%c",*pos);
            pos++;
        }
    }

    if(end){
        end+=4;
        while(end<fmenu+strlen(fmenu)){
            printf("%c",*end);
            end++;
        }
    }
}