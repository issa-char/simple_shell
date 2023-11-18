#include "main.h"

void runShell() {
    char command[100];
    int status;
	pid_t pid = fork();

    while (1) {
        printf("#cisfun$ "); 
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }


        command[strcspn(command, "\n")] = '\0';

       
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execlp(command, command, (char *)NULL);
            perror(command);
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
        }
    }
}


