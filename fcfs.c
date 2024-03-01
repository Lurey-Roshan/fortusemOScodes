#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0;
	int i;
    for (i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
	int i;
    for ( i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void displayResults(struct Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
	int i;
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    float averageWaitingTime = 0, averageTurnaroundTime = 0;
    for (i = 0; i < n; i++) {
        averageWaitingTime += processes[i].waitingTime;
        averageTurnaroundTime += processes[i].turnaroundTime;
    }

    averageWaitingTime /= n;
    averageTurnaroundTime /= n;

    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Exiting...\n");
        return 1;
    }

    struct Process processes[MAX_PROCESSES];

    // Input process details
    for (i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", processes[i].processId);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", processes[i].processId);
        scanf("%d", &processes[i].burstTime);
    }

    // Calculate waiting time and turnaround time
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    // Display results
    displayResults(processes, n);

    return 0;
}
