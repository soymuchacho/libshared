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
CMAKE_SOURCE_DIR = /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93

# Include any dependencies generated for this target.
include src/lib/CMakeFiles/tolua++.dir/depend.make

# Include the progress variables for this target.
include src/lib/CMakeFiles/tolua++.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib/CMakeFiles/tolua++.dir/flags.make

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o: src/lib/CMakeFiles/tolua++.dir/flags.make
src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o: src/lib/tolua_to.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.dir/tolua_to.c.o   -c /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_to.c

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.dir/tolua_to.c.i"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_to.c > CMakeFiles/tolua++.dir/tolua_to.c.i

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.dir/tolua_to.c.s"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_to.c -o CMakeFiles/tolua++.dir/tolua_to.c.s

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.requires:
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.requires

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.provides: src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.requires
	$(MAKE) -f src/lib/CMakeFiles/tolua++.dir/build.make src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.provides.build
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.provides

src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.provides.build: src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o: src/lib/CMakeFiles/tolua++.dir/flags.make
src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o: src/lib/tolua_push.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.dir/tolua_push.c.o   -c /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_push.c

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.dir/tolua_push.c.i"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_push.c > CMakeFiles/tolua++.dir/tolua_push.c.i

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.dir/tolua_push.c.s"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_push.c -o CMakeFiles/tolua++.dir/tolua_push.c.s

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.requires:
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.requires

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.provides: src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.requires
	$(MAKE) -f src/lib/CMakeFiles/tolua++.dir/build.make src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.provides.build
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.provides

src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.provides.build: src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o: src/lib/CMakeFiles/tolua++.dir/flags.make
src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o: src/lib/tolua_map.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.dir/tolua_map.c.o   -c /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_map.c

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.dir/tolua_map.c.i"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_map.c > CMakeFiles/tolua++.dir/tolua_map.c.i

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.dir/tolua_map.c.s"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_map.c -o CMakeFiles/tolua++.dir/tolua_map.c.s

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.requires:
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.requires

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.provides: src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.requires
	$(MAKE) -f src/lib/CMakeFiles/tolua++.dir/build.make src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.provides.build
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.provides

src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.provides.build: src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o: src/lib/CMakeFiles/tolua++.dir/flags.make
src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o: src/lib/tolua_event.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.dir/tolua_event.c.o   -c /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_event.c

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.dir/tolua_event.c.i"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_event.c > CMakeFiles/tolua++.dir/tolua_event.c.i

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.dir/tolua_event.c.s"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_event.c -o CMakeFiles/tolua++.dir/tolua_event.c.s

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.requires:
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.requires

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.provides: src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.requires
	$(MAKE) -f src/lib/CMakeFiles/tolua++.dir/build.make src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.provides.build
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.provides

src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.provides.build: src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o: src/lib/CMakeFiles/tolua++.dir/flags.make
src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o: src/lib/tolua_is.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tolua++.dir/tolua_is.c.o   -c /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_is.c

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tolua++.dir/tolua_is.c.i"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_is.c > CMakeFiles/tolua++.dir/tolua_is.c.i

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tolua++.dir/tolua_is.c.s"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/tolua_is.c -o CMakeFiles/tolua++.dir/tolua_is.c.s

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.requires:
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.requires

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.provides: src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.requires
	$(MAKE) -f src/lib/CMakeFiles/tolua++.dir/build.make src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.provides.build
.PHONY : src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.provides

src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.provides.build: src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o

# Object files for target tolua++
tolua_______OBJECTS = \
"CMakeFiles/tolua++.dir/tolua_to.c.o" \
"CMakeFiles/tolua++.dir/tolua_push.c.o" \
"CMakeFiles/tolua++.dir/tolua_map.c.o" \
"CMakeFiles/tolua++.dir/tolua_event.c.o" \
"CMakeFiles/tolua++.dir/tolua_is.c.o"

# External object files for target tolua++
tolua_______EXTERNAL_OBJECTS =

/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/build.make
/opt/vesper/git/libshared/build/libtolua++.a: src/lib/CMakeFiles/tolua++.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library /opt/vesper/git/libshared/build/libtolua++.a"
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && $(CMAKE_COMMAND) -P CMakeFiles/tolua++.dir/cmake_clean_target.cmake
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tolua++.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib/CMakeFiles/tolua++.dir/build: /opt/vesper/git/libshared/build/libtolua++.a
.PHONY : src/lib/CMakeFiles/tolua++.dir/build

src/lib/CMakeFiles/tolua++.dir/requires: src/lib/CMakeFiles/tolua++.dir/tolua_to.c.o.requires
src/lib/CMakeFiles/tolua++.dir/requires: src/lib/CMakeFiles/tolua++.dir/tolua_push.c.o.requires
src/lib/CMakeFiles/tolua++.dir/requires: src/lib/CMakeFiles/tolua++.dir/tolua_map.c.o.requires
src/lib/CMakeFiles/tolua++.dir/requires: src/lib/CMakeFiles/tolua++.dir/tolua_event.c.o.requires
src/lib/CMakeFiles/tolua++.dir/requires: src/lib/CMakeFiles/tolua++.dir/tolua_is.c.o.requires
.PHONY : src/lib/CMakeFiles/tolua++.dir/requires

src/lib/CMakeFiles/tolua++.dir/clean:
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib && $(CMAKE_COMMAND) -P CMakeFiles/tolua++.dir/cmake_clean.cmake
.PHONY : src/lib/CMakeFiles/tolua++.dir/clean

src/lib/CMakeFiles/tolua++.dir/depend:
	cd /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93 /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93 /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib /opt/vesper/git/libshared/luaScript/lua/tolua++-1.0.93/src/lib/CMakeFiles/tolua++.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib/CMakeFiles/tolua++.dir/depend

