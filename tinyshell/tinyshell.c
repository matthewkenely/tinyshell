/* ------------------------------------- tinyshell.c  ------------------------------------- */
/* Provides the read_and_exec() function which tokenises user input and serves as the main  */
/* command execution driver. The main() function, continually looping, prompting the user   */
/* and executing read_and_exec() for input and execution is in this file.                   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tinyshell.h"

/* -------------------------------------- CONSTANTS -------------------------------------- */
#define MAX_IN 256           // Max number of characters to read using fgets()
#define MAX_PIPELINES 8      // Max number of pipelines ([ls | grep c]; [echo h])
#define MAX_COMMANDS 8       // Max number of commands ([ls] | [grep c])
#define MAX_ARGS 8           // Max number of arguments per command ([grep] [c])
#define MAX_TOKEN_LENGTH 256 // Max token length per argument ([g][r][e][p])
#define MAX_FILE 64          // Max in/out file name length

/* ------------------------------------- ANSI COLORS ------------------------------------- */
#define ANSI_PROMPT "\e[0;33m"
#define ANSI_CWD "\e[0;35m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct
{

} pipeline_t;

// Read user input and execute it using functions in execute.c
int read_and_exec()
{
    // Pipeline allocation
    char ***pipeline = malloc(MAX_PIPELINES * MAX_COMMANDS * sizeof(*pipeline));

    for (int i = 0; i < (MAX_PIPELINES * MAX_COMMANDS); i++)
    {
        pipeline[i] = malloc(MAX_ARGS * sizeof(*pipeline[i]));

        for (int j = 0; j < MAX_ARGS; j++)
        {
            pipeline[i][j] = malloc(MAX_TOKEN_LENGTH * sizeof(*pipeline[i][j]));
        }
    }

    // User input
    char in_buf[MAX_IN];

    if (!fgets(in_buf, MAX_IN, stdin))
    {
        fprintf(stderr, "fgets() failed.\n");
        exit(EXIT_FAILURE);
    }

    in_buf[strlen(in_buf) - 1] = '\0';

    int current_commands = 1; // Keep track of number of commands in the current pipeline

    int i = 0, // Command index
        j = 0, // Argument index
        k = 0; // Character index

    // Boolean modes corresponding to metacharacters
    bool status_pipe = false,
         status_output_redirect = false,
         status_input_redirect = false,
         status_quote = false;

    // Meta-modes used when executing
    bool do_output_redirect = false,
         do_append_out = false,
         do_input_redirect = false;

    // Input/output redirection file paths
    char *file_out = malloc(MAX_FILE * sizeof(char));
    int out_i = 0;

    char *file_in = malloc(MAX_FILE * sizeof(char));
    int in_i = 0;

    // Input/output redirection file paths encountered
    bool out_waiting = false,
         in_waiting = false;

    bool char_encountered = false;

    bool do_pipe = true;
    bool wait_for_semicolon = false;

    bool execute = true;

    // Traverse user input
    for (int c = 0; c < strlen(in_buf); c++)
    {
        // Skip redundant pipes + command sequences/pipelines/commands/arguments which are too long
        if (wait_for_semicolon)
        {
            if (c < strlen(in_buf) - 1 && in_buf[c] == ';')
            {
                wait_for_semicolon = false;

                if (execute)
                {
                    if (i + 1 >= MAX_COMMANDS)
                    {
                        fprintf(stderr, "Too many pipelines passed to pipeline sequence\n");
                        return EXIT_FAILURE;
                    }

                    if (c == strlen(in_buf) - 1)
                    {
                        continue;
                    }

                    pipeline[i][j][k] = '\0';
                    pipeline[i][j + 1] = NULL;

                    if (do_output_redirect)
                        file_out[strlen(file_out)] = '\0';
                    else
                        file_out = NULL;

                    if (do_input_redirect)
                        file_in[strlen(file_in)] = '\0';
                    else
                        file_in = NULL;

                    if (current_commands == 1 && execute_builtin(**(pipeline + i), *(pipeline + i), false) == 0)
                    {
                        free(file_out);
                        file_out = malloc(MAX_FILE * sizeof(char));

                        free(file_in);
                        file_in = malloc(MAX_FILE * sizeof(char));

                        do_append_out =
                            do_input_redirect =
                                do_output_redirect = false;

                        status_input_redirect =
                            status_output_redirect =
                                status_pipe =
                                    status_quote = false;

                        i++;
                        j = 0;
                        k = 0;

                        current_commands = 1;

                        out_i = 0;
                        in_i = 0;

                        do_pipe = true;

                        out_waiting = false;
                        in_waiting = false;

                        continue;
                    }

                    else if (execute_pipeline(current_commands, pipeline + (i - (current_commands - 1)), false, do_input_redirect ? file_in : NULL, do_output_redirect ? file_out : NULL, do_append_out) == 1)
                    {
                        fprintf(stderr, "Exeuction failed\n");
                        return EXIT_FAILURE;
                    }

                    else
                    {
                        free(file_out);
                        file_out = malloc(MAX_FILE * sizeof(char));

                        free(file_in);
                        file_in = malloc(MAX_FILE * sizeof(char));

                        do_append_out =
                            do_input_redirect =
                                do_output_redirect = false;

                        status_input_redirect =
                            status_output_redirect =
                                status_pipe =
                                    status_quote = false;

                        i++;
                        j = 0;
                        k = 0;

                        current_commands = 1;

                        out_i = 0;
                        in_i = 0;

                        do_pipe = true;

                        out_waiting = false;
                        in_waiting = false;

                        continue;
                    }
                }
                else
                {
                    execute = true;

                    free(file_out);
                    file_out = malloc(MAX_FILE * sizeof(char));

                    free(file_in);
                    file_in = malloc(MAX_FILE * sizeof(char));

                    do_append_out =
                        do_input_redirect =
                            do_output_redirect = false;

                    status_input_redirect =
                        status_output_redirect =
                            status_pipe =
                                status_quote = false;

                    i++;
                    j = 0;
                    k = 0;

                    current_commands = 1;

                    out_i = 0;
                    in_i = 0;

                    do_pipe = true;

                    out_waiting = false;
                    in_waiting = false;

                    continue;
                }
            }
            else if (c == strlen(in_buf) - 1)
            {
                if (in_buf[c] == ' ')
                {
                    if (execute_pipeline(current_commands, pipeline + (i - (current_commands - 1)), false, do_input_redirect ? file_in : NULL, do_output_redirect ? file_out : NULL, do_append_out) == 1)
                    {
                        fprintf(stderr, "Exeuction failed\n");
                        return EXIT_FAILURE;
                    }

                    return EXIT_SUCCESS;
                }
                else
                {
                    return EXIT_FAILURE;
                }
            }
            else
            {
                continue;
            }
        }

        /* CHECK SYNTAX */
        // First and last argument cannot be metacharacters
        if (c == 0 || c == strlen(in_buf) - 2)
        {
            if (in_buf[c] == '>' && in_buf[c + 1] == '>')
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", ">>");
                return EXIT_FAILURE;
            }
        }

        if (c == 0 || c == strlen(in_buf) - 1)
        {
            if (in_buf[c] == '|' ||
                in_buf[c] == '>' ||
                in_buf[c] == '<' ||
                (c == 0 && in_buf[c] == ';'))
            {
                fprintf(stderr, "Syntax error near unexpected token [%c]\n", in_buf[c]);
                return EXIT_FAILURE;
            }
        }

        // Disallow adjacent metacharacters
        if (!status_quote && c < strlen(in_buf) - 2 && in_buf[c] == '>' && in_buf[c + 1] == '>' &&
            (in_buf[c + 2] == '|' ||
             in_buf[c + 2] == '>' ||
             in_buf[c + 2] == '<' ||
             in_buf[c + 2] == ';'))
        {
            fprintf(stderr, "Syntax error near unexpected token [%c]\n", in_buf[c]);
            return EXIT_FAILURE;
        }

        if (!status_quote && !(in_buf[c] == '>' && in_buf[c + 1] == '>') &&
            (in_buf[c] == '|' ||
             in_buf[c] == '>' ||
             in_buf[c] == '<' ||
             in_buf[c] == ';') &&
            (in_buf[c + 1] == '|' ||
             in_buf[c + 1] == '>' ||
             in_buf[c + 1] == '<' ||
             in_buf[c + 1] == ';'))
        {
            fprintf(stderr, "Syntax error near unexpected token [%c]\n", in_buf[c]);
            return EXIT_FAILURE;
        }

        /* CHECK IF METACHARACTER */
        // [|] Pipe
        if (!status_quote && in_buf[c] == '|')
        {
            if (!char_encountered)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", "|");
                return EXIT_FAILURE;
            }
            if (do_pipe)
            {
                if (current_commands >= MAX_COMMANDS)
                {
                    fprintf(stderr, "Too many commands passed in pipeline [%s ... | %s ... | ... ]\n", pipeline[i - (current_commands - 1)][0], pipeline[i - (current_commands - 1) + 1][0]);
                    wait_for_semicolon = true;
                    execute = false;
                    continue;
                }

                if (status_output_redirect)
                {
                    if (out_waiting) // First out file character which is not a space
                    {
                        continue;
                    }
                    else // First space encountered while reading out file
                    {
                        file_out[out_i] = '\0';
                        status_output_redirect = false;
                        out_waiting = false;
                        // wait_for_semicolon = true;
                        continue;
                    }
                }

                if (status_input_redirect)
                {
                    if (in_waiting)
                    {
                        continue;
                    }
                    else
                    {
                        file_in[in_i] = '\0';
                        status_input_redirect = false;
                        in_waiting = false;
                        continue;
                    }
                }

                status_pipe = true;
                status_output_redirect = false;
                status_input_redirect = false;

                pipeline[i][j][k] = '\0';
                pipeline[i][j + 1] = NULL;

                i++;
                j = 0;
                k = 0;

                current_commands++;

                continue;
            }
            else
            {
                continue;
            }
        }

        // [>>] Append out (overrides output redirect)
        else if (!status_quote && in_buf[c] == '>' && in_buf[c + 1] == '>')
        {
            if (!char_encountered)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", ">>");
                return EXIT_FAILURE;
            }

            if (do_output_redirect)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", ">>");
                return EXIT_FAILURE;
            }

            status_pipe = false;
            status_output_redirect = true;

            do_output_redirect = true;
            do_append_out = true;

            out_waiting = true;

            pipeline[i][j][k] = '\0';
            pipeline[i][j + 1] = NULL;

            c++;
            continue;
        }

        // [>] Output redirect
        else if (!status_quote && in_buf[c] == '>')
        {
            if (!char_encountered)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", ">");
                return EXIT_FAILURE;
            }

            if (do_output_redirect)
            {
                fprintf(stderr, "Syntax error near unexpected token [%c]\n", in_buf[c]);
                return EXIT_FAILURE;
            }

            status_pipe = false;
            status_output_redirect = true;

            do_output_redirect = true;

            out_waiting = true;

            pipeline[i][j][k] = '\0';
            pipeline[i][j + 1] = NULL;

            continue;
        }

        // [<] Input redirect
        else if (!status_quote && in_buf[c] == '<')
        {
            if (!char_encountered)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", "<");
                return EXIT_FAILURE;
            }

            if (do_input_redirect)
            {
                fprintf(stderr, "Syntax error near unexpected token [%c]\n", in_buf[c]);
                return EXIT_FAILURE;
            }

            status_pipe = false;
            status_output_redirect = false;
            status_input_redirect = true;

            do_input_redirect = true;

            in_waiting = true;

            pipeline[i][j][k] = '\0';
            pipeline[i][j + 1] = NULL;

            continue;
        }

        // [ ] New argument
        else if (!status_quote && in_buf[c] == ' ')
        {
            if (j + 1 >= MAX_ARGS)
            {
                fprintf(stderr, "Too many arguments passed to command [%s] in pipeline %d\n", pipeline[i - (current_commands - 1)][0], i - (current_commands - 1) + 1);
                wait_for_semicolon = true;
                execute = false;
                continue;
            }

            if (status_output_redirect)
            {
                if (out_waiting) // First out file character which is not a space
                {
                    continue;
                }
                else // First space encountered while reading out file
                {
                    file_out[out_i] = '\0';
                    status_output_redirect = false;
                    out_waiting = false;
                    // wait_for_semicolon = true;
                    continue;
                }
            }

            if (status_input_redirect)
            {
                if (in_waiting)
                {
                    continue;
                }
                else
                {
                    file_in[in_i] = '\0';
                    status_input_redirect = false;
                    in_waiting = false;
                    continue;
                }
            }

            if (c == strlen(in_buf) - 1)
            {
                return EXIT_SUCCESS;
            }

            if ((c == 0 || c == strlen(in_buf) - 1) ||
                (j == 0 && k == 0) ||
                in_buf[c + 1] == ' ' ||
                in_buf[c + 1] == '|' ||
                in_buf[c + 1] == '>' ||
                in_buf[c + 1] == '<' ||
                in_buf[c + 1] == ';' ||
                in_buf[c - 1] == '|' ||
                in_buf[c - 1] == '>' ||
                in_buf[c - 1] == '<' ||
                in_buf[c - 1] == ';')
            {
                continue;
            }

            pipeline[i][j][k] = '\0';

            j++;
            k = 0;

            continue;
        }

        // ["] Literal interpretation
        else if (in_buf[c] == '"')
        {
            if (status_quote)
            {
                status_quote = false;
                continue;
            }

            status_quote = true;

            continue;
        }

        // [\] Strip metacharacter meaning of following character
        else if (in_buf[c] == '\\')
        {
            if (k + 1 >= MAX_TOKEN_LENGTH)
            {
                fprintf(stderr, "Too many characters passed to argument [%c%c%c%c%c...] in pipeline %d\n",
                        pipeline[i][j][0], pipeline[i][j][1], pipeline[i][j][2], pipeline[i][j][3], pipeline[i][j][4], i + 1);
                wait_for_semicolon = true;
                execute = false;
                continue;
            }
            pipeline[i][j][k++] = in_buf[c + 1];
            c++;
            continue;
        }

        // [;] Additional pipeline
        else if (!status_quote && in_buf[c] == ';')
        {
            if (!char_encountered)
            {
                fprintf(stderr, "Syntax error near unexpected token [%s]\n", ";");
                return EXIT_FAILURE;
            }

            wait_for_semicolon = false;

            if (i + 1 >= MAX_COMMANDS)
            {
                fprintf(stderr, "Too many pipelines passed to pipeline sequence\n");
                return EXIT_FAILURE;
            }

            if (c == strlen(in_buf) - 1)
            {
                continue;
            }

            pipeline[i][j][k] = '\0';
            pipeline[i][j + 1] = NULL;

            if (do_output_redirect)
                file_out[strlen(file_out)] = '\0';
            else
                file_out = NULL;

            if (do_input_redirect)
                file_in[strlen(file_in)] = '\0';
            else
                file_in = NULL;

            if (current_commands == 1 && execute_builtin(**(pipeline + i), *(pipeline + i), false) == 0)
            {
                free(file_out);
                file_out = malloc(MAX_FILE * sizeof(char));

                free(file_in);
                file_in = malloc(MAX_FILE * sizeof(char));

                do_append_out =
                    do_input_redirect =
                        do_output_redirect = false;

                status_input_redirect =
                    status_output_redirect =
                        status_pipe =
                            status_quote = false;

                i++;
                j = 0;
                k = 0;

                current_commands = 1;

                out_i = 0;
                in_i = 0;

                do_pipe = true;

                out_waiting = false;
                in_waiting = false;

                continue;
            }

            else if (execute_pipeline(current_commands, pipeline + (i - (current_commands - 1)), false, do_input_redirect ? file_in : NULL, do_output_redirect ? file_out : NULL, do_append_out) == 1)
            {
                fprintf(stderr, "Exeuction failed\n");
                return EXIT_FAILURE;
            }

            else
            {
                free(file_out);
                file_out = malloc(MAX_FILE * sizeof(char));

                free(file_in);
                file_in = malloc(MAX_FILE * sizeof(char));

                do_append_out =
                    do_input_redirect =
                        do_output_redirect = false;

                status_input_redirect =
                    status_output_redirect =
                        status_pipe =
                            status_quote = false;

                i++;
                j = 0;
                k = 0;

                current_commands = 1;

                out_i = 0;
                in_i = 0;

                do_pipe = true;

                out_waiting = false;
                in_waiting = false;

                continue;
            }

            continue;
        }

        /* CHECK IF WRITING IN/OUT FILE PATH */
        // Out file
        if (status_output_redirect)
        {
            out_waiting = false; // Indicate that a non-space character has been found
            file_out[out_i++] = in_buf[c];

            continue;
        }

        // In file
        else if (status_input_redirect)
        {
            in_waiting = false; // Indicate that a non-space character has been found
            file_in[in_i++] = in_buf[c];

            continue;
        }

        /* ADD NON-META CHARACTER TO PIPELINE */
        else
        {
            if (k + 1 >= MAX_TOKEN_LENGTH)
            {
                fprintf(stderr, "Too many characters passed to argument [%c%c%c%c%c...] in pipeline %d\n",
                        pipeline[i][j][0], pipeline[i][j][1], pipeline[i][j][2], pipeline[i][j][3], pipeline[i][j][4], i + 1);
                wait_for_semicolon = true;
                execute = false;
                continue;
            }

            pipeline[i][j][k++] = in_buf[c];
            char_encountered = true;
            status_pipe = false;
        }
    }

    if (status_quote)
    {
        fprintf(stderr, "Syntax error: mismatched quotes\n");
        return EXIT_FAILURE;
    }

    pipeline[i][j + 1] = NULL;
    pipeline[i][j][k] = '\0';

    if (do_output_redirect)
        file_out[strlen(file_out)] = '\0';
    else
        file_out = NULL;

    if (do_input_redirect)
        file_in[strlen(file_in)] = '\0';
    else
        file_in = NULL;

    /* EXECUTE LAST PIPELINE IN COMMAND SEQUENCE */
    // Attempt to execute command as buitlin
    if (!(current_commands == 1 && (execute_builtin(**(pipeline + i), *(pipeline + i), false) == 0)))
    {
        // Execute command using execvp() in execute.c
        if (execute_pipeline(current_commands, pipeline + (i - (current_commands - 1)), false, do_input_redirect ? file_in : NULL, do_output_redirect ? file_out : NULL, do_append_out) == 1)
        {
            return EXIT_FAILURE;
        }
    }

    // Free pipeline
    for (int i = 0; i < (MAX_PIPELINES * MAX_COMMANDS); i++)
    {
        for (int j = 0; j < MAX_ARGS; j++)
        {
            free(pipeline[i][j]);
            pipeline[i][j] = NULL;
        }
        free(pipeline[i]);
        pipeline[i] = NULL;
    }

    free(pipeline);
    pipeline[i] = NULL;

    return EXIT_SUCCESS;
}

int main(void)
{
    char cwd[128];

    // User prompt loop
    while (1)
    {
        if (getcwd(cwd, 128))
        {
            printf(ANSI_PROMPT "tiny_shell" ANSI_COLOR_RESET "@");
            printf(ANSI_CWD "%s", cwd);
            printf(ANSI_COLOR_RESET "$ ");
        }
        else
        {
            perror("getcwd() failed");
            return EXIT_FAILURE;
        }

        if (read_and_exec() == -1)
        {
            fprintf(stderr, "Exeuction failed\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
