#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct { int id, arrival, burst, remaining, completion; } Process;

int main(void) {
    Process p[MAX_PROCESSES];
    int n, quantum, done = 0, time = 0, queue[MAX_PROCESSES + 1];
    int front = 0, back = 0, size = 0, queued[MAX_PROCESSES] = {0};
    double total_wait = 0, total_turnaround = 0;

    puts("Virtual Production Render Scheduler - Round Robin");
    printf("Number of rendering jobs (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        fputs("Invalid job count.\n", stderr); return 1;
    }
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        printf("Job %d arrival time and burst time: ", i + 1);
        if (scanf("%d %d", &p[i].arrival, &p[i].burst) != 2 ||
            p[i].arrival < 0 || p[i].burst <= 0) {
            fputs("Arrival must be non-negative and burst time positive.\n", stderr); return 1;
        }
        p[i].remaining = p[i].burst;
    }
    printf("Time quantum: ");
    if (scanf("%d", &quantum) != 1 || quantum <= 0) {
        fputs("Time quantum must be positive.\n", stderr); return 1;
    }
    /* Advance time across idle gaps; newly arrived jobs join the FIFO ready queue. */
    printf("\nExecution order (time slices):\n");
    while (done < n) {
        for (int i = 0; i < n; ++i)
            if (!queued[i] && p[i].remaining > 0 && p[i].arrival <= time) {
                queue[back] = i; back = (back + 1) % (MAX_PROCESSES + 1);
                ++size; queued[i] = 1;
            }
        if (size == 0) {
            int next = -1;
            for (int i = 0; i < n; ++i)
                if (p[i].remaining > 0 && (next < 0 || p[i].arrival < p[next].arrival)) next = i;
            if (next < 0) break;
            time = p[next].arrival;
            continue;
        }
        int i = queue[front]; front = (front + 1) % (MAX_PROCESSES + 1);
        --size; queued[i] = 0;
        int run = p[i].remaining < quantum ? p[i].remaining : quantum;
        int start = time; time += run; p[i].remaining -= run;
        printf("P%d: %d-%d\n", p[i].id, start, time);
        for (int j = 0; j < n; ++j)
            if (j != i && !queued[j] && p[j].remaining > 0 && p[j].arrival <= time) {
                queue[back] = j; back = (back + 1) % (MAX_PROCESSES + 1);
                ++size; queued[j] = 1;
            }
        if (p[i].remaining > 0) {
            queue[back] = i; back = (back + 1) % (MAX_PROCESSES + 1);
            ++size; queued[i] = 1;
        }
        else { p[i].completion = time; ++done; }
    }
    puts("\nProcess\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; ++i) {
        int tat = p[i].completion - p[i].arrival;
        int wt = tat - p[i].burst;
        total_turnaround += tat; total_wait += wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival,
               p[i].burst, p[i].completion, tat, wt);
    }
    printf("Average turnaround time = %.2f\nAverage waiting time = %.2f\n",
           total_turnaround / n, total_wait / n);
    return 0;
}
