#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 5
#define MAX_ARRIVAL_TIME 10
#define MAX_BURST_TIME 5
int arr_time[5],arr_id[5];
int count=0;
typedef struct {
    int pid;
    int priority;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    
} process;

void initialize_processes(process *p, int n);
void print_processes(process *p, int n);
void simulate(process *p, int n, int simulation_time);

void initialize_processes(process *p, int n) {
    int i,j;
    printf("\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\tPriority With Preemption Algorithm SIMULATION STARTS\n");
    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        p[i].pid = i+1;
        p[i].priority = rand() % 10 + 1;
        p[i].arrival_time = rand() % MAX_ARRIVAL_TIME + 1;
        p[i].burst_time = rand() % MAX_BURST_TIME + 1;
        p[i].remaining_time = p[i].burst_time;
        
    }
}

void print_processes(process *p, int n) {
    int i;
    printf("PID\tPriority\tArrival Time\tBurst Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].priority, p[i].arrival_time, p[i].burst_time);
        
    }
}

void simulate(process *p, int n, int simulation_time) {
    
    int i, t, completed = 0;
    process *current_process = NULL;
    printf("Time\tProcess\n");
    for (t = 0; t < simulation_time; t++) {
        
        
            // check if any process arrived at this time
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time == t) {
                printf("%d\tProcess %d arrived\n", t, p[i].pid);
            }
        }
        // check if current process has finished its burst time
        if (current_process != NULL && current_process->remaining_time == 0) {
            arr_time[count]=t;
            arr_id[count]=current_process->pid;
            printf("%d\tProcess %d completed\n", t, current_process->pid);
            completed++;
            current_process = NULL;
            count++;
            
        }
        
        // select the highest priority process that has arrived and has remaining burst time
        if (current_process == NULL||current_process!=NULL) {
            process *highest_priority_process = NULL;
            for (i = 0; i < n; i++) {
                if (p[i].arrival_time <= t && p[i].remaining_time > 0) {
                    if (highest_priority_process == NULL || p[i].priority > highest_priority_process->priority) {
                        highest_priority_process = &p[i];
                    }
                }
            }
            if (highest_priority_process!=NULL) {
                if (current_process == NULL || highest_priority_process->priority > current_process->priority) {
                    current_process = highest_priority_process;
                    printf("%d\tProcess %d started\n", t, current_process->pid);
                    
                }
            }
        }
        // decrement remaining time of current process
        
         if (current_process != NULL) {
            current_process->remaining_time--;
         }
           
         
         
        
        // end simulation if all processes have completed
        
        
        

}
}
int print_final(process *p, int n) {
    int i;
    float wt=0,tat=0;
    printf("PID  Priority  Arrival_Time  Burst_Time  Completion_Time  Turn_Around_Time  Waiting_Time\n");
    for (i = 0; i < n; i++) {
        
        for(int j=0; j<n; j++)
        {
            if(arr_id[j]==p[i].pid)
            {
                int Completion_Time=arr_time[j];
                int TAT=Completion_Time-p[i].arrival_time;
                int WT=TAT-p[i].burst_time;
                tat+=TAT;
                wt+=WT;
                printf("%d\t%d\t    %d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].priority, p[i].arrival_time, p[i].burst_time,Completion_Time,TAT,WT);
            }
        }
        
        
    }
    printf("\n\nAverage Waiting Time is %.2f",wt/5);
    printf("\nAverage TurnAround Time is %.2f",tat/5);
    printf("\n\n:::::::::::::::::::::::::::::::::::::::::::::");
    printf("\n      S I M U L A T I O N     E N D S");
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::\n\n");
}

int main() {
    
    process p[MAX_PROCESSES];
    initialize_processes(p, MAX_PROCESSES);
    printf("\n\n");
    print_processes(p, MAX_PROCESSES);
    
    printf("\n\n");
    simulate(p, MAX_PROCESSES, 50);
    printf("\n\n");
    print_final(p, MAX_PROCESSES);
    return 0;
}


