#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Dijkstra's Algorithm Declarations
#define V 9

int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j);
void printSolution(int dist[], int n, int parent[]);
void dijkstra(int graph[V][V], int src);

// Train Schedule System Declarations
typedef struct {
    int trainID;
    char schedule[50];
} TrainInfo;

typedef struct {
    TrainInfo* trains;
    int numTrains;
    int capacity;
} TrainScheduleSystem;

void initializeSystem(TrainScheduleSystem* system, int initialCapacity);
void resizeArray(TrainScheduleSystem* system);
void insertTrain(TrainScheduleSystem* system, int trainID, const char* schedule);
void removeTrain(TrainScheduleSystem* system, int trainID);
void adjustSchedule(TrainScheduleSystem* system, int trainID, const char* newSchedule);
void displaySchedule(TrainScheduleSystem* system);
void freeSystem(TrainScheduleSystem* system);

// Binary Search Tree Declarations
typedef struct TreeNode {
    int routeId;
    int scheduledTime;
    int estimatedCost;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int routeId, int scheduledTime, int estimatedCost);
TreeNode* insert(TreeNode* root, int routeId, int scheduledTime, int estimatedCost);
TreeNode* deleteNode(TreeNode* root, int scheduledTime);
TreeNode* search(TreeNode* root, int scheduledTime);
void inorderTraversal(TreeNode* root);
void freeTree(TreeNode* root);

// Main function
int main() {
    // Dijkstra's Algorithm
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    printf("Dijkstra's Algorithm Results:\n");
    dijkstra(graph, 0);

    // Train Schedule System
    TrainScheduleSystem trainSystem;
    initializeSystem(&trainSystem, 5);

    printf("\nTrain Schedule System:\n");

    int choice;
    do {
        printf("\nTrain Schedule System\n");
        printf("1. Insert Train\n");
        printf("2. Remove Train\n");
        printf("3. Adjust Schedule\n");
        printf("4. Display Schedule\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert Train
                {
                    int trainID;
                    char schedule[50];
                    printf("Enter Train ID: ");
                    scanf("%d", &trainID);
                    printf("Enter Schedule: ");
                    scanf("%s", schedule);
                    insertTrain(&trainSystem, trainID, schedule);
                }
                break;

            case 2:
                // Remove Train
                {
                    int trainID;
                    printf("Enter Train ID to remove: ");
                    scanf("%d", &trainID);
                    removeTrain(&trainSystem, trainID);
                }
                break;

            case 3:
                // Adjust Schedule
                {
                    int trainID;
                    char newSchedule[50];
                    printf("Enter Train ID to adjust schedule: ");
                    scanf("%d", &trainID);
                    printf("Enter New Schedule: ");
                    scanf("%s", newSchedule);
                    adjustSchedule(&trainSystem, trainID, newSchedule);
                }
                break;

            case 4:
                // Display Schedule
                displaySchedule(&trainSystem);
                break;

            case 5:
                // Exit
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    // Free allocated memory for Train Schedule System
    freeSystem(&trainSystem);

    // Binary Search Tree
    TreeNode* root = NULL;
    int numRoutes;

    printf("Enter the number of scheduled routes: ");
    scanf("%d", &numRoutes);

    printf("Enter details for each route (routeId, scheduledTime, estimatedCost):\n");
    for (int i = 0; i < numRoutes; i++) {
        int routeId, scheduledTime, estimatedCost;
        printf("Route %d: ", i + 1);
        scanf("%d %d %d", &routeId, &scheduledTime, &estimatedCost);
        root = insert(root, routeId, scheduledTime, estimatedCost);
    }

    // Print the original scheduled routes
    printf("\nOriginal Scheduled Routes:\n");
    inorderTraversal(root);

    // Perform operations (you can modify this based on your requirements)
    int scheduledTimeToDelete;
    printf("\nEnter the scheduled time to delete a route: ");
    scanf("%d", &scheduledTimeToDelete);
    root = deleteNode(root, scheduledTimeToDelete);

    int scheduledTimeToSearch;
    printf("Enter the scheduled time to search for a route: ");
    scanf("%d", &scheduledTimeToSearch);
    TreeNode* searchResult = search(root, scheduledTimeToSearch);

    // Print the updated scheduled routes
    printf("\nUpdated Scheduled Routes:\n");
    inorderTraversal(root);

    // Print the search result
    if (searchResult != NULL) {
        printf("\nRoute found for scheduled time %d: Route %d\n", scheduledTimeToSearch, searchResult->routeId);
    } else {
        printf("\nNo route found for scheduled time %d.\n", scheduledTimeToSearch);
    }

    // Free allocated memory for Binary Search Tree
    freeTree(root);

    return 0;
}
