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

// Function to find the index of the least recently used page in memory frames
int findLRUPageIndex(int arrivalTime[], int numFrames) {
    int lruIndex = 0;
    for (int i = 1; i < numFrames; i++) {
        if (arrivalTime[i] < arrivalTime[lruIndex]) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

// Function to simulate LRU page replacement algorithm
int simulateLRU(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES] = {0}; // Memory frames
    int arrivalTime[MAX_FRAMES] = {0}; // Arrival time of pages in memory frames
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isPagePresent(frames, numFrames, pages[i])) {
            pageFaults++;
            int lruIndex = findLRUPageIndex(arrivalTime, numFrames);
            frames[lruIndex] = pages[i];
            arrivalTime[lruIndex] = i; // Update arrival time of the new page
        } else {
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == pages[i]) {
                    arrivalTime[j] = i; // Update arrival time of the accessed page
                    break;
                }
            }
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

    int pageFaults = simulateLRU(pages, numPages, numFrames);
    printf("Number of page faults using LRU page replacement algorithm: %d\n", pageFaults);

    return 0;
}

