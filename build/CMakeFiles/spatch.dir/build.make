# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/syzik/spatch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/syzik/spatch/build

# Include any dependencies generated for this target.
include CMakeFiles/spatch.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/spatch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/spatch.dir/flags.make

CMakeFiles/spatch.dir/sources/endpoint.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/endpoint.c.o: ../sources/endpoint.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/spatch.dir/sources/endpoint.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/endpoint.c.o   -c /home/syzik/spatch/sources/endpoint.c

CMakeFiles/spatch.dir/sources/endpoint.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/endpoint.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/endpoint.c > CMakeFiles/spatch.dir/sources/endpoint.c.i

CMakeFiles/spatch.dir/sources/endpoint.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/endpoint.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/endpoint.c -o CMakeFiles/spatch.dir/sources/endpoint.c.s

CMakeFiles/spatch.dir/sources/endpoint.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/endpoint.c.o.requires

CMakeFiles/spatch.dir/sources/endpoint.c.o.provides: CMakeFiles/spatch.dir/sources/endpoint.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/endpoint.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/endpoint.c.o.provides

CMakeFiles/spatch.dir/sources/endpoint.c.o.provides.build: CMakeFiles/spatch.dir/sources/endpoint.c.o


CMakeFiles/spatch.dir/sources/fs.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/fs.c.o: ../sources/fs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/spatch.dir/sources/fs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/fs.c.o   -c /home/syzik/spatch/sources/fs.c

CMakeFiles/spatch.dir/sources/fs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/fs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/fs.c > CMakeFiles/spatch.dir/sources/fs.c.i

CMakeFiles/spatch.dir/sources/fs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/fs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/fs.c -o CMakeFiles/spatch.dir/sources/fs.c.s

CMakeFiles/spatch.dir/sources/fs.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/fs.c.o.requires

CMakeFiles/spatch.dir/sources/fs.c.o.provides: CMakeFiles/spatch.dir/sources/fs.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/fs.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/fs.c.o.provides

CMakeFiles/spatch.dir/sources/fs.c.o.provides.build: CMakeFiles/spatch.dir/sources/fs.c.o


CMakeFiles/spatch.dir/sources/group.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/group.c.o: ../sources/group.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/spatch.dir/sources/group.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/group.c.o   -c /home/syzik/spatch/sources/group.c

CMakeFiles/spatch.dir/sources/group.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/group.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/group.c > CMakeFiles/spatch.dir/sources/group.c.i

CMakeFiles/spatch.dir/sources/group.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/group.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/group.c -o CMakeFiles/spatch.dir/sources/group.c.s

CMakeFiles/spatch.dir/sources/group.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/group.c.o.requires

CMakeFiles/spatch.dir/sources/group.c.o.provides: CMakeFiles/spatch.dir/sources/group.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/group.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/group.c.o.provides

CMakeFiles/spatch.dir/sources/group.c.o.provides.build: CMakeFiles/spatch.dir/sources/group.c.o


CMakeFiles/spatch.dir/sources/list.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/list.c.o: ../sources/list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/spatch.dir/sources/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/list.c.o   -c /home/syzik/spatch/sources/list.c

CMakeFiles/spatch.dir/sources/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/list.c > CMakeFiles/spatch.dir/sources/list.c.i

CMakeFiles/spatch.dir/sources/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/list.c -o CMakeFiles/spatch.dir/sources/list.c.s

CMakeFiles/spatch.dir/sources/list.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/list.c.o.requires

CMakeFiles/spatch.dir/sources/list.c.o.provides: CMakeFiles/spatch.dir/sources/list.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/list.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/list.c.o.provides

CMakeFiles/spatch.dir/sources/list.c.o.provides.build: CMakeFiles/spatch.dir/sources/list.c.o


CMakeFiles/spatch.dir/sources/parser.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/parser.c.o: ../sources/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/spatch.dir/sources/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/parser.c.o   -c /home/syzik/spatch/sources/parser.c

CMakeFiles/spatch.dir/sources/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/parser.c > CMakeFiles/spatch.dir/sources/parser.c.i

CMakeFiles/spatch.dir/sources/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/parser.c -o CMakeFiles/spatch.dir/sources/parser.c.s

CMakeFiles/spatch.dir/sources/parser.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/parser.c.o.requires

CMakeFiles/spatch.dir/sources/parser.c.o.provides: CMakeFiles/spatch.dir/sources/parser.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/parser.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/parser.c.o.provides

CMakeFiles/spatch.dir/sources/parser.c.o.provides.build: CMakeFiles/spatch.dir/sources/parser.c.o


CMakeFiles/spatch.dir/sources/sys_auth.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/sys_auth.c.o: ../sources/sys_auth.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/spatch.dir/sources/sys_auth.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/sys_auth.c.o   -c /home/syzik/spatch/sources/sys_auth.c

CMakeFiles/spatch.dir/sources/sys_auth.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/sys_auth.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/sys_auth.c > CMakeFiles/spatch.dir/sources/sys_auth.c.i

CMakeFiles/spatch.dir/sources/sys_auth.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/sys_auth.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/sys_auth.c -o CMakeFiles/spatch.dir/sources/sys_auth.c.s

CMakeFiles/spatch.dir/sources/sys_auth.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/sys_auth.c.o.requires

CMakeFiles/spatch.dir/sources/sys_auth.c.o.provides: CMakeFiles/spatch.dir/sources/sys_auth.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/sys_auth.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/sys_auth.c.o.provides

CMakeFiles/spatch.dir/sources/sys_auth.c.o.provides.build: CMakeFiles/spatch.dir/sources/sys_auth.c.o


CMakeFiles/spatch.dir/sources/user.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/user.c.o: ../sources/user.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/spatch.dir/sources/user.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/user.c.o   -c /home/syzik/spatch/sources/user.c

CMakeFiles/spatch.dir/sources/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/user.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/user.c > CMakeFiles/spatch.dir/sources/user.c.i

CMakeFiles/spatch.dir/sources/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/user.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/user.c -o CMakeFiles/spatch.dir/sources/user.c.s

CMakeFiles/spatch.dir/sources/user.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/user.c.o.requires

CMakeFiles/spatch.dir/sources/user.c.o.provides: CMakeFiles/spatch.dir/sources/user.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/user.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/user.c.o.provides

CMakeFiles/spatch.dir/sources/user.c.o.provides.build: CMakeFiles/spatch.dir/sources/user.c.o


CMakeFiles/spatch.dir/sources/spatch.c.o: CMakeFiles/spatch.dir/flags.make
CMakeFiles/spatch.dir/sources/spatch.c.o: ../sources/spatch.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/spatch.dir/sources/spatch.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spatch.dir/sources/spatch.c.o   -c /home/syzik/spatch/sources/spatch.c

CMakeFiles/spatch.dir/sources/spatch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spatch.dir/sources/spatch.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/syzik/spatch/sources/spatch.c > CMakeFiles/spatch.dir/sources/spatch.c.i

CMakeFiles/spatch.dir/sources/spatch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spatch.dir/sources/spatch.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/syzik/spatch/sources/spatch.c -o CMakeFiles/spatch.dir/sources/spatch.c.s

CMakeFiles/spatch.dir/sources/spatch.c.o.requires:

.PHONY : CMakeFiles/spatch.dir/sources/spatch.c.o.requires

CMakeFiles/spatch.dir/sources/spatch.c.o.provides: CMakeFiles/spatch.dir/sources/spatch.c.o.requires
	$(MAKE) -f CMakeFiles/spatch.dir/build.make CMakeFiles/spatch.dir/sources/spatch.c.o.provides.build
.PHONY : CMakeFiles/spatch.dir/sources/spatch.c.o.provides

CMakeFiles/spatch.dir/sources/spatch.c.o.provides.build: CMakeFiles/spatch.dir/sources/spatch.c.o


# Object files for target spatch
spatch_OBJECTS = \
"CMakeFiles/spatch.dir/sources/endpoint.c.o" \
"CMakeFiles/spatch.dir/sources/fs.c.o" \
"CMakeFiles/spatch.dir/sources/group.c.o" \
"CMakeFiles/spatch.dir/sources/list.c.o" \
"CMakeFiles/spatch.dir/sources/parser.c.o" \
"CMakeFiles/spatch.dir/sources/sys_auth.c.o" \
"CMakeFiles/spatch.dir/sources/user.c.o" \
"CMakeFiles/spatch.dir/sources/spatch.c.o"

# External object files for target spatch
spatch_EXTERNAL_OBJECTS =

spatch: CMakeFiles/spatch.dir/sources/endpoint.c.o
spatch: CMakeFiles/spatch.dir/sources/fs.c.o
spatch: CMakeFiles/spatch.dir/sources/group.c.o
spatch: CMakeFiles/spatch.dir/sources/list.c.o
spatch: CMakeFiles/spatch.dir/sources/parser.c.o
spatch: CMakeFiles/spatch.dir/sources/sys_auth.c.o
spatch: CMakeFiles/spatch.dir/sources/user.c.o
spatch: CMakeFiles/spatch.dir/sources/spatch.c.o
spatch: CMakeFiles/spatch.dir/build.make
spatch: /usr/lib/libssh.so
spatch: /usr/lib/libpam.so
spatch: /usr/lib/libdl.so
spatch: CMakeFiles/spatch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/syzik/spatch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable spatch"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spatch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/spatch.dir/build: spatch

.PHONY : CMakeFiles/spatch.dir/build

CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/endpoint.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/fs.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/group.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/list.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/parser.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/sys_auth.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/user.c.o.requires
CMakeFiles/spatch.dir/requires: CMakeFiles/spatch.dir/sources/spatch.c.o.requires

.PHONY : CMakeFiles/spatch.dir/requires

CMakeFiles/spatch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/spatch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/spatch.dir/clean

CMakeFiles/spatch.dir/depend:
	cd /home/syzik/spatch/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/syzik/spatch /home/syzik/spatch /home/syzik/spatch/build /home/syzik/spatch/build /home/syzik/spatch/build/CMakeFiles/spatch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/spatch.dir/depend
