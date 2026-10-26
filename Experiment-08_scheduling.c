#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int id, at, bt, ct, tat, wt;
} Process;

typedef struct {
    int id;
    int start, end;
} Segment;

void simulate(Process input[], int n, bool use_sjf)
{
    Process p[MAX];
    Segment gantt[2 * MAX];
    bool done[MAX] = {false};
    int count = 0, time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        p[i] = input[i];
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    while (completed < n) {
        int chosen = -1;

        for (int i = 0; i < n; i++) {
            if (done[i] || p[i].at > time)
                continue;

            if (chosen == -1) {
                chosen = i;
            } else if (use_sjf) {
                if (p[i].bt < p[chosen].bt ||
                    (p[i].bt == p[chosen].bt &&
                     p[i].at < p[chosen].at) ||
                    (p[i].bt == p[chosen].bt &&
                     p[i].at == p[chosen].at &&
                     p[i].id < p[chosen].id)) {
                    chosen = i;
                }
            } else {
                if (p[i].at < p[chosen].at ||
                    (p[i].at == p[chosen].at &&
                     p[i].id < p[chosen].id)) {
                    chosen = i;
                }
            }
        }

        if (chosen == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!done[i] &&
                    (next == -1 || p[i].at < p[next].at))
                    next = i;
            }

            if (next == -1)
                break;

            gantt[count++] = (Segment){0, time, p[next].at};
            time = p[next].at;
            continue;
        }

        int start = time;
        time += p[chosen].bt;

        p[chosen].ct = time;
        p[chosen].tat = p[chosen].ct - p[chosen].at;
        p[chosen].wt = p[chosen].tat - p[chosen].bt;

        gantt[count++] =
            (Segment){p[chosen].id, start, time};

        done[chosen] = true;
        completed++;
    }

    printf("\n========================================\n");
    printf("%s\n", use_sjf
           ? "SJF (NON-PREEMPTIVE) SCHEDULING"
           : "FCFS SCHEDULING");
    printf("========================================\n");

    printf("\nGantt Chart:\n");
    for (int i = 0; i < count; i++) {
        if (gantt[i].id == 0)
            printf("| IDLE ");
        else
            printf("|  P%d  ", gantt[i].id);
    }
    printf("|\n");

    if (count > 0) {
        printf("%d", gantt[0].start);
        for (int i = 0; i < count; i++)
            printf("\t%d", gantt[i].end);
        printf("\n");
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    double total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f\n",
           total_tat / n);
    printf("Average Waiting Time = %.2f\n",
           total_wt / n);
}

int main(void)
{
    Process p[MAX];
    int n;

    printf("CPU SCHEDULING: FCFS AND SJF\n");
    printf("Enter number of processes (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("Enter arrival time and burst time for P%d: ",
               i + 1);

        if (scanf("%d %d", &p[i].at, &p[i].bt) != 2 ||
            p[i].at < 0 || p[i].bt <= 0) {
            printf("Invalid input. AT must be >= 0 and BT > 0.\n");
            return 1;
        }
    }

    simulate(p, n, false);
    simulate(p, n, true);

    return 0;
}
