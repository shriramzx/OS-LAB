#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id, burst, priority, completion, turnaround, waiting;
} Process;

int main(void) {
    Process p[MAX_PROCESSES], tmp;
    int n, time = 0;
    double total_wait = 0, total_turnaround = 0;

    puts("Smart Disaster-Response Control Center - Priority Scheduling");
    puts("Non-preemptive priority scheduling; smaller number means higher priority.");
    printf("Number of emergency tasks (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        fputs("Invalid task count.\n", stderr); return 1;
    }
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        printf("Task %d burst time and priority: ", i + 1);
        if (scanf("%d %d", &p[i].burst, &p[i].priority) != 2 ||
            p[i].burst <= 0 || p[i].priority < 0) {
            fputs("Burst time must be positive and priority non-negative.\n", stderr); return 1;
        }
    }
    /* Stable ordering: lower priority value first, then input order. */
    for (int i = 1; i < n; ++i) {
        tmp = p[i]; int j = i;
        while (j > 0 && p[j - 1].priority > tmp.priority) { p[j] = p[j - 1]; --j; }
        p[j] = tmp;
    }
    printf("\nExecution order: ");
    for (int i = 0; i < n; ++i) {
        p[i].completion = (time += p[i].burst);
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
        total_wait += p[i].waiting; total_turnaround += p[i].turnaround;
        printf("P%d%s", p[i].id, i == n - 1 ? "\n" : " -> ");
    }
    puts("\nProcess\tPriority\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; ++i)
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\n", p[i].id, p[i].priority,
               p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    printf("Average turnaround time = %.2f\nAverage waiting time = %.2f\n",
           total_turnaround / n, total_wait / n);
    return 0;
}
