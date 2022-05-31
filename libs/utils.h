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
double minDifftime(struct tm t1,struct tm t2){
    time_t timeA, timeB;
    struct tm tA, tB, *tptr;
    double diff;

    time(&timeA);
    time(&timeB);
    tptr = localtime(&timeA);
    tA = *tptr;
    tptr = localtime(&timeB);
    tB = *tptr;

    tA.tm_mday = 0;
    tA.tm_mon = 0;
    tA.tm_year = 100;
    tA.tm_hour = t1.tm_hour;
    tA.tm_min = t1.tm_min;
    tA.tm_sec = 0;

    tB.tm_mday = 0;
    tB.tm_mon = 0;
    tB.tm_year = 100;
    tB.tm_hour = t2.tm_hour;
    tB.tm_min = t2.tm_min;
    tB.tm_sec = 0;

    return difftime(mktime(&tA), mktime(&tB))/60;
}

int betweenTime(struct tm time, struct tm min, struct tm max){
    int err=0;
    if(minDifftime(time,min)>=0 && minDifftime(max,time)>=0){
        err=1;
    }
    return err;
}

int dayOfWeek(struct tm time){
    int day=time.tm_mday;
    int mon=time.tm_mon+1;
    long year=time.tm_year+1900;

    return ((day += mon<3?year--:year-2),(23*mon/9+day+4+year/4-year/100+year/400))%7;
}
int weekOfYear(struct tm time){
    return (time.tm_yday+6-time.tm_wday)/7;
}