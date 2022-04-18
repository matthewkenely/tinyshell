/* ------------------------------------ redirection.c  ------------------------------------ */
/* Provides the redirect_input() and redirect_output() functions for I/O redirecton when    */
/* executing commands                                                                       */
/* Adapted from Keith Bugeja's "CPS1012 - Redirection and Pipes Part 1 (I/O Redirection)"   */
/* https://www.youtube.com/watch?v=XflfgbUiHYI                                              */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tinyshell.h"

int reopen(int fd, char *pathname, int flags, mode_t mode)
{
    int open_fd = open(pathname, flags, mode);
    if (open_fd == fd || open_fd < 0)
        return open_fd;

    int dup_fd = dup2(open_fd, fd);

    if (close(open_fd) == -1)
    {
        perror("close() failed");
        return EXIT_FAILURE;
    }

    return dup_fd == -1 ? dup_fd : fd;
}

int redirect_input(char *input)
{
    return reopen(STDIN_FILENO, input, O_RDONLY, S_IRUSR);
}

int redirect_output(char *output, int append_flag)
{
    return reopen(STDOUT_FILENO, output, append_flag | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}
