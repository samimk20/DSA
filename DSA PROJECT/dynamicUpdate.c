#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent train information
typedef struct {
    int trainID;
    char schedule[50];
    // Add other relevant details as needed
} TrainInfo;

// Structure to represent the train schedule system
typedef struct {
    TrainInfo* trains;
    int numTrains;
    int capacity;
} TrainScheduleSystem;

// Function to initialize the train schedule system
void initializeSystem(TrainScheduleSystem* system, int initialCapacity) {
    system->trains = (TrainInfo*)malloc(initialCapacity * sizeof(TrainInfo));
    system->numTrains = 0;
    system->capacity = initialCapacity;
}

// Function to resize the dynamic array when needed
void resizeArray(TrainScheduleSystem* system) {
    system->capacity *= 2;
    system->trains = (TrainInfo*)realloc(system->trains, system->capacity * sizeof(TrainInfo));
}

// Function to insert a new train into the schedule system
void insertTrain(TrainScheduleSystem* system, int trainID, const char* schedule) {
    if (system->numTrains == system->capacity) {
        resizeArray(system);
    }

    // Add the new train to the end of the array
    system->trains[system->numTrains].trainID = trainID;
    strcpy(system->trains[system->numTrains].schedule, schedule);
    system->numTrains++;

    printf("Train %d inserted successfully.\n", trainID);
}

// Function to find the index of a train in the schedule system
int findTrainIndex(TrainScheduleSystem* system, int trainID) {
    for (int i = 0; i < system->numTrains; i++) {
        if (system->trains[i].trainID == trainID) {
            return i; // Train found, return its index
        }
    }
    return -1; // Train not found
}

// Function to remove a train from the schedule system
void removeTrain(TrainScheduleSystem* system, int trainID) {
    int index = findTrainIndex(system, trainID);
    if (index != -1) {
        // Move the last train in the array to the removed train's position
        system->trains[index] = system->trains[system->numTrains - 1];
        system->numTrains--;

        printf("Train %d removed successfully.\n", trainID);
    } else {
        printf("Train %d not found.\n", trainID);
    }
}

// Function to adjust the schedule of a train
void adjustSchedule(TrainScheduleSystem* system, int trainID, const char* newSchedule) {
    int index = findTrainIndex(system, trainID);
    if (index != -1) {
        // Update the schedule of the specified train
        strcpy(system->trains[index].schedule, newSchedule);

        printf("Schedule adjusted for Train %d.\n", trainID);
    } else {
        printf("Train %d not found.\n", trainID);
    }
}

// Function to display the current train schedule
void displaySchedule(TrainScheduleSystem* system) {
    printf("\nTrain Schedule:\n");
    for (int i = 0; i < system->numTrains; i++) {
        printf("Train ID: %d, Schedule: %s\n", system->trains[i].trainID, system->trains[i].schedule);
    }
}

// Function to free memory allocated for the train schedule system
void freeSystem(TrainScheduleSystem* system) {
    free(system->trains);
}

int main() {
    TrainScheduleSystem trainSystem;
    initializeSystem(&trainSystem, 5); // Initial capacity of 5 trains

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

    // Free allocated memory
    freeSystem(&trainSystem);

    return 0;
}
