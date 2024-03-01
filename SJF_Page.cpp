#include <stdio.h>

struct process {
    int pid;  // Process ID
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n, i, j;
    float avg_wait = 0.0, avg_turnaround = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process processes[n];

    // Get process details
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1; // Assign process ID
    }

    // Sort processes by burst time (shortest first)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                // Swap processes
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate waiting time for each process
    processes[0].waiting_time = 0; // No waiting for the first
    for (i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }

    // Calculate turnaround time (waiting + burst)
    for (i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }

    // Calculate average waiting and turnaround times
    for (i = 0; i < n; i++) {
        avg_wait += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    avg_wait /= n;
    avg_turnaround /= n;

    // Print results
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wait);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}

