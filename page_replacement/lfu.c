#include<stdio.h>

#define MAX_FRAMES 10

int frames[MAX_FRAMES], freq[MAX_FRAMES], count = 0;

// Helper: find page index
int findFrameLFU(int page, int framesize) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}

// Helper: find LFU index
int findLFU(int framesize) {
    int minf = freq[0], minidx = 0;
    for (int i = 1; i < framesize; i++) {
        if (freq[i] < minf) {
            minf = freq[i];
            minidx = i;
        }
    }
    return minidx;
}

void lfuPageReplace(int pages[], int n, int framesize) {
    int pagefaults = 0;
    count = 0;
    for (int i = 0; i < framesize; i++)
        freq[i] = 0;

    printf("\nLFU Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        printf("Page %d ->", pages[i]);

        int idx = findFrameLFU(pages[i], framesize);
        if (idx == -1) {
            pagefaults++;
            if (count < framesize) {
                frames[count] = pages[i];
                freq[count] = 1;
                count++;
            } else {
                int lfu_idx = findLFU(framesize);
                printf("Replacing Page %d ->", frames[lfu_idx]);
                frames[lfu_idx] = pages[i];
                freq[lfu_idx] = 1;
            }
        } else {
            printf("Page Hit ->");
            freq[idx]++;
        }

        printf("Frames: ");
        for (int j = 0; j < framesize; j++) {
            if (j < count) {
                printf("%d(%d) ", frames[j], freq[j]);
            }
            else printf("_ ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pagefaults);
}



int main() {
    int n, framesize;
    printf("Enter the number of pages : ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference sequence : ");
    for (int i=0 ; i<n ; i++) scanf("%d",&pages[i]);
    printf("Enter the frame size : ");
    scanf("%d",&framesize);

    lfuPageReplace(pages, n, framesize);
    return 0;
}
