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

# Include any dependencies generated for this target.
include src/CMakeFiles/labo6_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/labo6_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/labo6_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/labo6_lib.dir/flags.make

src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o: src/CMakeFiles/labo6_lib.dir/flags.make
src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o: /home/reds/pco/lab6/pco23_lab06/code/src/computationmanager.cpp
src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o: src/CMakeFiles/labo6_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o -MF CMakeFiles/labo6_lib.dir/computationmanager.cpp.o.d -o CMakeFiles/labo6_lib.dir/computationmanager.cpp.o -c /home/reds/pco/lab6/pco23_lab06/code/src/computationmanager.cpp

src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/labo6_lib.dir/computationmanager.cpp.i"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reds/pco/lab6/pco23_lab06/code/src/computationmanager.cpp > CMakeFiles/labo6_lib.dir/computationmanager.cpp.i

src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/labo6_lib.dir/computationmanager.cpp.s"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reds/pco/lab6/pco23_lab06/code/src/computationmanager.cpp -o CMakeFiles/labo6_lib.dir/computationmanager.cpp.s

src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o: src/CMakeFiles/labo6_lib.dir/flags.make
src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o: /home/reds/pco/lab6/pco23_lab06/code/src/computeengine.cpp
src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o: src/CMakeFiles/labo6_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o -MF CMakeFiles/labo6_lib.dir/computeengine.cpp.o.d -o CMakeFiles/labo6_lib.dir/computeengine.cpp.o -c /home/reds/pco/lab6/pco23_lab06/code/src/computeengine.cpp

src/CMakeFiles/labo6_lib.dir/computeengine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/labo6_lib.dir/computeengine.cpp.i"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reds/pco/lab6/pco23_lab06/code/src/computeengine.cpp > CMakeFiles/labo6_lib.dir/computeengine.cpp.i

src/CMakeFiles/labo6_lib.dir/computeengine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/labo6_lib.dir/computeengine.cpp.s"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reds/pco/lab6/pco23_lab06/code/src/computeengine.cpp -o CMakeFiles/labo6_lib.dir/computeengine.cpp.s

# Object files for target labo6_lib
labo6_lib_OBJECTS = \
"CMakeFiles/labo6_lib.dir/computationmanager.cpp.o" \
"CMakeFiles/labo6_lib.dir/computeengine.cpp.o"

# External object files for target labo6_lib
labo6_lib_EXTERNAL_OBJECTS =

src/liblabo6_lib.a: src/CMakeFiles/labo6_lib.dir/computationmanager.cpp.o
src/liblabo6_lib.a: src/CMakeFiles/labo6_lib.dir/computeengine.cpp.o
src/liblabo6_lib.a: src/CMakeFiles/labo6_lib.dir/build.make
src/liblabo6_lib.a: src/CMakeFiles/labo6_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library liblabo6_lib.a"
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && $(CMAKE_COMMAND) -P CMakeFiles/labo6_lib.dir/cmake_clean_target.cmake
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/labo6_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/labo6_lib.dir/build: src/liblabo6_lib.a
.PHONY : src/CMakeFiles/labo6_lib.dir/build

src/CMakeFiles/labo6_lib.dir/clean:
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src && $(CMAKE_COMMAND) -P CMakeFiles/labo6_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/labo6_lib.dir/clean

src/CMakeFiles/labo6_lib.dir/depend:
	cd /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reds/pco/lab6/pco23_lab06/code /home/reds/pco/lab6/pco23_lab06/code/src /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src /home/reds/pco/lab6/pco23_lab06/build-code-Desktop-Debug/src/CMakeFiles/labo6_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/labo6_lib.dir/depend
