#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

bool isSafeState(int available, int allocation[], int need[], int numProcesses) {
    int work = available;

    // Iterate through each process
    for (int i = 0; i < numProcesses; i++) {
        if (need[i] <= work) { // Check if the process's resource needs can be met
            work += allocation[i]; // Release resources allocated to the process
        } else {
            return false; // Unsafe state
        }
    }
    return true; // Safe state
}

int main() {
    int available;
    printf("Enter the number of available resources: ");
    scanf("%d", &available);

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    int allocation[MAX_PROCESSES];
    int need[MAX_PROCESSES];

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &allocation[i]);
    }

    // Input need matrix
    printf("Enter need matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &need[i]);
    }

    // Check if the system is in a safe state
    if (isSafeState(available, allocation, need, numProcesses)) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}

