#pragma once
#include <time.h>

typedef struct Clientes{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct tm fechaNacimiento;
    struct tm ultimaActividad;
    struct tm fechaBaja;
    struct Clientes *next;
}Clientes;

typedef struct Profesores{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct Profesores *next;
}Profesores;

typedef struct Actividades{
    char nombre[50];
    int cupo;
    int sucursal;
    int turno;
    long profesorDNI;
    struct Actividades *next;
}Actividades;

typedef struct Turnos{
    int dias[7];
    struct tm horarioInicio;
    struct tm horarioFin;
    struct Turnos *next;
}Turnos;

typedef struct ClientesActivTurno{
    long dni;
    char actividad[50];
    struct ClientesActivTurno *next;
}ClientesActivTurno;

typedef struct ClientesPagos{
    long dni;
    float monto;
    struct tm fechaEmision;
    struct tm fechaPago;
    struct ClientesPagos *next;
}ClientesPagos;

typedef struct Reservas{
    long dni;
    char actividad[50];
    struct Reservas *next;
}Reservas;