#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 100
#define MAX_PROCESSES 10

// Structure to represent a memory block
struct MemoryBlock {
    int start;
    int size;
    int processId;
};

// Function to initialize the memory blocks
void initializeMemory(struct MemoryBlock memory[], int size) {
    for (int i = 0; i < size; i++) {
        memory[i].start = i * 10;
        memory[i].size = 10;
        memory[i].processId = -1;
    }
}

// Function to display the memory allocation graph
void displayMemoryGraph(struct MemoryBlock memory[], int size) {
    printf("Memory Allocation Graph:\n");
    for (int i = 0; i < size; i++) {
        if (memory[i].processId == -1) {
            printf("|          ");
        } else {
            printf("|  P%d(%2d)  ", memory[i].processId, memory[i].size);
        }
    }
    printf("|\n");
}

// Function to allocate memory using best fit algorithm
void bestFit(struct MemoryBlock memory[], int numBlocks, int processId, int processSize) {
    int bestFitIndex = -1;
    int minFragmentation = MEMORY_SIZE + 1;

    for (int i = 0; i < numBlocks; i++) {
        if (memory[i].processId == -1 && memory[i].size >= processSize) {
            int fragmentation = memory[i].size - processSize;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].processId = processId;
        memory[bestFitIndex].size = processSize;
    } else {
        printf("Memory allocation failed for Process %d\n", processId);
    }
}

int main() {
    struct MemoryBlock memory[MEMORY_SIZE / 10];
    initializeMemory(memory, MEMORY_SIZE / 10);

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    if (numProcesses <= 0 || numProcesses > MAX_PROCESSES) {
        printf("Invalid number of processes. Exiting...\n");
        return 1;
    }

    printf("Enter the size of each process:\n");
    for (int i = 1; i <= numProcesses; i++) {
        int processSize;
        printf("Process %d size: ", i);
        scanf("%d", &processSize);
        bestFit(memory, MEMORY_SIZE / 10, i, processSize);
    }

    displayMemoryGraph(memory, MEMORY_SIZE / 10);

    return 0;
}

