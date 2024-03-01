#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to check if a page exists in memory frames
bool isPagePresent(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the oldest page in memory frames
int findOldestPageIndex(int arrivalTime[], int numFrames) {
    int oldestIndex = 0;
    for (int i = 1; i < numFrames; i++) {
        if (arrivalTime[i] < arrivalTime[oldestIndex]) {
            oldestIndex = i;
        }
    }
    return oldestIndex;
}

// Function to simulate FCFS page replacement algorithm
int simulateFCFS(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES] = {0}; // Memory frames
    int arrivalTime[MAX_FRAMES] = {0}; // Arrival time of pages in memory frames
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isPagePresent(frames, numFrames, pages[i])) {
            pageFaults++;
            int oldestIndex = findOldestPageIndex(arrivalTime, numFrames);
            frames[oldestIndex] = pages[i];
            arrivalTime[oldestIndex] = i; // Update arrival time of the new page
        }
    }

    return pageFaults;
}

int main() {
    int numPages, numFrames;
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &numPages);

    printf("Enter the page reference string: ");
    int pages[MAX_PAGES];
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    if (numFrames <= 0 || numFrames > MAX_FRAMES) {
        printf("Invalid number of frames. Exiting...\n");
        return 1;
    }

    int pageFaults = simulateFCFS(pages, numPages, numFrames);
    printf("Number of page faults using FCFS page replacement algorithm: %d\n", pageFaults);

    return 0;
}

