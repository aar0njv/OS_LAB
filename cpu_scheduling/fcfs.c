#include <stdio.h>

void sortProcesses(int processes[], int n, int arrival[], int burst[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrival[j] > arrival[j + 1]) {
                int temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;

                temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;
            }
        }
    }
}


void findWaiting(int processes[], int n, int burst[], int arrival[], int waiting[],int completion[]) {
    completion[0] = arrival[0] + burst[0];
    waiting[0] = 0;

    for (int i = 1; i < n; i++) {
    
       if (arrival[i] > completion[i-1]) {
    
       		completion[i] = arrival[i] + burst[i];
       		waiting[i] = 0;
    
       		} 
       		
       else  {
       
       			completion[i] = completion[i-1] + burst[i];
       			waiting[i] = completion[i-1] - arrival[i];
       			
        }
    }
}

void findTAT(int processes[], int n, int burst[], int completion[], int arrival[], int TAT[]) {
    
    for (int i = 0; i < n; i++) {
    
        TAT[i] = completion[i] - arrival[i];
    }
}

void findAvgTime(int processes[], int n, int arrival[], int burst[]) {

    int waiting[n], TAT[n], completion[n];

    findWaiting(processes, n, burst, arrival, waiting, completion);
    findTAT(processes, n, burst, completion, arrival, TAT);

    float totalWaiting = 0, totalTAT = 0;

    printf("Process ID\tArrival Time\tBurst Time\tCompletion\tWaiting Time\tTurnAround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaiting += waiting[i];
        totalTAT += TAT[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival[i], burst[i], completion[i], waiting[i], TAT[i]);
    }
    printf("Average Waiting Time: %f\n", totalWaiting / n);
    printf("Average TurnAround Time: %f\n", totalTAT / n);
}



int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], arrival[n], burst[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter the arrival time: ");
        scanf("%d", &arrival[i]);
        printf("Enter the burst time: ");
        scanf("%d", &burst[i]);
    }

    sortProcesses(processes, n, arrival, burst);
    findAvgTime(processes, n, arrival, burst);

    return 0;
}
