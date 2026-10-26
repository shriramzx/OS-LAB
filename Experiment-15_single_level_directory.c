#include <stdio.h>
#include <string.h>

#define MAX_FILES 100

int main(void) {
    char directory[30], files[MAX_FILES][50], name[50];
    int count = 0, choice;
    printf("College Student Project Management - Single-Level Directory\nDirectory name: ");
    if (scanf("%29s", directory) != 1) return 1;
    do {
        printf("\n1 Add file  2 List files  3 Search  4 Delete  5 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) {
            if (count == MAX_FILES) { puts("Directory is full."); continue; }
            printf("File name: "); if (scanf("%49s", name) != 1) return 1;
            int duplicate = 0;
            for (int i = 0; i < count; ++i) if (strcmp(files[i], name) == 0) duplicate = 1;
            if (duplicate) puts("That file name already exists in this directory.");
            else { strcpy(files[count++], name); puts("File added."); }
        } else if (choice == 2) {
            printf("Directory %s files:", directory);
            if (!count) printf(" (empty)");
            for (int i = 0; i < count; ++i) printf(" %s", files[i]);
            putchar('\n');
        } else if (choice == 3 || choice == 4) {
            printf("File name: "); if (scanf("%49s", name) != 1) return 1;
            int found = -1;
            for (int i = 0; i < count; ++i) if (strcmp(files[i], name) == 0) { found = i; break; }
            if (found < 0) puts("File not found.");
            else if (choice == 3) printf("%s is in directory %s at position %d.\n", name, directory, found + 1);
            else {
                if (found != count - 1) strcpy(files[found], files[count - 1]);
                --count; puts("File deleted.");
            }
        } else if (choice != 5) puts("Invalid choice.");
    } while (choice != 5);
    return 0;
}
