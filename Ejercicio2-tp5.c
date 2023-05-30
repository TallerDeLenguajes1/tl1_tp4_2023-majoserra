#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defino estructuras
struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 - 100
} typedef Tarea;
struct Nodo
{
    Tarea T;                // Dato
    struct Nodo *Siguiente; // Puntero al Siguiente
};
typedef struct Nodo *Lista;
// Declaracion de Funciones
Tarea crearTarea(int id);
void mostrarTarea(Tarea T);
Lista crearListavacia();
Lista crearNodo(Lista H, Tarea T);
Lista insertarNodo(Lista H, Lista nodo);
void eliminarNodo(Lista *H, int id);
void mostrarDatos(Lista H);
Lista quitarNodo(Lista *L, Tarea nodo);
void MoverTareas(Lista *H, Lista *R, Lista *P, int resp, Lista nodoAbuscar);
void listarTareas(Lista L);
Lista BuscarTareaID(Lista L, int id);
void modificacion(Lista *pen, Lista *R, Lista *pro, int id);
int main()
{
    Lista TareaPendiente, TareaRealizada, TareaProceso;
    int cant, id, consulta_modificar, opcion;
    // Creamos las 3 Listas Vacias
    TareaPendiente = crearListavacia();
    TareaRealizada = crearListavacia();
    /*a) Agregar una nueva lista enlazada para las tareas en proceso, llamada TareasEnProceso*/
    TareaProceso = crearListavacia();

    printf("\nIngrese la Cantidad de Tareas: ");
    scanf("%d", &cant);

    for (int i = 0; i < cant; i++)
    {
        TareaPendiente = crearNodo(TareaPendiente, crearTarea(i));
    }
    //! MoverTareas(&TareaPendiente, &TareaRealizada, &TareaProceso);
    /*i) Liste todas las tareas cargadas en todas las categorías (Pendientes, En Proceso y
    Realizadas), mostrando todos sus datos.*/
    printf("\n---------Tareas Pendiente ---------");
    listarTareas(TareaPendiente);

    printf("\n");
    printf("\nDesea Modificar alguna Tarea (1=SI)(0=NO): ");
    scanf("%d", &consulta_modificar);

    while (consulta_modificar == 1)
    {
        printf("\n---------Tareas Pendiente ---------");
        listarTareas(TareaPendiente);
        printf("\n---------Tareas Realizadas ---------");
        listarTareas(TareaRealizada);
        printf("\n---------Tareas en Proceso ---------");
        listarTareas(TareaProceso);
        printf("\nQue Tarea desea Seleccionar? (ingrese ID)");
        scanf("%d", &id);
        if (BuscarTareaID(TareaPendiente, id) != NULL)
        {
            printf("\nMenu: ");
            printf("\n1-.Mover a Realizada");
            printf("\n2-.Mover a en Proceso");
            printf("\n3.-Eliminar la Tarea :)");
            printf("\nElija una opcion: ");
            scanf("%d", &opcion);
            MoverTareas(&TareaPendiente, &TareaRealizada, &TareaProceso, opcion, BuscarTareaID(TareaPendiente, id));
        }
        else
        {
            if (BuscarTareaID(TareaRealizada, id) != NULL)
            {
                printf("\nMenu: ");
                printf("\n1-.Mover a Pendiente");
                printf("\n2-.Mover a en Proceso");
                printf("\n3.-Eliminar la Tarea :)");
                printf("\nElija una opcion: ");
                scanf("%d", &opcion);
                MoverTareas(&TareaRealizada, &TareaPendiente, &TareaProceso, opcion, BuscarTareaID(TareaRealizada, id));
            }
            else
            {
                if (BuscarTareaID(TareaProceso, id) != NULL)
                {
                    printf("\nMenu: ");
                    printf("\n1-.Mover a Realizada");
                    printf("\n2-.Mover a Pendiente");
                    printf("\n3.-Eliminar la Tarea :)");
                    printf("\nElija una opcion: ");
                    scanf("%d", &opcion);
                    MoverTareas(&TareaProceso, &TareaRealizada, &TareaPendiente, opcion, BuscarTareaID(TareaProceso, id));
                }
            }
        }

        printf("\nDesea Modificar otra Tarea (1=SI)(0=NO): ");
        scanf("%d", &consulta_modificar);
    }
    printf("\n---------Tareas Pendiente ---------");
    listarTareas(TareaPendiente);
    printf("\n---------Tareas Realizadas ---------");
    listarTareas(TareaRealizada);
    printf("\n---------Tareas en Proceso ---------");
    listarTareas(TareaProceso);

    printf("\nDATOS TAREA: \n");
    mostrarDatos(TareaPendiente);

    return 0;
}
void modificacion(Lista *pen, Lista *R, Lista *pro, int id)
{
    printf("HOLA");
}
// Funciones para Tarea
void listarTareas(Lista L) // Funcion que Lista toda la lista de tareas (que muestra la lista)
{
    Lista aux = L;
    while (aux != NULL)
    {
        printf("\n");
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
    }
}
Tarea crearTarea(int id)
{
    srand(time(NULL));
    Tarea aux;
    char *buff = (char *)malloc(sizeof(char) * 300);
    printf("\nIngrese la Descripcion: ");
    fflush(stdin);
    gets(buff);
    aux.Descripcion = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(aux.Descripcion, buff);
    aux.Duracion = rand() % 91 + 10;
    aux.TareaID = id;
    free(buff);
    return aux;
}
void mostrarTarea(Tarea T)
{
    printf("\nDescripcion: %s", T.Descripcion);
    printf("\nDuracion: %d", T.Duracion);
    printf("\nTareaID: %d", T.TareaID);
}
// Funciones Principales de Lista
Lista crearListavacia()
{
    return NULL;
}
Lista crearNodo(Lista H, Tarea T)
{
    Lista nuevo;
    nuevo = (Lista)malloc(sizeof(struct Nodo));
    nuevo->Siguiente = H;
    nuevo->T = T;
    H = nuevo;
    return H; // Devolvemos la cabeza
}
Lista insertarNodo(Lista L, Lista nodo)
{
    nodo->Siguiente = L;
    L = nodo;
    return L;
}
Lista quitarNodo(Lista *L, Tarea nodo)
{
    Lista aux = *L;
    Lista auxAnterior = *L;

    while (aux != NULL && aux->T.TareaID != nodo.TareaID)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }

    if (aux)
    {
        if (aux == *L)
        {
            *L = aux->Siguiente;
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }
    return aux;
}
void MoverTareas(Lista *H, Lista *R, Lista *P, int resp, Lista nodoAbuscar)
{
    Lista nodo;
    printf("\n--------------");
    mostrarTarea(nodoAbuscar->T);
    if (resp == 1)
    {
        nodo = nodoAbuscar;
        nodo = quitarNodo(H, nodo->T);
        *R = insertarNodo(*R, nodo);
    }
    else
    {
        if (resp == 2)
        {
            nodo = nodoAbuscar;
            nodo = quitarNodo(H, nodo->T);
            *P = insertarNodo(*P, nodo);
        }
        else
        {
            if (resp == 3)
            {
                eliminarNodo(H, nodoAbuscar->T.TareaID);
            }
        }
    }
}

//! void MoverTareas(Lista *H, Lista *R, Lista *P)
// {
//     Lista aux = *H;
//     Lista nodo;
//     int resp;
//     while (aux != NULL)
//     {
//         printf("\n--------------");
//         mostrarTarea(aux->T);
//         printf("\nRealizo La Tarea?(0=NO)(1=SI)(2=Proceso)");
//         scanf("%d", &resp);
//         if (resp == 1)
//         {
//             nodo = aux;
//             aux = aux->Siguiente;
//             nodo = quitarNodo(H, nodo->T);
//             *R = insertarNodo(*R, nodo);
//         }
//         else
//         {
//             if (resp == 2)
//             {
//                 nodo = aux;
//                 aux = aux->Siguiente;
//                 nodo = quitarNodo(H, nodo->T);
//                 *P = insertarNodo(*P, nodo);
//             }
//             else
//             {
//                 aux = aux->Siguiente;
//             }
//         }
//     }
// }
/*b) Agregue una función Eliminar para eliminar Tareas*/
void eliminarNodo(Lista *H, int id)
{
    Lista aux = *H;
    Lista auxAnterior = *H;

    while (aux != NULL && aux->T.TareaID != id)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }
    if (aux)
    {
        if (aux == *H)
        {
            *H = aux->Siguiente;
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        free(aux);
    }
}
/*c) Agregue una función MostrarDatos que reciba una lista y muestre la cantidad de
tareas y el tiempo asociado a la misma (la suma del campo duración de todos las tareas
de la lista)
*/
void mostrarDatos(Lista H)
{
    Lista aux = H;
    int cant_Tareas = 0, duracion = 0;
    while (aux != NULL)
    {
        cant_Tareas++;                         // Suma la cantidad de tareas que tiene la lista
        duracion = duracion + aux->T.Duracion; // Suma del campo duracion de toda la lista
        aux = aux->Siguiente;                  // Recorrer la lista
    }
    printf("\nLa cantidad de Tareas es: %d", cant_Tareas);
    printf("\nEl tiempo asociado es: %d", duracion);
}
/*Funcion que busca una Tarea por ID*/
Lista BuscarTareaID(Lista L, int id)
{
    Lista aux = L;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    aux = NULL;
    return aux;
}