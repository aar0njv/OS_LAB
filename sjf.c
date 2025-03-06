

#include <stdio.h>



struct Process {

	 int id; // Process ID
	 int at; // Arrival Time
	 int bt; // Burst Time
	 int wt; // Waiting Time
	 int tat; // Turnaround Time
	 int ct;

	};


void sortProcesses(struct Process p[], int n) {
 struct Process temp;
 for (int i = 0; i < n - 1; i++) {

	 for (int j = i + 1; j < n; j++) {
		 if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].bt > p[j].bt)) {
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
	 int min_bt;

	 while (completed < n) {
	 	min_index = -1;
	 	min_bt = 9999; // A large number to find the minimum

	 for (int i = 0; i < n; i++) {
		 if (p[i].at <= time && p[i].wt == -1 && p[i].bt < min_bt) {
			 min_bt = p[i].bt;
			 min_index = i;
	 		}
	 }

	 if (min_index != -1){
		 p[min_index].wt = time - p[min_index].at; // Calculate waiting time
		 p[min_index].tat = p[min_index].wt + p[min_index].bt; // Calculate turnaround time
		 time += p[min_index].bt; // Update current time
		 completed++;
		 p[min_index].ct = p[min_index].tat + p[min_index].at;

	 } 
	 else {
	 	time++;
	   }
     }

}


void displayResults(struct Process processes[], int n) {

	 printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

	 for (int i = 0; i < n; i++) {

		 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
		 processes[i].id, 
		 processes[i].at, 
		 processes[i].bt, 
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
	 processes[i].id = i + 1; // Assigning process ID
	 printf("Enter the Arrival Time: ");
	 scanf("%d", &processes[i].at);
	 printf("Enter the Burst Time: ");
	 scanf("%d", &processes[i].bt);
	 processes[i].wt = -1; // Initialize waiting time to -1 (not yet calculated)

	 }



 sortProcesses(processes, n); // Sort processes by arrival time
 calculate_time(processes, n); // Calculate waiting and turnaround times
 sortProcesses2(processes , n);
 displayResults(processes, n); // Display the results

 return 0;

}


