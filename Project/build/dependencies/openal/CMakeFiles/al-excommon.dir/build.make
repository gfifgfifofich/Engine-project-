# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build

# Include any dependencies generated for this target.
include dependencies/openal/CMakeFiles/al-excommon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/al-excommon.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/al-excommon.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/al-excommon.dir/flags.make

dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o: dependencies/openal/CMakeFiles/al-excommon.dir/flags.make
dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/examples/common/alhelpers.c
dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o: dependencies/openal/CMakeFiles/al-excommon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o -MF CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o.d -o CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/examples/common/alhelpers.c

dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/examples/common/alhelpers.c > CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.i

dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/examples/common/alhelpers.c -o CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.s

# Object files for target al-excommon
al__excommon_OBJECTS = \
"CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o"

# External object files for target al-excommon
al__excommon_EXTERNAL_OBJECTS =

dependencies/openal/libal-excommon.a: dependencies/openal/CMakeFiles/al-excommon.dir/examples/common/alhelpers.c.o
dependencies/openal/libal-excommon.a: dependencies/openal/CMakeFiles/al-excommon.dir/build.make
dependencies/openal/libal-excommon.a: dependencies/openal/CMakeFiles/al-excommon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libal-excommon.a"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/al-excommon.dir/cmake_clean_target.cmake
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/al-excommon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/al-excommon.dir/build: dependencies/openal/libal-excommon.a
.PHONY : dependencies/openal/CMakeFiles/al-excommon.dir/build

dependencies/openal/CMakeFiles/al-excommon.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/al-excommon.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/al-excommon.dir/clean

dependencies/openal/CMakeFiles/al-excommon.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal/CMakeFiles/al-excommon.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/al-excommon.dir/depend

