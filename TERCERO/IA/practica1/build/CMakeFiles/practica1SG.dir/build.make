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
CMAKE_SOURCE_DIR = /home/lauralazaro/Escritorio/GITHUB/IA/practica1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lauralazaro/Escritorio/GITHUB/IA/practica1/build

# Include any dependencies generated for this target.
include CMakeFiles/practica1SG.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/practica1SG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/practica1SG.dir/flags.make

CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o: CMakeFiles/practica1SG.dir/flags.make
CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o: ../bin_src/juegoSG.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lauralazaro/Escritorio/GITHUB/IA/practica1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o -c /home/lauralazaro/Escritorio/GITHUB/IA/practica1/bin_src/juegoSG.cc

CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lauralazaro/Escritorio/GITHUB/IA/practica1/bin_src/juegoSG.cc > CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.i

CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lauralazaro/Escritorio/GITHUB/IA/practica1/bin_src/juegoSG.cc -o CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.s

# Object files for target practica1SG
practica1SG_OBJECTS = \
"CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o"

# External object files for target practica1SG
practica1SG_EXTERNAL_OBJECTS =

practica1SG: CMakeFiles/practica1SG.dir/bin_src/juegoSG.cc.o
practica1SG: CMakeFiles/practica1SG.dir/build.make
practica1SG: lib/libobj3DLib.a
practica1SG: lib/libmotorLib.a
practica1SG: lib/libmodelosBelkanLib.a
practica1SG: lib/libGLUILib.a
practica1SG: lib/libcomportamientosLib.a
practica1SG: lib/libobj3DLib.a
practica1SG: /usr/lib/x86_64-linux-gnu/libjpeg.so
practica1SG: /usr/lib/x86_64-linux-gnu/libGL.so
practica1SG: /usr/lib/x86_64-linux-gnu/libGLU.so
practica1SG: /usr/lib/x86_64-linux-gnu/libglut.so
practica1SG: /usr/lib/x86_64-linux-gnu/libXmu.so
practica1SG: /usr/lib/x86_64-linux-gnu/libXi.so
practica1SG: CMakeFiles/practica1SG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lauralazaro/Escritorio/GITHUB/IA/practica1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable practica1SG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/practica1SG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/practica1SG.dir/build: practica1SG

.PHONY : CMakeFiles/practica1SG.dir/build

CMakeFiles/practica1SG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/practica1SG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/practica1SG.dir/clean

CMakeFiles/practica1SG.dir/depend:
	cd /home/lauralazaro/Escritorio/GITHUB/IA/practica1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lauralazaro/Escritorio/GITHUB/IA/practica1 /home/lauralazaro/Escritorio/GITHUB/IA/practica1 /home/lauralazaro/Escritorio/GITHUB/IA/practica1/build /home/lauralazaro/Escritorio/GITHUB/IA/practica1/build /home/lauralazaro/Escritorio/GITHUB/IA/practica1/build/CMakeFiles/practica1SG.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/practica1SG.dir/depend

