#pragma once

#include <time.h>

int dayDifftime(struct tm t1,struct tm t2){
    time_t timeA, timeB;
    struct tm tA, tB, *tptr;
    double diff;

    time(&timeA);
    time(&timeB);
    tptr = localtime(&timeA);
    tA = *tptr;
    tptr = localtime(&timeB);
    tB = *tptr;

    tA.tm_mday = t1.tm_mday;
    tA.tm_mon = t1.tm_mon;
    tA.tm_year = t1.tm_year;

    tB.tm_mday = t2.tm_mday;
    tB.tm_mon = t2.tm_mon;
    tB.tm_year = t2.tm_year;

    return (int)(difftime(mktime(&tA), mktime(&tB))/86400);
}