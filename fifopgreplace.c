#include <stdio.h>

#define MAX_FRAMES 10 

int frames[MAX_FRAMES], front = 0, rear = 0, count = 0;


int isPageInFrames(int page, int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == page) {
            return 1; // Page hit
        }
    }
    return 0; // Page fault
}


void fifoPageReplacement(int pages[], int n, int frameSize) {
    int pageFaults = 0;

    printf("\nPage Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);

        if (!isPageInFrames(pages[i], frameSize)) {
     
            pageFaults++;

            if (count < frameSize) {
              
                frames[rear] = pages[i];
                rear = (rear + 1) % frameSize;
                count++;
            } else {
          
                printf("Replacing Page %d -> ", frames[front]);
                frames[front] = pages[i];
                front = (front + 1) % frameSize;
            }
        } else {
            printf("Page hit -> ");
        }

        printf("Frames: ");
        for (int j = 0; j < frameSize; j++) {
            if (j < count) {
                printf("%d ", frames[j]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frameSize;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    
    printf("Enter page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frameSize);

    fifoPageReplacement(pages, n, frameSize);

    return 0;
}
