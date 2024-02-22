#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for execve() */
#include <sys/types.h> /* for fork() */
#include <sys/wait.h> /* for wait() */
#include <string.h> /* for strcspn() */

int main(void)
{
    char *input = NULL;
    size_t bufsize = 0;
    pid_t pid;

    /* Print a prompt */
    printf("$ ");

    /* Main loop */
    while (1)
    {
        /* Read user input */
        if (getline(&input, &bufsize, stdin) == -1)
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character */
        input[strcspn(input, "\n")] = '\0';

        /* Fork to create a new process */
        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) /* Child process */
        {
            /* Tokenize input */
            /* Execute command */
            /* We'll implement this part later */
            /* For now, let's just print the command */
            printf("Executing: %s\n", input);

            /* Clean up and exit child process */
            free(input);
            exit(EXIT_SUCCESS);
        }
        else /* Parent process */
        {
            /* Wait for the child process to terminate */
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }

        /* Print a prompt again */
        printf("$ ");
    }

    /* Free allocated memory */
    free(input);

    return 0;
}

