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
CMAKE_SOURCE_DIR = /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93

# Include any dependencies generated for this target.
include src/bin/CMakeFiles/tolua++.bin.dir/depend.make

# Include the progress variables for this target.
include src/bin/CMakeFiles/tolua++.bin.dir/progress.make

# Include the compile flags for this target's objects.
include src/bin/CMakeFiles/tolua++.bin.dir/flags.make

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o: src/bin/CMakeFiles/tolua++.bin.dir/flags.make
src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o: src/bin/tolua.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.bin.dir/tolua.c.o   -c /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.bin.dir/tolua.c.i"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c > CMakeFiles/tolua++.bin.dir/tolua.c.i

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.bin.dir/tolua.c.s"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/tolua.c -o CMakeFiles/tolua++.bin.dir/tolua.c.s

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.requires:
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.requires

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.provides: src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.requires
	$(MAKE) -f src/bin/CMakeFiles/tolua++.bin.dir/build.make src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.provides.build
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.provides

src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.provides.build: src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o: src/bin/CMakeFiles/tolua++.bin.dir/flags.make
src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o: src/bin/toluabind.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.bin.dir/toluabind.c.o   -c /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.bin.dir/toluabind.c.i"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c > CMakeFiles/tolua++.bin.dir/toluabind.c.i

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.bin.dir/toluabind.c.s"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/toluabind.c -o CMakeFiles/tolua++.bin.dir/toluabind.c.s

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.requires:
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.requires

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.provides: src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.requires
	$(MAKE) -f src/bin/CMakeFiles/tolua++.bin.dir/build.make src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.provides.build
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.provides

src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.provides.build: src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o

# Object files for target tolua++.bin
tolua_______bin_OBJECTS = \
"CMakeFiles/tolua++.bin.dir/tolua.c.o" \
"CMakeFiles/tolua++.bin.dir/toluabind.c.o"

# External object files for target tolua++.bin
tolua_______bin_EXTERNAL_OBJECTS =

bin/tolua++.bin: src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o
bin/tolua++.bin: src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o
bin/tolua++.bin: src/bin/CMakeFiles/tolua++.bin.dir/build.make
bin/tolua++.bin: /opt/vesper/workspace/trunk/program_demo/Share/lua/lib/linux/libtolua++.a
bin/tolua++.bin: src/bin/CMakeFiles/tolua++.bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../bin/tolua++.bin"
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tolua++.bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/bin/CMakeFiles/tolua++.bin.dir/build: bin/tolua++.bin
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/build

src/bin/CMakeFiles/tolua++.bin.dir/requires: src/bin/CMakeFiles/tolua++.bin.dir/tolua.c.o.requires
src/bin/CMakeFiles/tolua++.bin.dir/requires: src/bin/CMakeFiles/tolua++.bin.dir/toluabind.c.o.requires
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/requires

src/bin/CMakeFiles/tolua++.bin.dir/clean:
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin && $(CMAKE_COMMAND) -P CMakeFiles/tolua++.bin.dir/cmake_clean.cmake
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/clean

src/bin/CMakeFiles/tolua++.bin.dir/depend:
	cd /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93 /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93 /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin /opt/vesper/workspace/trunk/program_demo/Share/lua/tolua++-1.0.93/src/bin/CMakeFiles/tolua++.bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bin/CMakeFiles/tolua++.bin.dir/depend

