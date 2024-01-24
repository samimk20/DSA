#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_CAPACITY 3  // Declare cache capacity

// Structure to represent a train route
typedef struct {
    char source[50];
    char destination[50];
    // Add other relevant details as needed
} TrainRoute;

// Structure to represent a cached route
typedef struct {
    TrainRoute originalRoute;
    TrainRoute optimizedRoute;
} CachedRoute;

// Function to perform train route optimization
TrainRoute optimizeRoute(const TrainRoute* originalRoute) {
    // Placeholder optimization logic
    // Modify this function as needed for your optimization algorithm
    TrainRoute optimizedRoute;
    strcpy(optimizedRoute.source, originalRoute->source);
    strcpy(optimizedRoute.destination, originalRoute->destination);
    return optimizedRoute;
}

// Function to check if a route is present in the cache
int isInCache(const CachedRoute* cache, int cacheSize, const TrainRoute* route) {
    for (int i = 0; i < cacheSize; i++) {
        if (strcmp(cache[i].originalRoute.source, route->source) == 0 &&
            strcmp(cache[i].originalRoute.destination, route->destination) == 0) {
            return i; // Route found in cache, return its index
        }
    }
    return -1; // Route not found in cache
}

// Function to add a route to the cache
void addToCache(CachedRoute* cache, int* cacheSize, const TrainRoute* originalRoute, const TrainRoute* optimizedRoute) {
    // Check if the cache is full
    if (*cacheSize == CACHE_CAPACITY) {
        // Remove the oldest entry (assuming FIFO replacement strategy)
        for (int i = 0; i < CACHE_CAPACITY - 1; i++) {
            cache[i] = cache[i + 1];
        }
        (*cacheSize)--;
    }

    // Add the new entry to the cache
    cache[*cacheSize].originalRoute = *originalRoute;
    cache[*cacheSize].optimizedRoute = *optimizedRoute;
    (*cacheSize)++;
}

// Function to perform train route optimization with caching
TrainRoute optimizeRouteWithCache(CachedRoute* cache, int* cacheSize, const TrainRoute* route) {
    // Check if the route is present in the cache
    int cacheIndex = isInCache(cache, *cacheSize, route);

    if (cacheIndex != -1) {
        // Route found in cache, return the optimized route from the cache
        printf("Route found in cache.\n");
        return cache[cacheIndex].optimizedRoute;
    } else {
        // Route not found in cache, perform optimization
        TrainRoute optimizedRoute = optimizeRoute(route);

        // Add the route and its optimized version to the cache
        addToCache(cache, cacheSize, route, &optimizedRoute);

        return optimizedRoute;
    }
}

int main() {
    TrainRoute route;
    CachedRoute cache[CACHE_CAPACITY];
    int cacheSize = 0;

    printf("Enter the source station: ");
    scanf("%s", route.source);
    printf("Enter the destination station: ");
    scanf("%s", route.destination);

    TrainRoute optimizedRoute = optimizeRouteWithCache(cache, &cacheSize, &route);

    printf("\nOptimized Route:\n");
    printf("Source: %s\n", optimizedRoute.source);
    printf("Destination: %s\n", optimizedRoute.destination);

    return 0;
}
