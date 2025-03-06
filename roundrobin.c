#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int name;
    int arrival;
    int burst;
    int remaining;
    int status;
    int completion;
    int waiting;
    int turnaround;
} Process;

typedef struct Node {
    Process process;
    struct Node* next;
} Node;

Node *front = NULL, *rear = NULL;

// Function to enqueue a process into the queue
void enqueue(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;
    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Function to dequeue a process from the queue
Process dequeue() {
    Node* temp = front;
    Process process = temp->process;
    front = front->next;
    free(temp);
    return process;
}

// Function to check if the queue is empty
int isEmpty() {
    return front == NULL;
}

int main() {
    int n = 6;  // Number of processes
    int quantum = 4;  // Time quantum

    // Predefined process list
    Process processes[] = {
        {1, 0, 5, 5, 0, -1, -1, -1},  
        {2, 1, 6, 6, 0, -1, -1, -1},  
        {3, 2, 3, 3, 0, -1, -1, -1},
        {4, 3, 1, 1, 0, -1, -1, -1},  
        {5, 4, 5, 5, 0, -1, -1, -1},  
        {6, 6, 4, 4, 0, -1, -1, -1}
    };

    int current_time = 0;
    int completed = 0;

    // Enqueue the first process if it has arrived at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival == 0) {
            enqueue(processes[i]);
            processes[i].status = 1;
        }
    }

    // Round Robin execution
    printf("Gantt Chart:\n");
    while (completed < n) {
        if (!isEmpty()) {
            Process currentProcess = dequeue();
            int execution_time = (currentProcess.remaining < quantum) ? currentProcess.remaining : quantum;
            currentProcess.remaining -= execution_time;
            current_time += execution_time;

            // Check for new arrivals
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival <= current_time && processes[i].status == 0) {
                    enqueue(processes[i]);
                    processes[i].status = 1;
                }
            }

            // Print execution step
            printf("Time %d -> P%d\n", current_time, currentProcess.name);

            // If process completed, store completion time
            if (currentProcess.remaining == 0) {
                completed++;
                for (int i = 0; i < n; i++) {
                    if (processes[i].name == currentProcess.name) {
                        processes[i].completion = current_time;
                        break;
                    }
                }
            } else {
                enqueue(currentProcess);
            }
        } else {
            current_time++;
        }
    }

    // Compute turnaround time and waiting time
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        total_wt += processes[i].waiting;
        total_tat += processes[i].turnaround;

        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
            processes[i].name, processes[i].arrival, processes[i].burst,
            processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }

    // Calculate and print averages
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}

