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
include CMakeFiles/2b.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2b.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2b.dir/flags.make

CMakeFiles/2b.dir/tasks/task-2/b.c.o: CMakeFiles/2b.dir/flags.make
CMakeFiles/2b.dir/tasks/task-2/b.c.o: ../tasks/task-2/b.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/2b.dir/tasks/task-2/b.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/2b.dir/tasks/task-2/b.c.o   -c /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-2/b.c

CMakeFiles/2b.dir/tasks/task-2/b.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2b.dir/tasks/task-2/b.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-2/b.c > CMakeFiles/2b.dir/tasks/task-2/b.c.i

CMakeFiles/2b.dir/tasks/task-2/b.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2b.dir/tasks/task-2/b.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heliaea/Programming/Assignments/cps1012-assignment/tasks/task-2/b.c -o CMakeFiles/2b.dir/tasks/task-2/b.c.s

# Object files for target 2b
2b_OBJECTS = \
"CMakeFiles/2b.dir/tasks/task-2/b.c.o"

# External object files for target 2b
2b_EXTERNAL_OBJECTS =

2b: CMakeFiles/2b.dir/tasks/task-2/b.c.o
2b: CMakeFiles/2b.dir/build.make
2b: CMakeFiles/2b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 2b"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2b.dir/build: 2b

.PHONY : CMakeFiles/2b.dir/build

CMakeFiles/2b.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2b.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2b.dir/clean

CMakeFiles/2b.dir/depend:
	cd /home/heliaea/Programming/Assignments/cps1012-assignment/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heliaea/Programming/Assignments/cps1012-assignment /home/heliaea/Programming/Assignments/cps1012-assignment /home/heliaea/Programming/Assignments/cps1012-assignment/build /home/heliaea/Programming/Assignments/cps1012-assignment/build /home/heliaea/Programming/Assignments/cps1012-assignment/build/CMakeFiles/2b.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2b.dir/depend

