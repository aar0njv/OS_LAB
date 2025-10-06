#include<stdio.h>

void sortByArrival(int n, int pid[], int arrival[], int burst[]) {
    for (int i=0 ; i<n-1 ; i++) {
        for (int j=0 ; j<n-i-1 ; j++) {
            if (arrival[j] > arrival[j+1] || (arrival[j] == arrival[j+1] && burst[j] > burst[j+1])) {
                int temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;;

                temp = arrival[j];
                arrival[j] = arrival[j+1];
                arrival[j+1] = temp;
                
                temp = burst[j];
                burst[j] = burst[j+1];
                burst[j+1] = temp;

            }
        }
    }
}

void calculateSJF(int n, int pid[], int arrival[], int burst[], int waiting[], int completion[], int tat[]) {
    int current = 0;
    int completed = 0;
    int min_index, min_bt;

    while (completed < n) {
            min_index = -1;
            min_bt = 99999;

            for (int i=0 ; i<n ; i++) {
                if(arrival[i] <= current && waiting[i] == -1 && burst[i] < min_bt){
                    min_bt = burst[i];
                    min_index = i;
                }
            }
            if (min_index != -1) {

                waiting[min_index] = current - arrival[min_index];
                tat[min_index] = waiting[min_index] + burst[min_index];
                current += burst[min_index];
                completed ++;
                completion[min_index] = tat[min_index] + arrival[min_index];

            } else {
                
                current++;

            }

    }
}


void sortByCompletion(int n, int pid[], int arrival[], int burst[], int waiting[], int completion[], int tat[]) {
    for (int i=0 ; i<n-1 ; i++) {
        for (int j=0 ; j<n-i-1 ; j++) {
            if (completion[j] > completion[j+1]) {
                int temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;;

                temp = arrival[j];
                arrival[j] = arrival[j+1];
                arrival[j+1] = temp;
                
                temp = burst[j];
                burst[j] = burst[j+1];
                burst[j+1] = temp;

                temp = waiting[j];
                waiting[j] = waiting[j+1];
                waiting[j+1] = temp;

                temp = completion[j];
                completion[j] = completion[j+1];
                completion[j+1] = temp;

                temp = tat[j];
                tat[j] = tat[j+1];
                tat[j+1] = temp;

            }
        }
    }
}

void display(int n, int pid[], int arrival[], int burst[], int waiting[], int completion[], int tat[]) {
    printf("\nPROCESS ID\tARRIVAL\tBURST\tWAITING\tCOMPLETION\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("   %d\t\t%d\t%d\t%d\t%d\t\t%d\n", pid[i], arrival[i], burst[i], waiting[i], completion[i], tat[i]);
    }

}


int main() {
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], waiting[n], completion[n], tat[n];

    for (int i=0 ; i<n ; i++) {
        pid[i] = i+1;
        printf("Enter the Arrival Time : ");
        scanf("%d", &arrival[i]);
        printf("Enter the burst time : ");
        scanf("%d", &burst[i]);
        waiting[i] = -1;
        

    }

    sortByArrival(n, pid, arrival, burst);
    calculateSJF(n, pid, arrival, burst, waiting, completion, tat);
    sortByCompletion(n, pid, arrival, burst, waiting, completion, tat);
    display(n, pid, arrival, burst, waiting, completion, tat);

}

