#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#define MAX_REQUESTS 100
#define UP_DIRECTION 1
#define DOWN_DIRECTION 0 


void sort_requests(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void cscan_disk_scheduling(int requests[], int num_requests, int initial_head, int max_track, int direction) {
    int total_seek_time = 0;
    int current_position = initial_head;
    
    int sorted_tracks[num_requests + 1]; 
    for (int i = 0; i < num_requests; i++) {
        sorted_tracks[i] = requests[i];
    }
    sorted_tracks[num_requests] = initial_head;
    
    sort_requests(sorted_tracks, num_requests + 1);

    int start_index_in_sorted = -1; 
    for (int i = 0; i < num_requests + 1; i++) {
        if (sorted_tracks[i] == initial_head) { 
            start_index_in_sorted = i;
            break;
        }
    }
    
    printf("\n--- C-SCAN Disk Scheduling ---\n");
    printf("Initial Head Position: %d\n", initial_head);
    printf("Direction of Service: %s\n", (direction == UP_DIRECTION) ? "UP (towards %d)" : "DOWN (towards 0)", max_track);
    printf("Serviced Sequence: %d", initial_head);


    if (direction == UP_DIRECTION) { 
        for (int i = start_index_in_sorted + 1; i < num_requests + 1; i++) {
            total_seek_time += abs(sorted_tracks[i] - current_position);
            current_position = sorted_tracks[i];
            printf(" -> %d", current_position);
        }
        
        if (current_position != max_track) {
            total_seek_time += abs(max_track - current_position);
            current_position = max_track;
        }

        printf(" -> %d (Jump)", 0);
        total_seek_time += abs(max_track - 0); // Total movement includes the large jump
        current_position = 0;
        
        for (int i = 0; i < start_index_in_sorted; i++) {
            total_seek_time += abs(sorted_tracks[i] - current_position);
            current_position = sorted_tracks[i];
            printf(" -> %d", current_position);
        }

    } else { // Direction is DOWN_DIRECTION
        for (int i = start_index_in_sorted - 1; i >= 0; i--) {
            total_seek_time += abs(sorted_tracks[i] - current_position);
            current_position = sorted_tracks[i];
            printf(" -> %d", current_position);
        }
        
        if (current_position != 0) {
            total_seek_time += abs(0 - current_position);
            current_position = 0;
        }
        

        printf(" -> %d (Jump)", max_track);
        total_seek_time += abs(max_track - 0); 
        current_position = max_track;
        
        for (int i = num_requests; i > start_index_in_sorted; i--) {
            if (sorted_tracks[i] != initial_head) { 
                total_seek_time += abs(sorted_tracks[i] - current_position);
                current_position = sorted_tracks[i];
                printf(" -> %d", current_position);
            }
        }
    }

    printf("\n\nResults:\n");
    printf("Total Head Movement (Seek Time): %d tracks\n", total_seek_time);
}

int main() {
    int num_requests;
    int initial_head, max_track, direction;
    int requests[MAX_REQUESTS]; 

    printf("Enter the number of I/O requests (max %d): ", MAX_REQUESTS);
    if (scanf("%d", &num_requests) != 1 || num_requests <= 0 || num_requests > MAX_REQUESTS) {
        printf("Invalid number of requests or exceeds maximum allowed.\n");
        return 1;
    }

    printf("Enter the sequence of disk track requests:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initial_head);

    printf("Enter the total number of cylinders (Max Track Number, e.g., 199): ");
    scanf("%d", &max_track);

    printf("Enter initial direction (%d for UP, %d for DOWN): ", UP_DIRECTION, DOWN_DIRECTION);
    scanf("%d", &direction);

    cscan_disk_scheduling(requests, num_requests, initial_head, max_track, direction);

    return 0;
}