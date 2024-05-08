#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} typedef Nodo;

typedef Nodo *Cabecera;

Cabecera carga(int id, char descripcion[], int duracion, Cabecera lista);

int idAuto(int *id);
int duracion();
void MostrarTareas(Cabecera Tareas);
void Buscar(Cabecera Realizadas, Cabecera Pendientes);

int main()
{
    srand(time(NULL));

    Cabecera TareasPendientes = NULL;
    Cabecera TareasRealizadas = NULL;

    // INTERFAZ CARGA DE TAREAS PENDIENTES

    int seguir = 1;
    int id = 999;
    int numero;
    int durac;

    do
    {
        printf("\nIngrese descripcion de la tarea: ");
        char buff[50];
        scanf(" %[^\n]", buff); // en esta linea me ayuda chatgpt
        // fflush(stdin);
        // gets(buff);
        numero = idAuto(&id);
        durac = duracion();

        TareasPendientes = carga(numero, buff, durac, TareasPendientes);
        printf("\nDesea seguir cargando tareas? ");
        printf("\n1.Si  2.No");
        printf("\nResponda: ");
        scanf("%d", &seguir);

    } while (seguir == 1);

    // INTERFAZ PARA MOSTRAR LAS TAREAS PENDIENTES

    MostrarTareas(TareasPendientes);

    // INTERFAZ PARA PASAR DE TAREA PENDIENTE A TAREA REALIZADA
    printf("\n------INDICAR TAREAS REALIZADAS------");

    int idRealizado;

    do
    {
        printf("\nIngrese el id de la tarea: ");
        scanf("%d", &idRealizado);

        Nodo *aux = TareasPendientes;
        Nodo *anterior = NULL;

        while (aux != NULL)
        {

            if (idRealizado == aux->T.TareaID)
            {
                TareasRealizadas = carga(aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion, TareasRealizadas);
                if (anterior != NULL)
                {
                    anterior->Siguiente = aux->Siguiente;
                }
                else
                {
                    TareasPendientes = aux->Siguiente;
                }
                free(aux);
                break;
            }
            anterior = aux;
            aux = aux->Siguiente;
        }

        printf("\nDesea seguir eliminando tareas? ");
        printf("\n1.Si  2.No");
        printf("\nResponda: ");
        scanf("%d", &seguir);

    } while (seguir == 1);

    // MOSTRAMOS AMBAS

    printf("\n-----TAREAS PENDIENTES-----");
    MostrarTareas(TareasPendientes);
    printf("\n-----TAREAS REALIZADAS-----");
    MostrarTareas(TareasRealizadas);
    printf("\n");

    Buscar(TareasRealizadas, TareasPendientes);

    return 0;
}

Cabecera carga(int id, char descripcion[], int duracion, Cabecera lista)
{

    Nodo *Aux = (Nodo *)malloc(sizeof(Nodo));

    Aux->T.TareaID = id;
    Aux->T.Descripcion = (char *)malloc((strlen(descripcion) + 1) * sizeof(char));
    strcpy(Aux->T.Descripcion, descripcion);
    Aux->T.Duracion = duracion;

    Aux->Siguiente = lista;
    lista = Aux;

    return lista;
}

int idAuto(int *id)
{
    *id += 1;
    return *id;
}

int duracion()
{

    int durac = rand() % ((100 - 10 + 1) + 10);

    return durac;
}

void MostrarTareas(Cabecera Tareas)
{

    Nodo *Aux = Tareas;
    int i = 1;

    while (Aux != NULL)
    {
        printf("\n-----TAREA NUMERO %d------", i);
        printf("\nID: %d", Aux->T.TareaID);
        printf("\nDescripcion: %s", Aux->T.Descripcion);
        printf("\nDuracion: %d minutos", Aux->T.Duracion);
        Aux = Aux->Siguiente;
        i++;
    }
}

void Buscar(Cabecera Realizadas, Cabecera Pendientes)
{
    printf("-----BUSCAR TAREA------\n");
    printf("Por id (1)\n");
    printf("Por descripcion (2)\n");
    printf("Ingrese: ");
    int num;
    scanf("%d", &num);
    Nodo *aux;

    if (num == 1)
    {
        printf("Ingrese id a buscar: ");
        int id;
        scanf("%d", &id);
        aux = Realizadas;
        while (aux != NULL)
        {
            if (aux->T.TareaID == id)
            {
                printf("\n-----TAREA BUSCADA: REALIZADA------");
                printf("\nID: %d", aux->T.TareaID);
                printf("\nDescripcion: %s", aux->T.Descripcion);
                printf("\nDuracion: %d minutos", aux->T.Duracion);
                break;
                return;
            }
            aux = aux->Siguiente;
        }
        aux = Pendientes;
        while (aux != NULL)
        {
            if (aux->T.TareaID == id)
            {
                printf("\n-----TAREA BUSCADA: PENDIENTE------");
                printf("\nID: %d", aux->T.TareaID);
                printf("\nDescripcion: %s", aux->T.Descripcion);
                printf("\nDuracion: %d minutos", aux->T.Duracion);
                break;
                return;
            }
            aux = aux->Siguiente;
        }
        printf("-----LA TAREA NO EXISTE-----");
    }
    else
    {
        printf("Ingrese descripcion a buscar: ");
        char buffer[50];
        fflush(stdin);
        gets(buffer);

        aux = Realizadas;
        while (aux != NULL)
        {
            if (strcmp(aux->T.Descripcion, buffer) == 0)
            {
                printf("\n-----TAREA BUSCADA: REALIZADA------");
                printf("\nID: %d", aux->T.TareaID);
                printf("\nDescripcion: %s", aux->T.Descripcion);
                printf("\nDuracion: %d minutos", aux->T.Duracion);
                break;
                return;
            }
            aux = aux->Siguiente;
        }
        aux = Pendientes;
        while (aux != NULL)
        {
            if (strcmp(aux->T.Descripcion, buffer) == 0)
            {
                printf("\n-----TAREA BUSCADA: PENDIENTE------");
                printf("\nID: %d", aux->T.TareaID);
                printf("\nDescripcion: %s", aux->T.Descripcion);
                printf("\nDuracion: %d minutos", aux->T.Duracion);
                break;
                return;
            }
            aux = aux->Siguiente;
        }
        printf("-----LA TAREA NO EXISTE-----");
    }
}