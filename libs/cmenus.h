#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strext.h"

#ifdef __unix__
#define cls "clear"
#else
#define cls "cls"
#endif
/*
* cls se puede usar de la siguiente manera:
* system(cls);
* para limpiar la pantalla en linux y windows por igual
*/


char **_cmenus, *_crequest, *_cerror;

void SetCurPos(int XPos, int YPos);
void ClearConsole();
void setMenus(char *menus[], char request[], char error[]);
void showMenu(int type, int err);
int promptMenu(int type, int err);
int fullMenu(int type, int *err, void (*funcs[])(void), int count);

//funcion para limpiar la consola con codigos ANSI
void ClearConsole(){
    printf("\e[2J\e[H");
}

void SetCurPos(int XPos, int YPos)
{
    printf("\033[%d;%dH", YPos + 1, XPos + 1);//printf("\033[%d;%dH", (y), (x)) sacado de internet
}

void setMenus(char *menus[], char request[], char error[])
{
    _cmenus = menus;
    _crequest = request;
    _cerror = error;
}

void showMenu(int type, int err)
{    printf("%s", _cmenus[type]);

    printf("\n%s", _crequest);
    printf("\e7");

    if (err)
    {
        printf("\n%s", _cerror);
        printf("\e8");
    }
}

int promptMenu(int type, int err)
{
    int option = 0;
#ifndef not_clean_screen
    system(cls);
#endif
    showMenu(type, err);
    scanf("%i", &option);
    fseek(stdin, 0, SEEK_END); // se limpia el buffer de entrada
    printf("\n");
    return option;
}

int fullMenu(int type, int *err, void (*funcs[])(void), int count)
{
    int option, run = 1;
    option = promptMenu(type, *err);
    (*err) = 0;
    if (option > 0 && option <= count)
    {
        funcs[option - 1]();
    }
    else if (option == count + 1)
    {
        run = 0;
    }
    else
    {
        (*err) = 1;
    }

    return run;
}
int TryToInt32(char *str, int *out)
{
    if(!str)
        return 0;
    
    int length=strlen(str);
    for (int i = 1; i < 256; i++)
    {
        if ((((char)i) >= 48 && ((char)i) <= 57) || ((char)i) == '-')
        {
        } //rango ascii de numeros enteros
        else
        {
            for (int j = 0; j < length; j++)
            {
                if (str[j] == (char)i)
                    return 0;
            }
        }
    }

    *out = atoi(str);
    return 1;
}
int TryToInt64(char *str, long *out)
{
    if(!str)
        return 0;
    
    int length=strlen(str);
    for (int i = 1; i < 256; i++)
    {
        if ((((char)i) >= 48 && ((char)i) <= 57) || ((char)i) == '-')
        {
        } //rango ascii de numeros enteros
        else
        {
            for (int j = 0; j < length; j++)
            {
                if (str[j] == (char)i)
                    return 0;
            }
        }
    }
    *out = atol(str);
    return 1;
}
int TryToFloat(char *str, float *out)
{
    if(!str)
        return 0;
    
    int length=strlen(str);
    for (int i = 1; i < 256; i++)
    {
        if ((((char)i) >= 48 && ((char)i) <= 57) || ((char)i) == '-' || ((char)i) == '.')
        {
        } //rango ascii de numeros enteros
        else
        {
            for (int j = 0; j < length; j++)
            {
                if (str[j] == (char)i)
                    return 0;
            }
        }
    }

    *out = atof(str);
    return 1;
}