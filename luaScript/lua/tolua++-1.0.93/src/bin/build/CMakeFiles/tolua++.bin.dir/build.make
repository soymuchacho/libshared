# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build

# Include any dependencies generated for this target.
include CMakeFiles/tolua++.bin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tolua++.bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tolua++.bin.dir/flags.make

CMakeFiles/tolua++.bin.dir/tolua.o: CMakeFiles/tolua++.bin.dir/flags.make
CMakeFiles/tolua++.bin.dir/tolua.o: ../tolua.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/tolua++.bin.dir/tolua.o"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.bin.dir/tolua.o   -c /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c

CMakeFiles/tolua++.bin.dir/tolua.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.bin.dir/tolua.i"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c > CMakeFiles/tolua++.bin.dir/tolua.i

CMakeFiles/tolua++.bin.dir/tolua.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.bin.dir/tolua.s"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c -o CMakeFiles/tolua++.bin.dir/tolua.s

CMakeFiles/tolua++.bin.dir/tolua.o.requires:
.PHONY : CMakeFiles/tolua++.bin.dir/tolua.o.requires

CMakeFiles/tolua++.bin.dir/tolua.o.provides: CMakeFiles/tolua++.bin.dir/tolua.o.requires
	$(MAKE) -f CMakeFiles/tolua++.bin.dir/build.make CMakeFiles/tolua++.bin.dir/tolua.o.provides.build
.PHONY : CMakeFiles/tolua++.bin.dir/tolua.o.provides

CMakeFiles/tolua++.bin.dir/tolua.o.provides.build: CMakeFiles/tolua++.bin.dir/tolua.o

CMakeFiles/tolua++.bin.dir/toluabind.o: CMakeFiles/tolua++.bin.dir/flags.make
CMakeFiles/tolua++.bin.dir/toluabind.o: ../toluabind.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/tolua++.bin.dir/toluabind.o"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.bin.dir/toluabind.o   -c /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c

CMakeFiles/tolua++.bin.dir/toluabind.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.bin.dir/toluabind.i"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c > CMakeFiles/tolua++.bin.dir/toluabind.i

CMakeFiles/tolua++.bin.dir/toluabind.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.bin.dir/toluabind.s"
	/usr/local/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c -o CMakeFiles/tolua++.bin.dir/toluabind.s

CMakeFiles/tolua++.bin.dir/toluabind.o.requires:
.PHONY : CMakeFiles/tolua++.bin.dir/toluabind.o.requires

CMakeFiles/tolua++.bin.dir/toluabind.o.provides: CMakeFiles/tolua++.bin.dir/toluabind.o.requires
	$(MAKE) -f CMakeFiles/tolua++.bin.dir/build.make CMakeFiles/tolua++.bin.dir/toluabind.o.provides.build
.PHONY : CMakeFiles/tolua++.bin.dir/toluabind.o.provides

CMakeFiles/tolua++.bin.dir/toluabind.o.provides.build: CMakeFiles/tolua++.bin.dir/toluabind.o

# Object files for target tolua++.bin
tolua_______bin_OBJECTS = \
"CMakeFiles/tolua++.bin.dir/tolua.o" \
"CMakeFiles/tolua++.bin.dir/toluabind.o"

# External object files for target tolua++.bin
tolua_______bin_EXTERNAL_OBJECTS =

../bin/tolua++.bin: CMakeFiles/tolua++.bin.dir/tolua.o
../bin/tolua++.bin: CMakeFiles/tolua++.bin.dir/toluabind.o
../bin/tolua++.bin: CMakeFiles/tolua++.bin.dir/build.make
../bin/tolua++.bin: CMakeFiles/tolua++.bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/tolua++.bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tolua++.bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tolua++.bin.dir/build: ../bin/tolua++.bin
.PHONY : CMakeFiles/tolua++.bin.dir/build

CMakeFiles/tolua++.bin.dir/requires: CMakeFiles/tolua++.bin.dir/tolua.o.requires
CMakeFiles/tolua++.bin.dir/requires: CMakeFiles/tolua++.bin.dir/toluabind.o.requires
.PHONY : CMakeFiles/tolua++.bin.dir/requires

CMakeFiles/tolua++.bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tolua++.bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tolua++.bin.dir/clean

CMakeFiles/tolua++.bin.dir/depend:
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/build/CMakeFiles/tolua++.bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tolua++.bin.dir/depend
