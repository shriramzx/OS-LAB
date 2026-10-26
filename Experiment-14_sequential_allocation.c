#include <stdio.h>
#include <string.h>

#define TOTAL_BLOCKS 32
#define RESERVED_BLOCKS 8
#define MAX_FILES (TOTAL_BLOCKS - RESERVED_BLOCKS)

typedef struct { char name[20]; int start, size; } File;

int main(void) {
    int used[TOTAL_BLOCKS] = {0}, files, size;
    File table[MAX_FILES];
    for (int b = 0; b < RESERVED_BLOCKS; ++b) used[b] = 1;
    puts("College Examination Document Storage - Sequential File Allocation");
    printf("Number of files (1-%d): ", MAX_FILES);
    if (scanf("%d", &files) != 1 || files < 1 || files > MAX_FILES) { fputs("Invalid file count.\n", stderr); return 1; }
    for (int f = 0; f < files; ++f) {
        printf("File %d name and required block count: ", f + 1);
        if (scanf("%19s %d", table[f].name, &size) != 2 || size <= 0 || size > TOTAL_BLOCKS - RESERVED_BLOCKS) {
            fputs("Invalid name or block count.\n", stderr); return 1;
        }
        int start = -1;
        for (int b = RESERVED_BLOCKS; b + size <= TOTAL_BLOCKS; ++b) {
            int free_run = 1;
            for (int k = b; k < b + size; ++k) if (used[k]) { free_run = 0; break; }
            if (free_run) { start = b; break; }
        }
        if (start < 0) { printf("Insufficient contiguous space for %s.\n", table[f].name); return 1; }
        table[f].start = start; table[f].size = size;
        for (int k = start; k < start + size; ++k) used[k] = 1;
    }
    puts("\nFile\tSize\tStarting block\tAllocated blocks");
    for (int f = 0; f < files; ++f) {
        printf("%s\t%d\t%d\t\t", table[f].name, table[f].size, table[f].start);
        for (int k = 0; k < table[f].size; ++k) printf("%d%s", table[f].start + k, k + 1 == table[f].size ? "" : " ");
        putchar('\n');
    }
    puts("Simulation assumption: blocks 0-7 are reserved; each file receives one contiguous run.");
    return 0;
}
