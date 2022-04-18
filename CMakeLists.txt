cmake_minimum_required(VERSION 3.15)
project(cps1012-assignment C)

## TinyShell
add_executable(tinyshell tinyshell/tinyshell.c tinyshell/builtin.c tinyshell/execute.c tinyshell/redirection.c tinyshell/tinyshell.h)