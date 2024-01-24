#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to represent train station information
typedef struct {
    char name[50];
    char location[50];
    // Add other relevant details as needed
} StationInfo;

// Function to input train station information
void inputStationInfo(StationInfo* station) {
    printf("Enter station name: ");
    scanf("%s", station->name);

    printf("Enter station location: ");
    scanf("%s", station->location);

    // Add additional input for other details as needed
}

// Function to display train station information
void displayStationInfo(const StationInfo* station) {
    printf("Station Name: %s\n", station->name);
    printf("Station Location: %s\n", station->location);
    // Add additional display for other details as needed
}

int main() {
    int numStations;

    printf("Enter the number of train stations: ");
    scanf("%d", &numStations);

    // Dynamically allocate an array of StationInfo structures
    StationInfo* stations = (StationInfo*)malloc(numStations * sizeof(StationInfo));

    // Input information for each station
    for (int i = 0; i < numStations; i++) {
        printf("\nEnter information for Station %d:\n", i + 1);
        inputStationInfo(&stations[i]);
    }

    // Display information for each station
    printf("\nTrain Station Information:\n");
    for (int i = 0; i < numStations; i++) {
        printf("\nStation %d:\n", i + 1);
        displayStationInfo(&stations[i]);
    }

    // Free dynamically allocated memory
    free(stations);

    return 0;
}
