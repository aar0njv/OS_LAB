#include <stdio.h>
#include <stdlib.h>


void main() {
    int n,tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n], remaining[n];
    

    for(int i=0 ; i<n ; i++){
        process[i] = i+1;
        printf("Enter the arrival time of %dth process: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter the burst time of %dth process: ", i+1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];

    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    
    int current_time = 0, completed_count = 0;

    int completion[n], waiting[n], tat[n];

    int did_run = 0;    // to check if a process ran in last cycle

    int i = 0; //current process index

    printf("Gant Chart: (Time : Process) \n");

    while (completed_count < n) {
        if (arrival[i] <= current_time && remaining[i] > 0) {
            int exec_time = (remaining[i] < tq) ? remaining[i] : tq;

            remaining[i] -= exec_time;
            current_time += exec_time;
            did_run = 1;

            printf("%d:P%d ", current_time - exec_time, i+1);

            if (remaining[i] == 0) {
                completed_count++;
                completion[i] = current_time;
            }
        }
    
        i = (i+1) % n;

        if (i==0 && did_run == 0 && completed_count < n) {
            current_time++;
            printf("%d: IDLE ->", current_time - 1);
        }

        if (i == 0){
            did_run = 0;
        }
    }

    printf("%d: END \n", current_time);


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

