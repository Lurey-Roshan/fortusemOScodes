#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // Include for sleep function on Windows

// Global variable to signal the thread to terminate
volatile int terminateThread = 0;

// Function that the thread will execute
void* threadFunction(void* arg) {
    while (!terminateThread) {
        // Simulate some work
        printf("Thread is running...\n");
        sleep(1);  // Simulating work using sleep
    }

    printf("Thread is terminating\n");

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t threadId;

    // Create the thread
    if (pthread_create(&threadId, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Allow some time for the thread to run (simulating main program work)
    sleep(5);

    // Set the flag to terminate the thread
    terminateThread = 1;

    // Wait for the thread to finish
    if (pthread_join(threadId, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Main program is continuing...\n");

    return 0;
}