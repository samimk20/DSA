#include <stdio.h>
#include <limits.h>

#define V 9

// Function to find the vertex with the minimum distance value, from the set of vertices not yet included in the Shortest Path Tree (SPT)
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < V; v++)
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

// Function to print the solution, including distances and paths
void printSolution(int dist[], int n, int parent[]) {
    int src = 0;
    printf("Vertex\t Distance\tPath");
  
    for (int i = 1; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

// Dijkstra's algorithm to find the shortest paths from a given source vertex to all other vertices in a weighted graph
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int parent[V];
    int sptSet[V];
  
    // Initialize all distances as INFINITE, sptSet[] as false, and parent[] as -1
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0, parent[i] = -1;
  
    // Distance from the source vertex to itself is always 0
    dist[src] = 0;
  
    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);
  
        // Mark the picked vertex as processed
        sptSet[u] = 1;
  
        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u, dist[v] = dist[u] + graph[u][v];
            }
    }
  
    // Print the solution
    printSolution(dist, V, parent);
}

// Main function
int main() {
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
  
    // Run Dijkstra's algorithm with the given graph and source vertex
    dijkstra(graph, 0);
  
    return 0;
}
