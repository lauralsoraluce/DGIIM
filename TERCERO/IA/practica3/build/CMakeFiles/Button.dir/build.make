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
CMAKE_SOURCE_DIR = /home/lauralazaro/Escritorio/GITHUB/IA/practica3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lauralazaro/Escritorio/GITHUB/IA/practica3/build

# Include any dependencies generated for this target.
include CMakeFiles/Button.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Button.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Button.dir/flags.make

CMakeFiles/Button.dir/src/Button.cpp.o: CMakeFiles/Button.dir/flags.make
CMakeFiles/Button.dir/src/Button.cpp.o: ../src/Button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lauralazaro/Escritorio/GITHUB/IA/practica3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Button.dir/src/Button.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Button.dir/src/Button.cpp.o -c /home/lauralazaro/Escritorio/GITHUB/IA/practica3/src/Button.cpp

CMakeFiles/Button.dir/src/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Button.dir/src/Button.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lauralazaro/Escritorio/GITHUB/IA/practica3/src/Button.cpp > CMakeFiles/Button.dir/src/Button.cpp.i

CMakeFiles/Button.dir/src/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Button.dir/src/Button.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lauralazaro/Escritorio/GITHUB/IA/practica3/src/Button.cpp -o CMakeFiles/Button.dir/src/Button.cpp.s

# Object files for target Button
Button_OBJECTS = \
"CMakeFiles/Button.dir/src/Button.cpp.o"

# External object files for target Button
Button_EXTERNAL_OBJECTS =

lib/libButton.a: CMakeFiles/Button.dir/src/Button.cpp.o
lib/libButton.a: CMakeFiles/Button.dir/build.make
lib/libButton.a: CMakeFiles/Button.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lauralazaro/Escritorio/GITHUB/IA/practica3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library lib/libButton.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Button.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Button.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Button.dir/build: lib/libButton.a

.PHONY : CMakeFiles/Button.dir/build

CMakeFiles/Button.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Button.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Button.dir/clean

CMakeFiles/Button.dir/depend:
	cd /home/lauralazaro/Escritorio/GITHUB/IA/practica3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lauralazaro/Escritorio/GITHUB/IA/practica3 /home/lauralazaro/Escritorio/GITHUB/IA/practica3 /home/lauralazaro/Escritorio/GITHUB/IA/practica3/build /home/lauralazaro/Escritorio/GITHUB/IA/practica3/build /home/lauralazaro/Escritorio/GITHUB/IA/practica3/build/CMakeFiles/Button.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Button.dir/depend
