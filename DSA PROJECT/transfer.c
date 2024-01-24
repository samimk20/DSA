#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define V_D 9
#define V_K 100
#define MAX 100

// Structure to represent an edge in the graph
typedef struct Edge {
    int src;    // Source vertex
    int dest;   // Destination vertex
    int time;   // Time taken for the route
    int cost;   // Cost of the route
} Edge;

// Structure to represent a graph
typedef struct Graph {
    int V;      // Number of vertices (train stations)
    int E;      // Number of edges (train routes)
    Edge* edge; // Array of edges
} Graph;

// Function prototypes
Graph* createGraph(int V, int E);
void addEdge(Graph* graph, int src, int dest, int time, int cost);
int find(int parent[], int i);
void unionSet(int parent[], int rank[], int x, int y);
int compareEdges(const void* a, const void* b);
void kruskalMST(Graph* graph);
int minDistance(int dist[], int sptSet[], int vertices);
void printPath(int parent[], int j);
void printSolution(int dist[], int n, int parent[]);
void dijkstra(int graph[V_D][V_D], int src);
void createTrainGraph(int trainGraph[V_K][V_K], int stations);
void dijkstra_train(int graph[V_K][V_K], int src, int stations);

// Function to create a new graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int time, int cost) {
    graph->edge[graph->E].src = src;
    graph->edge[graph->E].dest = dest;
    graph->edge[graph->E].time = time;
    graph->edge[graph->E].cost = cost;
    graph->E++;
}

// Function to find the parent of a set in the union-find data structure
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

// Function to perform union of two sets in the union-find data structure
void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Function to compare edges based on their costs for sorting
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->cost - ((Edge*)b)->cost;
}

// Function to find the Minimum Spanning Tree (MST) using Kruskal's Algorithm
void kruskalMST(Graph* graph) {
    int V = graph->V;
    int E = graph->E;
    Edge* result = (Edge*)malloc((V - 1) * sizeof(Edge));

    // Sort the edges based on their costs
    qsort(graph->edge, E, sizeof(Edge), compareEdges);

    int parent[V];
    int rank[V];

    // Initialize parent and rank arrays for union-find
    for (int i = 0; i < V; i++)
        parent[i] = i, rank[i] = 0;

    int e = 0;
    int i = 0;

    // Iterate through sorted edges and add to the result if it forms a cycle
    while (e < V - 1 && i < E) {
        Edge nextEdge = graph->edge[i++];
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        // If including this edge doesn't create a cycle, include it in result
        if (x != y) {
            result[e++] = nextEdge;
            unionSet(parent, rank, x, y);
        }
    }

    // Print the optimized train routes
    printf("Optimized Train Routes (Kruskal's Algorithm):\n");
    printf("Edge   Time   Cost\n");
    for (int i = 0; i < e; i++)
        printf("%d - %d   %d     %d\n", result[i].src, result[i].dest, result[i].time, result[i].cost);

    // Free dynamically allocated memory
    free(result);
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the path from source to a given vertex
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}

// Function to print the solution, including distances and paths for weighted graph
void printSolution(int dist[], int n, int parent[]) {
    int src = 0;
    printf("Vertex\t Distance\tPath");

    for (int i = 1; i < V_D; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

// Function to implement Dijkstra's algorithm for weighted graph
void dijkstra(int graph[V_D][V_D], int src) {
    int dist[V_D];
    int parent[V_D];
    int sptSet[V_D];

    // Initialize all distances as INFINITE, sptSet[] as false, and parent[] as -1
    for (int i = 0; i < V_D; i++)
        dist[i] = INT_MAX, sptSet[i] = 0, parent[i] = -1;

    // Distance from the source vertex to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V_D - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, V_D);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V_D; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u, dist[v] = dist[u] + graph[u][v];
            }
    }

    // Print the solution for weighted graph
    printSolution(dist, V_D, parent);
}

// Function to create the adjacency matrix for train connections based on user input
void createTrainGraph(int trainGraph[V_K][V_K], int stations) {
    printf("Enter the adjacency matrix for train connections:\n");
    for (int i = 0; i < stations; i++) {
        for (int j = 0; j < stations; j++) {
            scanf("%d", &trainGraph[i][j]);
        }
    }
}

// Function to implement Dijkstra's algorithm for train connections
void dijkstra_train(int graph[V_K][V_K], int src, int stations) {
    int dist[V_K];
    int parent[V_K];
    int sptSet[V_K];

    // Initialize all distances as INFINITE, sptSet[] as false, and parent[] as -1
    for (int i = 0; i < stations; i++)
        dist[i] = INT_MAX, sptSet[i] = 0, parent[i] = -1;

    // Distance from the source station to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all stations
    for (int count = 0; count < stations - 1; count++) {
        // Pick the minimum distance station from the set of stations not yet processed
        int u = minDistance(dist, sptSet, stations);

        // Mark the picked station as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent stations
        for (int v = 0; v < stations; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u, dist[v] = dist[u] + graph[u][v];
            }
    }

    // Print the solution
    printf("\nSource: %d\n", src);
    printf("Station\t\tDistance\tPath\n");

    for (int i = 0; i < stations; i++) {
        if (i != src) {
            printf("%d -> %d\t\t%d\t\t%d", src, i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int graph[V_D][V_D] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                           {4, 0, 8, 0, 0, 0, 0, 11, 0},
                           {0, 8, 0, 7, 0, 4, 0, 0, 2},
                           {0, 0, 7, 0, 9, 14, 0, 0, 0},
                           {0, 0, 0, 9, 0, 10, 0, 0, 0},
                           {0, 0, 4, 14, 10, 0, 2, 0, 0},
                           {0, 0, 0, 0, 0, 2, 0, 1, 6},
                           {8, 11, 0, 0, 0, 0, 1, 0, 7},
                           {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    int stations, source;

    // Your additional code for train connections and Dijkstra's algorithm for stations goes here
    printf("Enter the number of stations: ");
    scanf("%d", &stations);

    int trainGraph[V_K][V_K];

    // Create the adjacency matrix for train connections based on user input
    createTrainGraph(trainGraph, stations);

    // Get the source station
    printf("Enter the source station: ");
    scanf("%d", &source);

    // Run Dijkstra's algorithm for weighted graph
    dijkstra(graph, 0);

    // Run Dijkstra's algorithm for train connections
    dijkstra_train(trainGraph, source, stations);

    // Create a graph for train routes and find the Minimum Spanning Tree using Kruskal's Algorithm
    printf("\nEnter the number of train routes: ");
    scanf("%d", &stations);

    Graph* trainRouteGraph = createGraph(stations, stations);

    // Input details of each train route and add edges to the graph
    printf("Enter the details of each train route (src, dest, time, cost):\n");
    for (int i = 0; i < stations; i++) {
        int src, dest, time, cost;
        printf("Route %d: ", i + 1);
        scanf("%d %d %d %d", &src, &dest, &time, &cost);
        addEdge(trainRouteGraph, src, dest, time, cost);
    }

    // Find and print the Minimum Spanning Tree using Kruskal's Algorithm for train routes
    kruskalMST(trainRouteGraph);

    // Free dynamically allocated memory for train route graph
    free(trainRouteGraph->edge);
    free(trainRouteGraph);

    return 0;
}
