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
include dependencies/GLFW/tests/CMakeFiles/inputlag.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/tests/CMakeFiles/inputlag.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/tests/CMakeFiles/inputlag.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/tests/CMakeFiles/inputlag.dir/flags.make

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/tests/inputlag.c
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o -MF CMakeFiles/inputlag.dir/inputlag.c.o.d -o CMakeFiles/inputlag.dir/inputlag.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/tests/inputlag.c

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/inputlag.dir/inputlag.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/tests/inputlag.c > CMakeFiles/inputlag.dir/inputlag.c.i

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/inputlag.dir/inputlag.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/tests/inputlag.c -o CMakeFiles/inputlag.dir/inputlag.c.s

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/getopt.c
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o -MF CMakeFiles/inputlag.dir/__/deps/getopt.c.o.d -o CMakeFiles/inputlag.dir/__/deps/getopt.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/getopt.c

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/getopt.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/getopt.c > CMakeFiles/inputlag.dir/__/deps/getopt.c.i

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/getopt.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/getopt.c -o CMakeFiles/inputlag.dir/__/deps/getopt.c.s

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -MF CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c > CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s

# Object files for target inputlag
inputlag_OBJECTS = \
"CMakeFiles/inputlag.dir/inputlag.c.o" \
"CMakeFiles/inputlag.dir/__/deps/getopt.c.o" \
"CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"

# External object files for target inputlag
inputlag_EXTERNAL_OBJECTS =

dependencies/GLFW/tests/inputlag: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/inputlag.c.o
dependencies/GLFW/tests/inputlag: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o
dependencies/GLFW/tests/inputlag: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o
dependencies/GLFW/tests/inputlag: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/build.make
dependencies/GLFW/tests/inputlag: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/tests/inputlag: /usr/lib/libm.so
dependencies/GLFW/tests/inputlag: /usr/lib/librt.a
dependencies/GLFW/tests/inputlag: /usr/lib/libm.so
dependencies/GLFW/tests/inputlag: /usr/lib/libX11.so
dependencies/GLFW/tests/inputlag: dependencies/GLFW/tests/CMakeFiles/inputlag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable inputlag"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputlag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/tests/CMakeFiles/inputlag.dir/build: dependencies/GLFW/tests/inputlag
.PHONY : dependencies/GLFW/tests/CMakeFiles/inputlag.dir/build

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -P CMakeFiles/inputlag.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/tests/CMakeFiles/inputlag.dir/clean

dependencies/GLFW/tests/CMakeFiles/inputlag.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/tests/CMakeFiles/inputlag.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/GLFW/tests/CMakeFiles/inputlag.dir/depend

