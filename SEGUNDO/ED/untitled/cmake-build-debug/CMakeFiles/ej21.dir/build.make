# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lauralazaro/Escritorio/ED/untitled

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ej21.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ej21.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ej21.dir/flags.make

CMakeFiles/ej21.dir/ej21.cpp.o: CMakeFiles/ej21.dir/flags.make
CMakeFiles/ej21.dir/ej21.cpp.o: ../ej21.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ej21.dir/ej21.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ej21.dir/ej21.cpp.o -c /home/lauralazaro/Escritorio/ED/untitled/ej21.cpp

CMakeFiles/ej21.dir/ej21.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ej21.dir/ej21.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lauralazaro/Escritorio/ED/untitled/ej21.cpp > CMakeFiles/ej21.dir/ej21.cpp.i

CMakeFiles/ej21.dir/ej21.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ej21.dir/ej21.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lauralazaro/Escritorio/ED/untitled/ej21.cpp -o CMakeFiles/ej21.dir/ej21.cpp.s

# Object files for target ej21
ej21_OBJECTS = \
"CMakeFiles/ej21.dir/ej21.cpp.o"

# External object files for target ej21
ej21_EXTERNAL_OBJECTS =

ej21: CMakeFiles/ej21.dir/ej21.cpp.o
ej21: CMakeFiles/ej21.dir/build.make
ej21: CMakeFiles/ej21.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ej21"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ej21.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ej21.dir/build: ej21
.PHONY : CMakeFiles/ej21.dir/build

CMakeFiles/ej21.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ej21.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ej21.dir/clean

CMakeFiles/ej21.dir/depend:
	cd /home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lauralazaro/Escritorio/ED/untitled /home/lauralazaro/Escritorio/ED/untitled /home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug /home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug /home/lauralazaro/Escritorio/ED/untitled/cmake-build-debug/CMakeFiles/ej21.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ej21.dir/depend
