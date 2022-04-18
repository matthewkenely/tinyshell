/* -------------------------------------- execute.c  -------------------------------------- */
/* Provides the execute_pipeline() function, a modification of execute_pipeline_async_ex(). */
/* Automatically acts as a fork_exec() function, omitting the piping process when passed a  */
/* single command as an argument.                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tinyshell.h"

int execute_pipeline(int argc, char **pipeline[], bool async, char *file_in, char *file_out, bool append_out)
{
    int fd[(argc - 1) * 2];
    int *current_fd = fd,
        *previous_fd = NULL;

    int stage = 0;

    while (stage < argc)
    {
        previous_fd = current_fd - 2;

        if (stage < argc - 1)
        {
            if (pipe(current_fd) == -1)
            {
                perror("pipe() failed");
                return EXIT_FAILURE;
            }
        }

        pid_t cpid = fork();

        if (cpid == -1)
        {
            perror("fork() failed");
            return EXIT_FAILURE;
        }

        /* CHILD PROCESS */
        if (cpid == 0)
        {
            // First stage
            if (stage == 0 && file_in)
            {
                if (redirect_input(file_in) == -1)
                {
                    perror("redirect_input() failed");
                    return EXIT_FAILURE;
                }
            }

            // All stages except last
            if (stage < argc - 1)
            {
                if (close(current_fd[0]) == -1) // Close read
                {
                    perror("close() failed");
                    return EXIT_FAILURE;
                }

                if (dup2(current_fd[1], STDOUT_FILENO) == -1) // Bind STDOUT to write-end
                {
                    perror("dup2() failed");
                    return EXIT_FAILURE;
                }

                if (close(current_fd[1]) == -1)
                {
                    perror("close() failed");
                    return EXIT_FAILURE;
                }
            }

            // Last stage
            if (stage == argc - 1 && file_out)
            {
                int out_return = append_out ? redirect_output(file_out, O_RDWR | O_APPEND) : redirect_output(file_out, O_RDWR | O_TRUNC);
                if (out_return == -1)
                {
                    perror("redirect_output() failed");
                    return EXIT_FAILURE;
                }
            }

            // All stages except first
            if (stage > 0)
            {
                if (close(previous_fd[1]) == -1) // Close write
                {
                    perror("close() failed");
                    return EXIT_FAILURE;
                }

                if (dup2(previous_fd[0], STDIN_FILENO) == -1) // Bind STDIN to read-end
                {
                    perror("dup2() failed");
                    return EXIT_FAILURE;
                }

                if (close(previous_fd[0]) == -1)
                {
                    perror("close() failed");
                    return EXIT_FAILURE;
                }
            }

            if (execvp(**pipeline, *pipeline) == -1)
            {
                perror("execvp() failed");
                exit(EXIT_FAILURE);
            }

            return EXIT_SUCCESS;
        }

        /* PARENT PROCESS */
        if (stage >= 1)
        {
            if (close(previous_fd[0]) == -1 || close(previous_fd[1]) == -1)
            {
                perror("close() failed");
                return EXIT_FAILURE;
            }
        }

        // Block parent execution
        int status;
        if (!async)
        {
            if (waitpid(cpid, &status, WUNTRACED) == -1)
            {
                perror("waitpid() failed");
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (waitpid(cpid, &status, WNOHANG) == -1)
            {
                perror("waitpid() failed");
                return EXIT_FAILURE;
            }
        }

        if (!WIFEXITED(status))
        {
            return EXIT_FAILURE;
        }

        pipeline++;
        stage++;
        current_fd += 2;
    }

    return EXIT_SUCCESS;
}
