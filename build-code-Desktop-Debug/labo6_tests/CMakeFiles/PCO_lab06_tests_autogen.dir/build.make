# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/reds/pco/lab6/pco23_lab06/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug

# Utility rule file for PCO_lab06_tests_autogen.

# Include any custom commands dependencies for this target.
include labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/progress.make

labo6_tests/CMakeFiles/PCO_lab06_tests_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target PCO_lab06_tests"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/labo6_tests && /usr/bin/cmake -E cmake_autogen /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/AutogenInfo.json Debug

PCO_lab06_tests_autogen: labo6_tests/CMakeFiles/PCO_lab06_tests_autogen
PCO_lab06_tests_autogen: labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/build.make
.PHONY : PCO_lab06_tests_autogen

# Rule to build all files generated by this target.
labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/build: PCO_lab06_tests_autogen
.PHONY : labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/build

labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/clean:
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/labo6_tests && $(CMAKE_COMMAND) -P CMakeFiles/PCO_lab06_tests_autogen.dir/cmake_clean.cmake
.PHONY : labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/clean

labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/depend:
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reds/pco/lab6/pco23_lab06/code /home/reds/pco/lab6/pco23_lab06/code/labo6_tests /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/labo6_tests /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : labo6_tests/CMakeFiles/PCO_lab06_tests_autogen.dir/depend
