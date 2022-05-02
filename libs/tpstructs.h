#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../libs/cmenus.h"

struct Clientes;
typedef struct Clientes Clientes;
struct Profesores;
typedef struct Profesores Profesores;
struct Turnos;
typedef struct Turnos Turnos;
struct Actividades;
typedef struct Actividades Actividades;
struct ClientesActivTurno;
typedef struct ClientesActivTurno ClientesActivTurno;
struct ClientesPagos;
typedef struct ClientesPagos ClientesPagos;
struct Reservas;
typedef struct Reservas Reservas;

struct Clientes{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct tm fechaNacimiento;
    struct tm ultimaActividad;
    struct tm fechaBaja;
    Clientes *next;
};

struct Profesores{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct Profesores *next;
};

struct Turnos{
    char dias;
    struct tm horarioInicio;
    struct tm horarioFin;
    struct Turnos *next;
};

struct Actividades{
    char nombre[50];
    int cupo;
    int sucursal;
    Turnos turno;
    long profesorDNI;
    struct Actividades *next;
};

struct ClientesActivTurno{
    long dni;
    char actividad[50];
    struct ClientesActivTurno *next;
};

struct ClientesPagos{
    long dni;
    float monto;
    struct tm fechaEmision;
    struct tm fechaPago;
    struct ClientesPagos *next;
};

struct Reservas{
    long dni;
    char actividad[50];
    struct Reservas *next;
};