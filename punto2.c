#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/* la siguiente situación: En la misma distribuidora del práctico anterior ahora surgió
la necesidad de llevar un control de las tareas realizadas por sus empleados. Usted forma
parte del equipo de programación que se encargará de hacer el módulo en cuestión que a
partir de ahora se llamará módulo ToDo:*/

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

struct Tarea BuscarTarea(struct Tarea **tarea, int cant,int id);

int main(){
    int cantTareas, gestion, aux=0;
    struct Tarea **tareaPendiente; //todo Doble puntero 
    struct Tarea **tareaRealizada;
    char *buff;
    /*  1. Desarrollar una interfaz por consola donde se solicite al usuario (es decir el
           empleado) cuantas tareas debe cargar.*/

    printf("\nIngrese la cantidad de Tareas a Realizar: ");
    scanf("%d", &cantTareas);

    /*2. Tendrá que generar un arreglo de doble punteros dinámicamente del tipo Tarea
    con la cantidad de tareas solicitadas en el punto anterior.Recuerde inicializar
    los arreglos apuntando a NULL.*/
    buff = (char *)malloc(sizeof(char)*100);
    tareaPendiente = (struct Tarea **)malloc(sizeof(struct Tarea*)*cantTareas); //todo Asignacion de memoria dinamicamente
    srand(time(NULL));
    for (int i = 0; i < cantTareas; i++)
    {
        tareaPendiente[i] = NULL;
        tareaPendiente[i] = (struct Tarea *)malloc(sizeof(struct Tarea)); //todo No la multiplicamos por nada
        /*3. Desarrolle una interfaz de consola para cargar las tareas, ingresando su
        descripción y duración. Recuerde utilizar reserva de memoria dinámica para la
        carga de la descripción.*/
        tareaPendiente[i]->TareaID = i;
        tareaPendiente[i]->Duracion = rand() % 91 + 10;
        fflush(stdin);
        printf("\nIngrese la Descripcion: ");
        gets(buff);
        tareaPendiente[i]->Descripcion = (char *)malloc(sizeof(char)*strlen(buff)+1);
        strcpy(tareaPendiente[i]->Descripcion, buff);  
    }
    /* Una vez cargada todas las tareas. Irá listando de a una las tareas y
    preguntando si se realizó o no la misma.*/

    //! Declaramos memoria dinamicamente para nuestra nueva tareaRealizadas
    tareaRealizada = (struct Tarea **)malloc(sizeof(struct Tarea*)*cantTareas);
    for (int i = 0; i < cantTareas; i++)
    {
        printf("\n--------------TareaPendiente [%d]------------", i+1);
        printf("\nTareaID: %d", tareaPendiente[i]->TareaID);
        printf("\nduracion [%d]: %d", i+1, tareaPendiente[i]->Duracion); 
        printf("\nDescripcion: %s", tareaPendiente[i]->Descripcion);
        printf("\n");
        printf("\nRealizo la Tarea[%d]? (ingrese 1 si la realizo)", i);
        scanf("%d", &gestion);
        if (gestion==1)
        {
            /*Si la respuesta es Si tiene que “mover” dicha tarea a otro arreglo denominado tareas 
            realizadas que tendrá el mismo tamaño que el anterior. */
            tareaRealizada[aux] = (struct Tarea*)malloc(sizeof(struct Tarea));
            tareaRealizada[aux]=tareaPendiente[i];
            tareaPendiente[i]=NULL;  // Una vez movida la tarea ese casillero del vector tiene que apuntar a null.
            aux++;
        } 
    }
    /*5. Mostrar por pantalla todas las tareas realizadas y luego listar las tareas pendientes.*/
    printf("\n==============Tareas Realizadas=============\n");
    for (int i = 0; i < aux; i++)
    {
        printf("\n-------------Tarea Realizada [%d]------------", i+1);
        printf("\nTareaID: %d", tareaRealizada[i]->TareaID);
        printf("\nDuracion: %d", tareaRealizada[i]->Duracion);
        printf("\nDescripcion: %s", tareaRealizada[i]->Descripcion); 
        printf("\n");
    }
    printf("\n============Tareas Pendientes=============\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareaPendiente[i]!=NULL)
        {
            printf("\n--------------TareaPendiente [%d]------------", i+1);
            printf("\nTareaID: %d", tareaPendiente[i]->TareaID);
            printf("\nduracion [%d]: %d", i+1, tareaPendiente[i]->Duracion); 
            printf("\nDescripcion: %s", tareaPendiente[i]->Descripcion);
            printf("\n");
        }
    }
    
    return 0;
}

/*implemente una función de búsqueda de tarea por nro. de id de nombre BuscarTarea. La misma devuelve
la tarea solicitada. */
struct Tarea BuscarTarea(struct Tarea **tarea, int cant,int id){ //? Recibe el id de la tarea a buscar
    struct Tarea *aux = NULL; // inicializamos el puntero con Null
    for (int i = 0; i < cant; i++)
    {
        if (tarea[i]->TareaID==id)
        {
            aux = tarea[i];
        }
    }
    return *aux;
    
}
