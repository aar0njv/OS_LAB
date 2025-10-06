#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fcfs_disk_scheduling(int requests[], int num_requests, int head) {
    int total_seek = 0;
    int current_head = head;

    printf("\n---FCFS Disk Scheduling---\n");

    printf("%d", head);

    for (int i=0 ; i<num_requests ; i++) {
        int requested = requests[i];

        int seek_distance = abs(requested - current_head);

        total_seek += seek_distance;

        current_head = requested;

        printf(" -> %d", requested);
    }

    printf("\nInitial Head Position: %d\n", head);
    printf("Total Head Movement (Seek Time): %d tracks\n", total_seek);


}

int main() {

    int num_requests, head;

    printf("Enter the number of I/O requests: ");
    scanf("%d", &num_requests);

    int requests[num_requests];

    for (int i=0 ; i<num_requests ; i++) {
        printf("Enter the %dth request: ", i+1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head: ");
    scanf("%d", &head);

    fcfs_disk_scheduling(requests, num_requests, head);

    return 0;

}