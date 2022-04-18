/* -------------------------------------- builtin.c  -------------------------------------- */
/* Provides the execute_builtin() function, acting as a lookup function for all the builtin */
/* functions listed in builtin_list.                                                        */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/* -------------------------------------- CONSTANTS -------------------------------------- */
#define BUILTIN_COMMANDS 4

/* ------------------------------------- ANSI COLORS ------------------------------------- */
#define ANSI_TITLE "\e[0;33m"
#define ANSI_BORDER "\e[0;37m"
#define ANSI_QUOTE "\e[0;33m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* ----------------------------------- TYPE DEFINITION ----------------------------------- */
typedef int (*builtin_function_t)(char **);

// Single builtin command
typedef struct
{
    char *name;
    builtin_function_t function;
} builtin_command_t;

/* ----------------------------------- BUILTIN COMMANDS ---------------------------------- */
// [exit]
int exit_builtin(char **args)
{
    exit(EXIT_SUCCESS);
}

// [cd]
int cd_builtin(char **args)
{
    if (*args)
    {
        if (args[1] == NULL || strcmp(args[1], "~") == 0)
        {
            chdir(getenv("HOME"));
        }

        else if (chdir(args[1]) == -1)
        {
            printf("cd: %s: No such file or directory\n", args[1]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

// [cwd]
int cwd_builtin(char **args)
{
    char cwd[128];

    if (getcwd(cwd, 128))
    {
        printf("%s\n", cwd);
    }

    else
    {
        perror("getcwd() failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// [ver]
int ver_builtin(char **args)
{
    printf("@------------@" ANSI_TITLE " TINY SHELL " ANSI_COLOR_RESET "@------------@" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf("%-20s%18s", " Author:", "Matthew Kenely ");
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf("%-20s%18s", " Version:", "1.0 ");
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf("%-20s%18s", " ", " ");
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf(ANSI_QUOTE " But, use this, to summon one another " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf(ANSI_QUOTE " as spirits, cross the gaps between   " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf(ANSI_QUOTE " the worlds, and engage in jolly      " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
    printf(ANSI_QUOTE " co-operation!                        " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RESET "|\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RESET "@--------------------------------------@" ANSI_COLOR_RESET "\n");

    return EXIT_SUCCESS;
}

builtin_command_t builtin_list[BUILTIN_COMMANDS] =
    {
        {"exit", &exit_builtin},
        {"cd", &cd_builtin},
        {"cwd", &cwd_builtin},
        {"ver", &ver_builtin},
};

int execute_builtin(char *name, char **args, bool async)
{
    bool found = false;

    for (int i = 0; i < BUILTIN_COMMANDS; i++)
    {
        int min_length = sizeof(name) <= sizeof(builtin_list[i].name) ? sizeof(name) : sizeof(builtin_list[i].name);

        if (strncmp(builtin_list[i].name, name, min_length) == 0)
        {
            found = true;
            builtin_list[i].function(args);
            return EXIT_SUCCESS;
        }
    }

    if (!found)
    {
        // No error message, all commands are run through this function
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
