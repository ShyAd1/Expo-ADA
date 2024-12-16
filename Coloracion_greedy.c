#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, e; // Numero de vertices y aristas
typedef struct
{
    int *neighbors; // Lista de vecinos
    int size;       // Tamaño actual de la lista de vecinos
    int capacity;   // Capacidad máxima de la lista de vecinos
} GraphNode;

GraphNode *graph; // Grafo como lista de adyacencia\int *color;        // Colores de los vertices
int *color;       // Arreglo global para almacenar los colores de los nodos
int *unused;      // Arreglo temporal para almacenar colores usados

void addEdge(int x, int y)
{
    // Añadir y a la lista de adyacencia de x
    if (graph[x].size == graph[x].capacity)
    {
        graph[x].capacity *= 2;
        graph[x].neighbors = realloc(graph[x].neighbors, graph[x].capacity * sizeof(int));
    }
    graph[x].neighbors[graph[x].size++] = y;

    // Añadir x a la lista de adyacencia de y
    if (graph[y].size == graph[y].capacity)
    {
        graph[y].capacity *= 2;
        graph[y].neighbors = realloc(graph[y].neighbors, graph[y].capacity * sizeof(int));
    }
    graph[y].neighbors[graph[y].size++] = x;
}

void greedyColoring()
{
    color[0] = 0; // Color inicial para el primer vertice

    for (int i = 1; i < n; i++)
    {
        color[i] = -1; // Inicialmente sin color
    }

    for (int i = 0; i < n; i++)
    {
        unused[i] = 0; // Inicializar todos los colores como no usados
    }

    for (int i = 1; i < n; i++)
    {
        // Marcar los colores usados por los vecinos
        for (int j = 0; j < graph[i].size; j++)
        {
            int neighbor = graph[i].neighbors[j];
            if (color[neighbor] != -1)
            {
                unused[color[neighbor]] = 1;
            }
        }

        // Encontrar el primer color no usado
        int cr;
        for (cr = 0; cr < n; cr++)
        {
            if (!unused[cr])
            {
                break;
            }
        }

        color[i] = cr; // Asignar color al vertice

        // Reiniciar los colores usados
        for (int j = 0; j < graph[i].size; j++)
        {
            int neighbor = graph[i].neighbors[j];
            if (color[neighbor] != -1)
            {
                unused[color[neighbor]] = 0;
            }
        }
    }
}

int main()
{
    int x, y;

    printf("Ingrese el numero de vertices y aristas respectivamente: ");
    scanf("%d %d", &n, &e);

    // Reservar memoria para el grafo
    graph = malloc(n * sizeof(GraphNode));
    for (int i = 0; i < n; i++)
    {
        graph[i].neighbors = malloc(2 * sizeof(int));
        graph[i].size = 0;
        graph[i].capacity = 2;
    }

    color = malloc(n * sizeof(int));
    unused = malloc(n * sizeof(int));

    printf("\n");
    for (int i = 0; i < e; i++)
    {
        printf("Ingrese los vertices de la arista %d: ", i + 1);
        scanf("%d %d", &x, &y);
        x--;
        y--;
        addEdge(x, y);
    }

    greedyColoring();

    for (int i = 0; i < n; i++)
    {
        printf("El vertice %d tiene el color %d\n", i + 1, color[i] + 1);
    }

    // Liberar memoria
    for (int i = 0; i < n; i++)
    {
        free(graph[i].neighbors);
    }
    free(graph);
    free(color);
    free(unused);

    return 0;
}
