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
CMAKE_SOURCE_DIR = /workspaces/PHAS0100Assignment2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/PHAS0100Assignment2/build

# Include any dependencies generated for this target.
include Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/depend.make

# Include the progress variables for this target.
include Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/progress.make

# Include the compile flags for this target's objects.
include Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/flags.make

Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o: Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/flags.make
Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o: ../Code/CommandLineApps/solarSystemSimulator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/PHAS0100Assignment2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o"
	cd /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o -c /workspaces/PHAS0100Assignment2/Code/CommandLineApps/solarSystemSimulator.cpp

Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.i"
	cd /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/PHAS0100Assignment2/Code/CommandLineApps/solarSystemSimulator.cpp > CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.i

Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.s"
	cd /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/PHAS0100Assignment2/Code/CommandLineApps/solarSystemSimulator.cpp -o CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.s

# Object files for target solarSystemSimulator
solarSystemSimulator_OBJECTS = \
"CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o"

# External object files for target solarSystemSimulator
solarSystemSimulator_EXTERNAL_OBJECTS =

bin/solarSystemSimulator: Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/solarSystemSimulator.cpp.o
bin/solarSystemSimulator: Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/build.make
bin/solarSystemSimulator: Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/PHAS0100Assignment2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/solarSystemSimulator"
	cd /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solarSystemSimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/build: bin/solarSystemSimulator

.PHONY : Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/build

Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/clean:
	cd /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps && $(CMAKE_COMMAND) -P CMakeFiles/solarSystemSimulator.dir/cmake_clean.cmake
.PHONY : Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/clean

Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/depend:
	cd /workspaces/PHAS0100Assignment2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/PHAS0100Assignment2 /workspaces/PHAS0100Assignment2/Code/CommandLineApps /workspaces/PHAS0100Assignment2/build /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps /workspaces/PHAS0100Assignment2/build/Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Code/CommandLineApps/CMakeFiles/solarSystemSimulator.dir/depend

