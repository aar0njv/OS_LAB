#include <stdio.h>

struct Process {
    int id;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
    int priority;
};

void sortProcesses(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].priority > p[j].priority)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void sortProcesses2(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].ct > p[j].ct) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculate_time(struct Process p[], int n) {
    int time = 0;
    int completed = 0;
    int min_index;

    while (completed < n) {
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].wt == -1) {
                if (min_index == -1 || p[i].priority < p[min_index].priority) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            p[min_index].wt = time - p[min_index].at;
            p[min_index].tat = p[min_index].wt + p[min_index].bt;
            time += p[min_index].bt;
            completed++;
            p[min_index].ct = p[min_index].tat + p[min_index].at;
        } else {
            time++;
        }
    }
}

void displayResults(struct Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].id,
            processes[i].at,
            processes[i].bt,
            processes[i].priority,
            processes[i].ct,
            processes[i].wt,
            processes[i].tat);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        processes[i].id = i + 1;
        printf("Enter the Arrival Time: ");
        scanf("%d", &processes[i].at);
        printf("Enter the Burst Time: ");
        scanf("%d", &processes[i].bt);
        printf("Enter the Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].wt = -1;
    }

    sortProcesses(processes, n);
    calculate_time(processes, n);
    sortProcesses2(processes, n);
    displayResults(processes, n);

    return 0;
}

