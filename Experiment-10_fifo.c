#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 1000
#define MAX_FRAMES 100

int main(void) {
    int pages[MAX_PAGES], frames[MAX_FRAMES], n, count, faults = 0, next = 0;
    puts("Genome Sequencing Data Buffer - FIFO Page Replacement");
    printf("Number of page references (1-%d): ", MAX_PAGES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PAGES) { fputs("Invalid reference count.\n", stderr); return 1; }
    printf("Number of frames (1-%d): ", MAX_FRAMES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_FRAMES) { fputs("Invalid frame count.\n", stderr); return 1; }
    printf("Enter %d page numbers: ", n);
    for (int i = 0; i < n; ++i) if (scanf("%d", &pages[i]) != 1 || pages[i] < 0) { fputs("Page numbers must be non-negative integers.\n", stderr); return 1; }
    for (int i = 0; i < count; ++i) frames[i] = -1;
    puts("\nPage\tFrames\t\tStatus");
    for (int i = 0; i < n; ++i) {
        int hit = 0;
        for (int j = 0; j < count; ++j) if (frames[j] == pages[i]) hit = 1;
        if (!hit) { frames[next] = pages[i]; next = (next + 1) % count; ++faults; }
        printf("%d\t", pages[i]);
        for (int j = 0; j < count; ++j) {
            if (frames[j] < 0) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\t%s\n", hit ? "HIT" : "FAULT");
    }
    printf("\nTotal page faults = %d\nTotal page hits = %d\n", faults, n - faults);
    return 0;
}
