# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build

# Include any dependencies generated for this target.
include dependencies/openal/CMakeFiles/almultireverb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/almultireverb.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/almultireverb.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/almultireverb.dir/flags.make

dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o: dependencies/openal/CMakeFiles/almultireverb.dir/flags.make
dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/openal/examples/almultireverb.c
dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o: dependencies/openal/CMakeFiles/almultireverb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o -MF CMakeFiles/almultireverb.dir/examples/almultireverb.c.o.d -o CMakeFiles/almultireverb.dir/examples/almultireverb.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/openal/examples/almultireverb.c

dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/almultireverb.dir/examples/almultireverb.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/openal/examples/almultireverb.c > CMakeFiles/almultireverb.dir/examples/almultireverb.c.i

dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/almultireverb.dir/examples/almultireverb.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/openal/examples/almultireverb.c -o CMakeFiles/almultireverb.dir/examples/almultireverb.c.s

# Object files for target almultireverb
almultireverb_OBJECTS = \
"CMakeFiles/almultireverb.dir/examples/almultireverb.c.o"

# External object files for target almultireverb
almultireverb_EXTERNAL_OBJECTS =

dependencies/openal/almultireverb: dependencies/openal/CMakeFiles/almultireverb.dir/examples/almultireverb.c.o
dependencies/openal/almultireverb: dependencies/openal/CMakeFiles/almultireverb.dir/build.make
dependencies/openal/almultireverb: /usr/lib/libsndfile.so
dependencies/openal/almultireverb: dependencies/openal/libal-excommon.a
dependencies/openal/almultireverb: dependencies/openal/libopenal.so.1.23.1
dependencies/openal/almultireverb: dependencies/openal/CMakeFiles/almultireverb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable almultireverb"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/almultireverb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/almultireverb.dir/build: dependencies/openal/almultireverb
.PHONY : dependencies/openal/CMakeFiles/almultireverb.dir/build

dependencies/openal/CMakeFiles/almultireverb.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/almultireverb.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/almultireverb.dir/clean

dependencies/openal/CMakeFiles/almultireverb.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/openal/CMakeFiles/almultireverb.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/almultireverb.dir/depend

