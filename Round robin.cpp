#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

struct Process {
    int processId;
    int burstTime;
    int remainingBurstTime;
    int turnaroundTime;
    int waitingTime;
};

void roundRobin(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingBurstTime > 0) {
                int executionTime = (processes[i].remainingBurstTime > TIME_QUANTUM) ? TIME_QUANTUM : processes[i].remainingBurstTime;

                currentTime += executionTime;
                processes[i].remainingBurstTime -= executionTime;

                if (processes[i].remainingBurstTime == 0) {
                    completedProcesses++;
                    processes[i].turnaroundTime = currentTime - processes[i].waitingTime;
                }

                processes[i].waitingTime = currentTime;
            }
        }
    }
}

void displayResults(struct Process processes[], int n) {
    printf("Process\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].burstTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }

    float averageTurnaroundTime = 0, averageWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        averageTurnaroundTime += processes[i].turnaroundTime;
        averageWaitingTime += processes[i].waitingTime;
    }

    averageTurnaroundTime /= n;
    averageWaitingTime /= n;

    printf("\nAverage Turnaround Time: %.2f\n", averageTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
}

int main() {
    int n;
    char buffer[256]; // Buffer for input

    printf("Enter the number of processes: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Exiting...\n");
        return 1;
    }

    struct Process processes[MAX_PROCESSES];

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter burst time for Process %d: ", processes[i].processId);
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &processes[i].burstTime);
        processes[i].remainingBurstTime = processes[i].burstTime;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    // Apply Round Robin scheduling algorithm
    roundRobin(processes, n);

    // Display results
    displayResults(processes, n);

    return 0;
}

