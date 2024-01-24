#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Station {
    char name[50];
    int platformCount;
    // Add other station details as needed
    // For simplicity, this example includes only the station name and platform count
    struct Station* next;
} Station;

typedef struct HashTable {
    Station* table[TABLE_SIZE];
} HashTable;

// Function to create a new station node
Station* createStationNode(const char* name, int platformCount) {
    Station* newStation = (Station*)malloc(sizeof(Station));
    strcpy(newStation->name, name);
    newStation->platformCount = platformCount;
    newStation->next = NULL;
    return newStation;
}

// Function to create a hash table
HashTable* createHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Function to calculate the hash value for a given station name
unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash = hash * 31 + name[i];
    }
    return hash % TABLE_SIZE;
}

// Function to insert a station into the hash table
void insertStation(HashTable* hashTable, const char* name, int platformCount) {
    unsigned int hashValue = hashFunction(name);
    Station* newStation = createStationNode(name, platformCount);

    // Insert at the beginning of the linked list (chaining to handle collisions)
    newStation->next = hashTable->table[hashValue];
    hashTable->table[hashValue] = newStation;

    printf("Station '%s' inserted successfully.\n", name);
}

// Function to search for a station in the hash table
Station* searchStation(HashTable* hashTable, const char* name) {
    unsigned int hashValue = hashFunction(name);
    Station* current = hashTable->table[hashValue];

    // Traverse the linked list to find the station
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Station found
        }
        current = current->next;
    }

    return NULL; // Station not found
}

// Function to display all stations in the hash table
void displayStations(HashTable* hashTable) {
    printf("\nStation Information:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Station* current = hashTable->table[i];
        while (current != NULL) {
            printf("Station: %s, Platforms: %d\n", current->name, current->platformCount);
            current = current->next;
        }
    }
}

// Function to free memory allocated for the hash table
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Station* current = hashTable->table[i];
        while (current != NULL) {
            Station* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
}

int main() {
    HashTable* hashTable = createHashTable();
    int choice;

    do {
        printf("\nTrain Route Optimization - Station Information\n");
        printf("1. Insert Station\n");
        printf("2. Search Station\n");
        printf("3. Display Stations\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert Station
                {
                    char name[50];
                    int platformCount;
                    printf("Enter station name: ");
                    scanf("%s", name);
                    printf("Enter platform count: ");
                    scanf("%d", &platformCount);
                    insertStation(hashTable, name, platformCount);
                }
                break;

            case 2:
                // Search Station
                {
                    char name[50];
                    printf("Enter station name to search: ");
                    scanf("%s", name);
                    Station* foundStation = searchStation(hashTable, name);
                    if (foundStation != NULL) {
                        printf("Station '%s' found. Platforms: %d\n", foundStation->name, foundStation->platformCount);
                    } else {
                        printf("Station '%s' not found.\n", name);
                    }
                }
                break;

            case 3:
                // Display Stations
                displayStations(hashTable);
                break;

            case 4:
                // Exit
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    // Free allocated memory
    freeHashTable(hashTable);

    return 0;
}
