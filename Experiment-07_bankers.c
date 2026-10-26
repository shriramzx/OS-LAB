#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int main(void)
{
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximum[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[R] = {3, 3, 2};
    int need[P][R];
    int work[R];
    bool finished[P] = {false};
    int safe_sequence[P];
    int count = 0;

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("BANKER'S ALGORITHM\n");
    printf("Need Matrix:\n");
    printf("Process\tA\tB\tC\n");

    for (int i = 0; i < P; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++) {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < R; j++) {
        work[j] = available[j];
    }

    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (finished[i]) {
                continue;
            }

            bool can_finish = true;

            for (int j = 0; j < R; j++) {
                if (need[i][j] > work[j]) {
                    can_finish = false;
                    break;
                }
            }

            if (can_finish) {
                for (int j = 0; j < R; j++) {
                    work[j] += allocation[i][j];
                }

                safe_sequence[count++] = i;
                finished[i] = true;
                found = true;
            }
        }

        if (!found) {
            break;
        }
    }

    if (count == P) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence: ");

        for (int i = 0; i < P; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < P - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
        printf("No safe sequence exists for the given state.\n");
    }

    return 0;
}
