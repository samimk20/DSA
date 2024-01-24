#include <stdio.h>
#include <limits.h>

#define MAX_STATIONS 100

// Function to find the vertex with the minimum distance value
int minDistance(int distance[], int shortestPathSet[], int stations) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < stations; v++) {
        if (shortestPathSet[v] == 0 && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the final shortest path
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the solution
void printSolution(int distance[], int parent[], int source, int stations) {
    printf("Source: %d\n", source);
    printf("Station\t\tDistance\tPath\n");

    for (int i = 0; i < stations; i++) {
        if (i != source) {
            printf("%d -> %d\t\t%d\t\t%d", source, i, distance[i], source);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX_STATIONS][MAX_STATIONS], int source, int stations) {
    int distance[MAX_STATIONS];    // Distance from source to i
    int shortestPathSet[MAX_STATIONS]; // Shortest path set
    int parent[MAX_STATIONS];  // To store the shortest path tree

    // Initialize all distances as INFINITE and shortestPathSet[] as 0
    for (int i = 0; i < stations; i++) {
        distance[i] = INT_MAX;
        shortestPathSet[i] = 0;
        parent[i] = -1;
    }

    // Distance from source to itself is always 0
    distance[source] = 0;

    // Find shortest path for all stations
    for (int count = 0; count < stations - 1; count++) {
        int u = minDistance(distance, shortestPathSet, stations);

        // Mark the selected vertex as processed
        shortestPathSet[u] = 1;

        // Update distance value of the adjacent stations
        for (int v = 0; v < stations; v++) {
            if (!shortestPathSet[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the constructed distance array and path
    printSolution(distance, parent, source, stations);
}

int main() {
    int stations, source;

    // Get the number of stations
    printf("Enter the number of stations: ");
    scanf("%d", &stations);

    int graph[MAX_STATIONS][MAX_STATIONS];

    // Get the adjacency matrix representing train connections
    printf("Enter the adjacency matrix for train connections:\n");
    for (int i = 0; i < stations; i++) {
        for (int j = 0; j < stations; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Get the source station
    printf("Enter the source station: ");
    scanf("%d", &source);

    // Run Dijkstra's algorithm
    dijkstra(graph, source, stations);

    return 0;
}
