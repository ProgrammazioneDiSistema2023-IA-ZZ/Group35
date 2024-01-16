#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "syscall.h"

void print_menu() {
    printf(1, "Menu:\n");
    printf(1, "1. Add a process\n");
    printf(1, "2. Kill a process\n");
    printf(1, "3. Exit\n");
    printf(1, "Choose an option: ");
}

int main(int argc, char *argv[]){
    char choice[10];
    while(1){
        ptm();

        print_menu();

        int n = read(0, choice, sizeof(choice));
        if (n <= 0) {
            printf(1, "Error reading input\n");
            continue;
        }

        choice[n - 1] = '\0';

        int option = atoi(choice);

        switch (option) {
            case 1:
                // Add a process
                printf(1, "Adding a process...\n");
                int pid = fork();

                if (pid < 0) {
                    // Fork failed
                    printf(1, "Error: Fork failed\n");
                } else if (pid == 0) {
                    // CHILD
                    test();

                    while (1) {
                        sleep(100);
                    }
                } else {
                    // Parent process
                    sleep(1);
                }
                break;
            case 2:
                // Kill a process
                printf(1, "Choose a PID to delete: ");
                int n = read(0, choice, sizeof(choice));
                if (n <= 0) {
                    printf(1, "Error reading input\n");
                    continue;
                }

                choice[n - 1] = '\0';

                int deleted = atoi(choice);
                kill(deleted);
                break;
            case 3:
                // Exit the program
                printf(1, "Exiting...\n");
                exit();
            default:
                printf(1, "Invalid option. Please choose a valid option.\n");
        }
        sleep(1);
    }
    exit();
}
