// libs lines: 5281

#include <stdio.h>
#include <stdlib.h>
#include "libs/advmenu.h"
#include <signal.h>
#include "libs/tpstructs.h"
#include "libs/Handlers/Handlers.h"

#include "libs/List/Listas.h"
#include "libs/interfaces/interfaces.h"

int main(int argc, char **args)
{
    char *nomActividades[] = {
        "Complemento",
        "Complemento",
        "Pesas",
        "Pesas",
        "Zumba",
        "Zumba",
        "Crossfit",
        "Crossfit",
        "Cardio",
        "Cardio",
        "Bodybuilder",
        "Bodybuilder",
        "Bicicleta",
        "Bicicleta",
        "Funcional",
        "Funcional",
    };
    char *nomClientes[] = {
        "Lucia",
        "Ander",
        "Andres",
        "Sofia",
        "Hertrudis",
        "Felipe",
        "Carlos",
        "Pedro",
        "Lucia",
        "Lauraaa",
        "Martin",
        "Leopoldo",
        "Leonel",
        "Emmanuel",
        "Joaquin",
        "Oscar",
        "Ernestina",
        "Claudia",
        "Paulo",
        "Paula",
        "Paola",
        "Pepo",
        "Lautaro",

    };
    char *apeClientes[] = {
        "Noguera",
        "Rodriguez",
        "Marlos",
        "Ferreyra",
        "Martrudis",
        "Leopoldo",
        "Marlos",
        "Martínez",
        "Perez",
        "Pereyra",
        "Noguera",
        "Poldo",
        "Carrera",
        "Vogler",
        "Britez",
        "Wolfgang",
        "Mena",
        "Castro",
        "Toledano",
        "Ramiro",
        "Asensio",
        "Oliva",
        "Echeverría",
    };
    int dni[] = {
        62924491,
        18833863,
        72800015,
        42603356,
        85570696,
        7686118,
        33328115,
        36588664,
        85288296,
        62201207,
        7804557,
        52186794,
        25632727,
        41502190,
        47240698,
        15680096,
        61333949,
        47716905,
        16263675,
        32282079,
        31095448,
        29908818,
        28722187,
    };
    char *nomProf[] = {
        "Dominic",
        "Cody",
        "Jessica",
        "Lisa",
        "Bryan",
        "Wendy",
        "Stephanie",
        "Ryan",
        "Danielle",
        "Joseph",
        "Tony",
        "Anthony",
        "Lori",
        "Jennifer",
        "Jacob",
        "Valerie",
        "Ashley",
        "Jeff",
        "Melissa",
    };
    char *apeProf[] = {
        "Cochran",
        "English",
        "Johnson",
        "Hernandez",
        "Howard",
        "Weber",
        "Dean",
        "Allen",
        "Gordon",
        "Campos",
        "Smith",
        "Thompson",
        "Williams",
        "Brown",
        "Castillo",
        "Crane",
        "Ramirez",
        "Brooks",
        "Oconnor",
    };
    long dniProf[] = {
        62220146,
        21102510,
        81210949,
        88215985,
        6741991,
        75970294,
        67393964,
        77903325,
        57279696,
        19798233,
        50062755,
        37690100,
        22517474,
        52842007,
        96928596,
        31964147,
        44319403,
        49239014,
        75854185,
    };
    FILE *f;
    Actividades actividad;
    f = fopen("actividades.bin", "wb");
    for (int i = 0; i < 16; i++)
    {
        strcpy(actividad.nombre, nomActividades[i]);
        if (!(i % 2))
            actividad.sucursal = 1;
        else
            actividad.sucursal = 2;
        fwrite(&actividad, sizeof(actividad), 1, f);
        printf("\n%s -- %d", actividad.nombre, actividad.sucursal);
    }
    fclose(f);
    Clientes cliente;
    f = fopen("clientes.bin", "wb");
    for (int i = 0; i < 23; i++)
    {
        strcpy(cliente.nombre, nomClientes[i]);
        strcpy(cliente.apellido, apeClientes[i]);
        cliente.dni = dni[i];
        cliente.fechaNacimiento.tm_mday = i + 3;
        cliente.fechaNacimiento.tm_mon = 4;
        if (!(i % 2))
            cliente.fechaNacimiento.tm_year = 1990 - 1900;
        else
            cliente.fechaNacimiento.tm_year = 2000 - 1900;

        cliente.ultimaActividad.tm_mday = (rand() % 10) + 10;
        cliente.ultimaActividad.tm_mon = 4;
        cliente.ultimaActividad.tm_year = 122;
        cliente.fechaBaja.tm_mday = 0;
        cliente.fechaBaja.tm_mon = -1;
        cliente.fechaBaja.tm_year = -1900;
        itoa((rand() % 10001) + (rand() % 367) + 10000, cliente.telefono, 10);
        printf("\n%s %s-- %d", cliente.nombre, cliente.apellido, cliente.dni);
        printf("--Nacimiento: dia:%d mes:%d anio:%d", cliente.fechaNacimiento.tm_mday, cliente.fechaNacimiento.tm_mon, cliente.fechaNacimiento.tm_year);
        printf("--Ultima actividad: dia:%d mes:%d anio:%d", cliente.ultimaActividad.tm_mday, cliente.ultimaActividad.tm_mon, cliente.ultimaActividad.tm_year);
        fwrite(&cliente, sizeof(cliente), 1, f);
    }
    fclose(f);
    Profesores profesor;
    f = fopen("profRecords.bin", "wb");
    for (int i = 0; i < 19; i++)
    {
        strcpy(profesor.nombre, nomProf[i]);
        strcpy(profesor.apellido, apeProf[i]);
        profesor.dni = dniProf[i];
        itoa((rand() % 10001) + (rand() % 367) + 10000, profesor.telefono, 10);
        fwrite(&profesor, sizeof(profesor), 1, f);
    }
    fclose(f);
    return 0;
}