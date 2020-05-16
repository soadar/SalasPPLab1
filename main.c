#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMFECHA 10
#define TAMMASCOTAS 10
#define IDSTART 100

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct
{
    int id; //1000
    char descripcion[20];
} Tipo;

typedef struct
{
    int id; //5000
    char nombreColor[20];
} Color;

typedef struct
{
    int id;
    char nombre[20];
    int idTipo;//Validar
    int idColor;//Validar
    int edad;
} Mascota;

typedef struct
{
    int id; //20000
    char descripcion[25];
    float precio;
} Servicio;


typedef struct
{
    int id; //autoincremental
    int idMascota;//Validar
    int idServicio;//Validar
    int fecha; // validar dia mes año
} Trabajo;

Servicio listServ[3]=
{
    {20001, "Corte", 250.00},
    {20002, "Desparasitado", 300.00},
    {20003, "Castrado", 400.00}
};

Color listColor[5]=
{
    {5001, "Negro"},
    {5002, "Blanco"},
    {5003, "Gris"},
    {5004, "Rojo"},
    {5005, "Azul"}
};

Tipo listTipo[5]=
{
    {1001, "Ave"},
    {1002, "Perro"},
    {1003, "Gato"},
    {1004, "Roedor"},
    {1005, "Pez"}
};

Fecha listFecha[TAMFECHA];
Mascota listMascota[TAMMASCOTAS];

void harcodeomascotas(Mascota* list, int tam);

int menu();
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
void listarTipos (Tipo* list, int tam);
void listarColores (Color* list, int tam);
void listarServicios (Servicio* list, int tam);
int altaMascota(int idx, Mascota* listMascota, Color* listColor, Tipo* listTipo);
void listarMascotas (Mascota* list, int tam);
int buscarMascota(Mascota* list, int tam, int id, Tipo* listTipo);

int main()
{
    int salida=1;
    int idMascota=IDSTART;
    int idx;
    harcodeomascotas(listMascota, TAMMASCOTAS);

    do
    {
        system("CLS");
        switch(menu())
        {
        case 1:
            printf("\nalta"); //if alta = ok, id++
            if (altaMascota(idMascota, listMascota, listColor, listTipo) == 0)
            {
                idMascota++;
            }
            break;
        case 2:
            //printf("\nmodificar");
            printf("\nIngrese ID de la masctoa: ");
            scanf("%d",&idx);
            buscarMascota(listMascota,TAMMASCOTAS,idx,listTipo);
            break;
        case 3:
            //printf("\nbaja");
            break;
        case 4:
            //printf("\nlistar mascotas");
            listarMascotas(listMascota, idMascota);
            break;
        case 5:
            //printf("\nlistar tipos");
            listarTipos(listTipo, 5);
            break;
        case 6:
            //printf("\nlistar colores");
            listarColores(listColor, 5);
            break;
        case 7:
            //printf("\nlistar servicios");
            listarServicios(listServ,3);
            break;
        case 8:
            printf("\nalta trabajo");
            break;
        case 9:
            printf("\nlistar trabajos");
            break;
        default:
            printf("\nSe ingreso un dato invalido\n");
            system("pause>nul");
            salida=0;
            break;
        }
    }
    while (salida !=0);

    return 0;
}

int menu()
{
    int resp;
    printf("\n*** Menu Veterinaria ***\n\n");
    printf("1) Alta Mascota\n");
    printf("2) Modificar Mascota\n"); // MODIFICAR MASCOTA: Se ingresará el id, permitiendo en un submenú modificar: Tipo / Edad
    printf("3) Baja Masctota\n"); // Se ingresará el id de la mascota y se realizará una baja lógica.
    printf("4) Listar Mascotas\n"); //Hacer un único listado de todas las mascotas ordenadas por tipo y nombre.
    printf("5) Listar Tipos\n");
    printf("6) Listar Colores\n");
    printf("7) Listar Servicios\n");
    printf("8) Alta Trabajo\n"); //Se dará de alta cada ocurrencia de trabajo pidiéndole al usuario que elija una mascota y un Servicio
    printf("9) Listar Trabajos\n");
    utn_getNumero(&resp, "\nIngrese una opcion: ", "\nError, ingreso incorrecto, debe ingresar de 1 a 9\n", 1, 9, 3);
    return resp;
}

void listarTipos (Tipo* list, int tam)
{
    system("CLS");
    printf("\n ID          Descripcion\n\n");
    for (int i=0; i < tam; i++)
    {
        printf("%03d    %12s\n", list[i].id,list[i].descripcion);
    }
    printf("\n");
    system("pause");
}

void listarColores (Color* list, int tam)
{
    system("CLS");
    printf("\n ID            Color\n\n");
    for (int i=0; i < tam; i++)
    {
        printf("%03d    %12s\n", list[i].id,list[i].nombreColor);
    }
    printf("\n");
    system("pause");
}


void listarServicios (Servicio* list, int tam)
{
    system("CLS");
    printf("\n ID         Descripcion       precio\n\n");
    for (int i=0; i < tam; i++)
    {
        printf("%03d    %14s      %6.2f\n", list[i].id,list[i].descripcion, list[i].precio);
    }
    printf("\n");
    system("pause");
}

int altaMascota(int idx, Mascota* listMascota, Color* listColor, Tipo* listTipo)
{
    int resp;
    Mascota auxMascota;
    system("cls");

    printf("\n*** Alta mascota ***\n\n");
    auxMascota.id  = idx;
    printf("\nIngrese nombre: ");
    fflush(stdin);
    gets(auxMascota.nombre);
    listarTipos(listTipo, 5);
    utn_getNumero(&auxMascota.idTipo, "\nIngrese un tipo: ", "\nError, ingreso incorrecto, debe ingresar de 1001 a 1005\n", 1001, 1005, 3);
    listarColores(listColor, 5);
    utn_getNumero(&auxMascota.edad, "\nIngrese un color: ", "\nError, ingreso incorrecto, debe ingresar de 5001 a 5005\n", 5001, 5005, 3);
    printf("\nIngrese edad: ");
    scanf("%d",&auxMascota.edad);
    printf("\n\nCarga Exitosa\n");

    listMascota[idx] = auxMascota;

    return 0;
}


void listarMascotas (Mascota* list, int tam)
{
    system("CLS");
    printf("\n ID        Nombre       Tipo     color     edad\n\n");


    for (int i=0; i < tam; i++)
    {
        if (list[i].edad > 0)
        {
            printf("%03d    %15s    %d    %d    %d   \n", list[i].id, list[i].nombre, list[i].idTipo, list[i].idColor, list[i].edad);
        }

    }
    system("pause");
}

void harcodeomascotas(Mascota* list, int tam)
{
    int id[10]= {100,101,102,103,104,105,106,107,108,109};
    char nombre[10][30]= {"felipe", "miguel", "victor", "maria", "daniela", "daniel", "horacio", "dario", "sergia", "puma"};
    int tipo[10]= {1001,1002,1003,1004,1005,1002,1001,1005,1002,1004};
    int color[10]= {5001,5002,5003,5004,5005,5003,5002,5005,5002,5001};
    int edad[10]= {3,4,7,8,4,3,2,14,7,43};

    for (int i=0; i<tam; i++)
    {
        list[i].id=id[i];
        strcpy(list[i].nombre, nombre[i]);
        list[i].idTipo=tipo[i];
        list[i].idColor=color[i];
        list[i].edad=edad[i];
    }
}


int buscarMascota(Mascota* list, int tam, int id, Tipo* listTipo)
{
    int resp;
    system("cls");
    if( list != NULL)
    {
        for (int i=0; i < tam; i++)
        {
            if (list[i].id == id)
            {
                printf("\n\n*************************************\n");
                printf("*          Modificar mascota          *\n");
                printf("*************************************\n\n");
                printf("\nQue desea modificar?\n\n");
                printf("1) Tipo\n");
                printf("2) Edad\n");
                utn_getNumero(&resp, "\nIngrese una opcion: ", "\nError, ingreso incorrecto, debe ingresar de 1 a 2\n", 1, 2, 3);
                if (resp == 1)
                {
                    listarTipos(listTipo, 5);
                    utn_getNumero(&list[i].idTipo, "\nIngrese nuevo tipo: ", "\nError, ingreso incorrecto, debe ingresar de 1001 a 1005\n", 1001, 1005, 3);
                }
                else
                {
                    utn_getNumero(&list[i].edad, "\nIngrese nueva edad: ", "\nError, ingreso incorrecto, debe ingresar de 0 a 100\n", 0, 100, 3);
                }
                return 0;
            }
        }
        printf("\nEl ID no coincide con ningun empleado\n");
        system("pause>nul");
    }
    return -1;
}
