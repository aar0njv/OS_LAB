#include<stdio.h>

#define MAX_FRAMES 10

int frames[MAX_FRAMES], front = 0, rear = 0, count= 0;

int isInFrame(int page, int framesize) {
        for (int i=0 ; i<framesize ; i++) {
            if (frames[i] == page) {
                return 1;
            }
        }
        return 0;
}

void fifoPageReplace(int pages[], int n, int framesize) {
    int pagefaults = 0;

    printf("\nPage Replacement Process : \n");

    for (int i=0 ; i<n ; i++) {
        printf("Page %d ->", pages[i]);

        if(!isInFrame(pages[i],framesize)) {
            pagefaults++;

            if(count < framesize) {
                frames[rear] = pages[i];
                rear = (rear+1)%framesize;
                count++;

            } else {
                printf("Replacing Page %d ->", frames[front]);
                frames[front] = pages[i];
                front = (front+1)%framesize;

            }


        } else {
            printf("Page Hit ->");
        }
        printf("Frames: ");
        for (int j = 0; j < framesize; j++) {
            if (j < count) {
                printf("%d ", frames[j]);
            } else {
                printf("_ ");
            }
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

    for (int i=0 ; i<n ; i++) {
        scanf("%d",&pages[i]);
    }

    printf("Enter the frame size : ");
    scanf("%d",&framesize);

    fifoPageReplace(pages, n, framesize);

    return 0;

}