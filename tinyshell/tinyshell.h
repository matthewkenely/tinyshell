#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

// Execution
int execute_pipeline(int argc, char **pipeline[], bool async, char *file_in, char *file_out, bool append_out);

// Redirection
int redirect_input(char *input);

int redirect_output(char *output, int append_flag);

// Built-in commands
int execute_builtin(char *name, char **args, bool async);