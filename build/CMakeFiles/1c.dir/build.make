# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/heliaea/Programming/Assignments/cps1012-assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heliaea/Programming/Assignments/cps1012-assignment/build

# Include any dependencies generated for this target.
include CMakeFiles/1c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1c.dir/flags.make

CMakeFiles/1c.dir/tasks/task-1/c.c.o: CMakeFiles/1c.dir/flags.make
CMakeFiles/1c.dir/tasks/task-1/c.c.o: ../tasks/task-1/c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/1c.dir/tasks/task-1/c.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/1c.dir/tasks/task-1/c.c.o   -c /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-1/c.c

CMakeFiles/1c.dir/tasks/task-1/c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/1c.dir/tasks/task-1/c.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-1/c.c > CMakeFiles/1c.dir/tasks/task-1/c.c.i

CMakeFiles/1c.dir/tasks/task-1/c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/1c.dir/tasks/task-1/c.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-1/c.c -o CMakeFiles/1c.dir/tasks/task-1/c.c.s

# Object files for target 1c
1c_OBJECTS = \
"CMakeFiles/1c.dir/tasks/task-1/c.c.o"

# External object files for target 1c
1c_EXTERNAL_OBJECTS =

1c: CMakeFiles/1c.dir/tasks/task-1/c.c.o
1c: CMakeFiles/1c.dir/build.make
1c: CMakeFiles/1c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 1c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1c.dir/build: 1c

.PHONY : CMakeFiles/1c.dir/build

CMakeFiles/1c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1c.dir/clean

CMakeFiles/1c.dir/depend:
	cd /home/heliaea/Programming/Assignments/cps1012-assignment/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heliaea/Programming/Assignments/cps1012-assignment /home/heliaea/Programming/Assignments/cps1012-assignment /home/heliaea/Programming/Assignments/cps1012-assignment/build /home/heliaea/Programming/Assignments/cps1012-assignment/build /home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles/1c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1c.dir/depend

