#include <time.h>

typedef struct Clientes{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
    struct tm fechaNacimiento;
    struct tm ultimaActividad;
    struct tm fechaBaja;
}Clientes;

typedef struct Profesores{
    char nombre[50];
    char apellido[50];
    long dni;
    char telefono[20];
}Profesores;

typedef struct Actividades{
    char nombre[50];
    int cupo;
    int sucursal;
    int turno;
    long profesorDNI;
}Actividades;

typedef struct Turnos{
    int dias[7];
    struct tm horarioInicio;
    struct tm horarioFin;
}Turnos;

typedef struct ClientesActivTurno{
    long dni;
    char actividad[50];
}ClientesActivTurno;

typedef struct ClientesPagos{
    long dni;
    float monto;
    struct tm fechaEmision;
    struct tm fechaPago;
}ClientesPagos;

typedef struct Reservas{
    long dni;
    char actividad[50];
}Reservas;