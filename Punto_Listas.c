#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defino estructuras
struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 â€“ 100
} typedef Tarea;
struct Nodo
{
    Tarea T;                // Dato
    struct Nodo *Siguiente; // Puntero al Siguiente
};
typedef struct Nodo *Lista;
// Declaracion de funciones
Lista crearListaVacia();
Lista crearNodo(Lista cabeza, Tarea T);
Tarea crearTarea(int id);
void cargarTareas(Lista *cabeza);
void mostrarTarea(Tarea T);
Lista quitarNodo(Lista *cabeza, Tarea id);
Lista InsertarNodo(Lista L, Lista nodo);
void moverTarea(Lista *pendiente, Lista *realizada);
Lista BuscarTareaID(Lista L, int id);
Lista BuscarTareaP(Lista L, char *comparar);
// Funcion Principal
int main()
{
    Lista tareaPendiente;
    Lista tareaRealizada;
    int id;
    tareaPendiente = crearListaVacia();
    tareaRealizada = crearListaVacia();
    cargarTareas(&tareaPendiente);

    moverTarea(&tareaPendiente, &tareaRealizada);
    Lista aux = tareaPendiente;
    while (aux != NULL)
    {
        printf("\n---------Tarea Pendiente ---------");
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
    }

    Lista aux2 = tareaRealizada;
    while (aux2 != NULL)
    {
        printf("\n---------Tarea Realizadas ---------");
        mostrarTarea(aux2->T);
        aux2 = aux2->Siguiente;
    }

    printf("\nIngrese el ID de la tarea que desea Buscar: ");
    scanf("%d", &id);

    if (BuscarTareaID(tareaRealizada, id) != NULL)
    {
        printf("\nLa tarea que Busca es: ");
        mostrarTarea(BuscarTareaID(tareaRealizada, id)->T);
    }
    else
    {
        printf("\nNo se encontro la Tarea :(");
    }

    char *comparar;
    comparar = (char *)malloc(sizeof(char) * 100);
    printf("\nIngrese palabra de la tarea que desea Buscar: ");
    fflush(stdin);
    gets(comparar);
    if (BuscarTareaP(tareaRealizada, comparar) != NULL)
    {
        printf("\nLa tarea que Busca es: ");
        mostrarTarea(BuscarTareaP(tareaRealizada, comparar)->T);
    }
    else
    {
        printf("\nNo se encontro la Tarea :(");
    }

    return 0;
}
// Crear Lista Vacia
Lista crearListaVacia()
{
    return NULL;
}
// Crear Nodo
Lista crearNodo(Lista cabeza, Tarea T)
{
    Lista nuevoNodo;
    nuevoNodo = (Lista)malloc(sizeof(struct Nodo)); // memoria dinamica
    nuevoNodo->Siguiente = cabeza;
    nuevoNodo->T = T;
    cabeza = nuevoNodo;
    return cabeza;
}
// Crear Tarea
Tarea crearTarea(int id)
{
    Tarea tarea;
    char *buff = (char *)malloc(sizeof(char) * 300);
    printf("\nIngrese la Descripcion:");
    fflush(stdin);
    gets(buff);
    tarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(tarea.Descripcion, buff);
    tarea.Duracion = rand() % 91 + 10;
    tarea.TareaID = id;

    return tarea;
}
// cargarTareas
void cargarTareas(Lista *cabeza)
{
    int i = 0, cantT = 1;
    printf("\n--------------Cargue las Tareas-------------\n\n");
    while (cantT == 1)
    {
        *cabeza = crearNodo(*cabeza, crearTarea(i));
        i++;
        printf("\nDesea Seguir Cargando: ");
        scanf("%d", &cantT);
    }
}
// Mostrar Tarea
void mostrarTarea(Tarea T)
{
    printf("\nDescripcion: %s", T.Descripcion);
    printf("\nDuracion: %d", T.Duracion);
    printf("\nTareaID: %d", T.TareaID);
}
// Quitar Nodo
Lista quitarNodo(Lista *cabeza, Tarea id)
{
    Lista aux = *cabeza, auxAnterior = *cabeza;

    while (aux != NULL && aux->T.TareaID != id.TareaID)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }

    if (aux)
    {
        if (aux == *cabeza)
        {
            *cabeza = aux->Siguiente; // modificar el primero
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }
    return aux;
}
Lista InsertarNodo(Lista L, Lista nodo)
{
    nodo->Siguiente = L;
    L = nodo;
    return L;
}
void moverTarea(Lista *pendiente, Lista *realizada)
{
    Lista aux = *pendiente;
    Lista nodo;
    int pregunta;

    while (aux != NULL)
    {
        printf("\n--------------");
        mostrarTarea(aux->T);
        printf("\nRealizo la Tarea? (1=SI)(0=NO)");
        scanf("%d", &pregunta);
        if (pregunta)
        {
            nodo = aux;
            aux = aux->Siguiente;
            nodo = quitarNodo(pendiente, nodo->T);
            *realizada = InsertarNodo(*realizada, nodo);
        }
        else
        {
            aux = aux->Siguiente;
        }
    }
}
/*Implemente una funciÃ³n de bÃºsqueda de tarea por nro. de id de nombre BuscarTarea.
 La misma devuelve la tarea solicitada.*/
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
Lista BuscarTareaP(Lista L, char *comparar)
{
    Lista aux = NULL;
    while (L != NULL)
    {
        if (strstr(L->T.Descripcion, comparar))
        {
            aux = L;
        }
        L = L->Siguiente;
    }
    return aux;
}