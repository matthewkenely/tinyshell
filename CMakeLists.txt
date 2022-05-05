cmake_minimum_required(VERSION 3.15)
project(cps1012-assignment C)

# TASKS
## Task 1
add_executable(1a tasks/task-1/a.c)
add_executable(1b tasks/task-1/b.c)
add_executable(1c tasks/task-1/c.c)
add_executable(1d tasks/task-1/d.c)
add_executable(1e tasks/task-1/e.c)

## Task 2
add_executable(2a tasks/task-2/a.c)
add_executable(2b tasks/task-2/b.c)

## Task 3
add_executable(3a tasks/task-3/a.c tasks/task-3/builtin.c tasks/task-3/execute.c tasks/task-3/redirection.c tasks/task-3/tinyshell.h)
add_executable(3b tasks/task-3/b.c tasks/task-3/builtin.c tasks/task-3/execute.c tasks/task-3/redirection.c tasks/task-3/tinyshell.h)
add_executable(3c tasks/task-3/c.c tasks/task-3/builtin.c tasks/task-3/execute.c tasks/task-3/redirection.c tasks/task-3/tinyshell.h)
add_executable(3d tasks/task-3/d.c tasks/task-3/builtin.c tasks/task-3/execute.c tasks/task-3/redirection.c tasks/task-3/tinyshell.h)

## Task 4
add_executable(4a tasks/task-4/a.c tasks/task-4/builtin.c tasks/task-4/execute.c tasks/task-4/redirection.c tasks/task-4/tinyshell.h)
add_executable(4b tasks/task-4/b.c tasks/task-4/builtin.c tasks/task-4/execute.c tasks/task-4/redirection.c tasks/task-4/tinyshell.h)
add_executable(4c tasks/task-4/c.c tasks/task-4/builtin.c tasks/task-4/execute.c tasks/task-4/redirection.c tasks/task-4/tinyshell.h)

## TinyShell
add_executable(tinyshell tinyshell/tinyshell.c tinyshell/builtin.c tinyshell/execute.c tinyshell/redirection.c tinyshell/tinyshell.h)