#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int pid;      // Process ID
    int at;       // Arrival Time
    int bt;       // Burst Time
    int rt;       // Remaining Time (for preemptive)
    int priority; // Priority (lower value means higher priority)
    int ct;       // Completion Time
    int wt;       // Waiting Time
    int tat;      // Turnaround Time
} process;

// Utility function to swap two processes
void swap(process *a, process *b)
{
    process temp = *a;
    *a = *b;
    *b = temp;
}

// FCFS Scheduling
void fcfs(process proc[], int n)
{
    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (proc[j].at > proc[j + 1].at)
                swap(&proc[j], &proc[j + 1]);

    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < proc[i].at)
            current_time = proc[i].at;

        proc[i].ct = current_time + proc[i].bt;
        proc[i].tat = proc[i].ct - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        current_time = proc[i].ct;
    }

    printf("\nFCFS Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }
}

// SJF Preemptive Scheduling (Shortest Remaining Time First)
void sjf_preemptive(process proc[], int n)
{
    int completed = 0, current_time = 0, min_rt, shortest = -1;
    int finish_time, min_index;
    int is_process_running = 0;
    int *rt = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    while (completed != n)
    {
        min_rt = 1e9;
        shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (proc[i].at <= current_time && rt[i] > 0 && rt[i] < min_rt)
            {
                min_rt = rt[i];
                shortest = i;
            }
        }

        if (shortest == -1)
        {
            current_time++;
            continue;
        }

        rt[shortest]--;
        current_time++;

        if (rt[shortest] == 0)
        {
            completed++;
            proc[shortest].ct = current_time;
            proc[shortest].tat = proc[shortest].ct - proc[shortest].at;
            proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
        }
    }
    free(rt);

    printf("\nSJF (Preemptive) Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
}

// Priority Scheduling (Non-Preemptive)
void priority_nonpreemptive(process proc[], int n)
{
    int completed = 0, current_time = 0;
    int is_completed[MAX] = {0};

    while (completed != n)
    {
        int idx = -1;
        int highest_priority = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].at <= current_time && !is_completed[i])
            {
                if (proc[i].priority < highest_priority)
                {
                    highest_priority = proc[i].priority;
                    idx = i;
                }
                else if (proc[i].priority == highest_priority)
                {
                    // If priorities are same, choose the one with earlier arrival time
                    if (proc[i].at < proc[idx].at)
                        idx = i;
                }
            }
        }
        if (idx != -1)
        {
            proc[idx].ct = current_time + proc[idx].bt;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            current_time = proc[idx].ct;
            is_completed[idx] = 1;
            completed++;
        }
        else
        {
            current_time++;
        }
    }

    printf("\nPriority Scheduling (Non-Preemptive):\n");
    printf("PID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].priority, proc[i].ct, proc[i].tat, proc[i].wt);
}

// Round Robin Scheduling (Preemptive)
void round_robin(process proc[], int n, int quantum)
{
    int current_time = 0;
    int completed = 0;
    int queue[MAX];
    int front = 0, rear = 0;
    int is_in_queue[MAX] = {0};
    int *rt = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    // Initially add processes which have arrived at time 0
    for (int i = 0; i < n; i++)
    {
        if (proc[i].at == 0)
        {
            queue[rear++] = i;
            is_in_queue[i] = 1;
        }
    }

    if (rear == 0)
    {
        // No process arrived at time 0, advance time to earliest arrival
        int min_at = proc[0].at;
        for (int i = 1; i < n; i++)
            if (proc[i].at < min_at)
                min_at = proc[i].at;
        current_time = min_at;

        for (int i = 0; i < n; i++)
        {
            if (proc[i].at == current_time)
            {
                queue[rear++] = i;
                is_in_queue[i] = 1;
            }
        }
    }

    while (completed != n)
    {
        if (front == rear)
        {
            // Queue empty, increment time until new process arrives
            current_time++;
            for (int i = 0; i < n; i++)
            {
                if (!is_in_queue[i] && proc[i].at <= current_time && rt[i] > 0)
                {
                    queue[rear++] = i;
                    is_in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (front == MAX)
            front = 0;

        if (rt[idx] > quantum)
        {
            rt[idx] -= quantum;
            current_time += quantum;
        }
        else
        {
            current_time += rt[idx];
            rt[idx] = 0;
            completed++;
            proc[idx].ct = current_time;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
        }

        // Add new processes arrived during this quantum
        for (int i = 0; i < n; i++)
        {
            if (!is_in_queue[i] && proc[i].at <= current_time && rt[i] > 0)
            {
                queue[rear++] = i;
                if (rear == MAX)
                    rear = 0;
                is_in_queue[i] = 1;
            }
        }

        // If the current process still has burst time left, add it back to queue
        if (rt[idx] > 0)
        {
            queue[rear++] = idx;
            if (rear == MAX)
                rear = 0;
        }
    }

    free(rt);

    printf("\nRound Robin Scheduling (Preemptive) with Quantum = %d:\n", quantum);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
}

int main()
{
    int n, choice, quantum;
    process proc[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time, Burst Time and Priority (lower value means higher priority) for each process:\n");
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Process %d:\n", proc[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].at);
        printf("Burst Time: ");
        scanf("%d", &proc[i].bt);
        proc[i].rt = proc[i].bt;
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
    }

    printf("\nSelect CPU Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF (Preemptive)\n3. Priority (Non-Preemptive)\n4. Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fcfs(proc, n);
        break;
    case 2:
        sjf_preemptive(proc, n);
        break;
    case 3:
        priority_nonpreemptive(proc, n);
        break;
    case 4:
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        round_robin(proc, n, quantum);
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}
