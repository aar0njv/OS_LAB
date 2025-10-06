#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 20

// Function to implement the correct Round Robin algorithm using an array-based queue
void round_robin_scheduling() {
    int n, tq;
    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    int process[MAX_PROCESSES], arrival[MAX_PROCESSES], burst[MAX_PROCESSES], remaining[MAX_PROCESSES];
    // status: 0=Not Arrived, 1=Ready/In Queue, 2=Completed
    int status[MAX_PROCESSES]; 

    for(int i = 0; i < n; i++){
        process[i] = i + 1;
        printf("Enter the arrival time of P%d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter the burst time of P%d: ", i + 1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
        status[i] = 0; // Initialize status to Not Arrived
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    
    int current_time = 0;
    int completed_count = 0;

    int completion[MAX_PROCESSES], waiting[MAX_PROCESSES], tat[MAX_PROCESSES];
    
    // --- Array-Based FIFO Queue Simulation ---
    // Stores the index (0 to n-1) of the process
    int ready_queue[MAX_PROCESSES * 2]; 
    int front = 0, rear = 0;
    
    // Flag to track if the CPU was idle in the last step for print formatting
    int was_idle = 0; 

    // Helper to check for and enqueue new arrivals up to the current time
    void check_and_enqueue_arrivals() {
        for(int i = 0; i < n; i++) {
            if (status[i] == 0 && arrival[i] <= current_time) {
                ready_queue[rear++] = i;
                status[i] = 1; // Mark as Ready/In Queue
            }
        }
    }

    printf("\nGantt Chart: (Time : Process) \n");

    // 1. Initial check at time 0
    check_and_enqueue_arrivals();

    while (completed_count < n) {
        
        // --- 2. CPU Idle Check ---
        // If queue is empty (front == rear) AND not all processes are done
        if (front == rear) { 
            // If we were just running, and the queue is now empty, we need to check if any process will arrive soon.
            if (was_idle == 0) {
                 printf("%d:IDLE ", current_time);
            }
            was_idle = 1;
            current_time++;
            
            // Check for new arrivals after advancing time
            check_and_enqueue_arrivals();
            continue; 
        }

        // --- 3. Execute Process ---
        was_idle = 0;
        int current_process_index = ready_queue[front++]; // Dequeue
        
        int exec_time = (remaining[current_process_index] < tq) ? remaining[current_process_index] : tq;
        int start_time = current_time;

        // Execute: update remaining time and current time
        remaining[current_process_index] -= exec_time;
        current_time += exec_time;

        printf("%d:P%d ", start_time, current_process_index + 1);

        // --- 4. Check for New Arrivals DURING Execution ---
        // New processes arriving up to the *new* current_time must be enqueued first.
        check_and_enqueue_arrivals();

        // --- 5. Completion or Re-enqueue ---
        if (remaining[current_process_index] == 0) {
            completed_count++;
            completion[current_process_index] = current_time;
            status[current_process_index] = 2; // Mark as Completed
        } else {
            // Re-enqueue (Preemption): Add the unfinished process to the rear of the queue
            ready_queue[rear++] = current_process_index;
        }
    }

    printf("%d: END \n", current_time);

    // --- Calculation and Output ---
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    for (int j = 0; j < n; j++) {
        tat[j] = completion[j] - arrival[j];
        waiting[j] = tat[j] - burst[j];
        total_wt += waiting[j];
        total_tat += tat[j];

        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
            j + 1, arrival[j], burst[j],
            completion[j], tat[j], waiting[j]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    round_robin_scheduling();
    return 0;
}