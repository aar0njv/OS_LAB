#include<stdio.h>

#define MAX_FRAMES 10

int frames[MAX_FRAMES], count = 0;


int findFrame(int page, int framesize) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page) return i;
    return -1;
}


void updateLRU(int idx, int framesize) {
    int temp = frames[idx];
    for (int i = idx; i < count - 1; i++)
        frames[i] = frames[i + 1];
    frames[count - 1] = temp;
}

void lruPageReplace(int pages[], int n, int framesize) {
    int pagefaults = 0;

    printf("\nLRU Page Replacement Process:\n");

    count = 0;
    for (int i = 0; i < n; i++) {
        printf("Page %d ->", pages[i]);

        int idx = findFrame(pages[i], framesize);
        if (idx == -1) {
            pagefaults++;
            if (count < framesize) {
                frames[count++] = pages[i];
            } else {
                printf("Replacing Page %d ->", frames[0]);
                for (int j = 0; j < framesize - 1; j++)
                    frames[j] = frames[j + 1];
                frames[framesize - 1] = pages[i];
            }
        } else {
            printf("Page Hit ->");
            updateLRU(idx, framesize);
        }

        printf("Frames: ");
        for (int j = 0; j < framesize; j++) {
            if (j < count) printf("%d ", frames[j]);
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

    lruPageReplace(pages, n, framesize);
    return 0;
}
