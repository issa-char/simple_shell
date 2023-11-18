#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void runShell() {
    char command[100]; // Assuming commands won't exceed 100 characters
    int status;

    while (1) {
        printf("#cisfun$ "); // Displaying the prompt
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break; // Exiting the shell on Ctrl+D (EOF)
        }

        // Removing the trailing newline character from the command
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            execlp(command, command, (char *)NULL);
            // If exec returns, there was an error
            perror(command);
            exit(EXIT_FAILURE);
        } else { // Parent process
            waitpid(pid, &status, 0);
        }
    }
}


