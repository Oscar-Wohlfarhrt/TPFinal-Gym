#ifndef _strext
#define _strext
#include <string.h>
#include <ctype.h>

#ifdef __unix__
char *strlwr(char *text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
    }
    return text;
}

char *strupr(char *text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }
    return text;
}
#endif
#endif