#include <stdio.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_FILES 50

typedef struct { char name[30]; char files[MAX_FILES][50]; int count; } UserDirectory;

int main(void) {
    UserDirectory users[MAX_USERS] = {0};
    int user_count = 0, choice;
    char user[30], file[50];
    puts("College Student Project Management - Two-Level Directory");
    do {
        printf("\n1 Create user directory  2 Add file  3 List  4 Search  5 Delete file  6 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) {
            if (user_count == MAX_USERS) { puts("Directory table is full."); continue; }
            printf("User directory name: "); if (scanf("%29s", user) != 1) return 1;
            int duplicate = 0;
            for (int i = 0; i < user_count; ++i) if (strcmp(users[i].name, user) == 0) duplicate = 1;
            if (duplicate) puts("User directory already exists.");
            else { strcpy(users[user_count].name, user); users[user_count++].count = 0; puts("Directory created."); }
        } else if (choice >= 2 && choice <= 5) {
            printf("User directory: "); if (scanf("%29s", user) != 1) return 1;
            int u = -1;
            for (int i = 0; i < user_count; ++i) if (strcmp(users[i].name, user) == 0) { u = i; break; }
            if (u < 0) { puts("Directory not found."); continue; }
            if (choice == 3) {
                printf("Files in %s:", user);
                if (!users[u].count) printf(" (empty)");
                for (int i = 0; i < users[u].count; ++i) printf(" %s", users[u].files[i]);
                putchar('\n'); continue;
            }
            printf("File name: "); if (scanf("%49s", file) != 1) return 1;
            int f = -1;
            for (int i = 0; i < users[u].count; ++i) if (strcmp(users[u].files[i], file) == 0) { f = i; break; }
            if (choice == 2) {
                if (users[u].count == MAX_FILES) puts("User directory is full.");
                else if (f >= 0) puts("That file already exists for this user.");
                else { strcpy(users[u].files[users[u].count++], file); puts("File added."); }
            } else if (f < 0) puts("File not found.");
            else if (choice == 4) printf("%s/%s exists.\n", user, file);
            else {
                if (f != users[u].count - 1) strcpy(users[u].files[f], users[u].files[users[u].count - 1]);
                --users[u].count; puts("File deleted.");
            }
        } else if (choice != 6) puts("Invalid choice.");
    } while (choice != 6);
    return 0;
}
