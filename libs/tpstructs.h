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
struct ActTurno;
typedef struct ActTurno ActTurno;
struct ClientesPagos;
typedef struct ClientesPagos ClientesPagos;
struct Reservas;
typedef struct Reservas Reservas;
struct Asistencia;
typedef struct Asistencia Asistencia;

struct Clientes{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct tm fechaNacimiento;
    struct tm ultimaActividad;
    struct tm fechaBaja;
    struct Clientes *next;
};

struct Profesores{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct Profesores *next;
};

struct Turnos{
    long actividad;
    int dias;
    struct tm horarioInicio;
    struct tm horarioFin;
    long prof;
    int cupo;
    struct Turnos *next;
};

struct Actividades{
    char nombre[50];
    int sucursal;
    struct Actividades *next;
};

struct ActTurno{
    long dni;
    int turno;
    long cliente;
    struct ActTurno *next;
};

struct ClientesPagos{
    long actturn;
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

struct Asistencia{
    long actturn;
    struct tm fecha;
};