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
include dependencies/GLFW/examples/CMakeFiles/offscreen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/examples/CMakeFiles/offscreen.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/examples/CMakeFiles/offscreen.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/examples/CMakeFiles/offscreen.dir/flags.make

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/flags.make
dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/examples/offscreen.c
dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o -MF CMakeFiles/offscreen.dir/offscreen.c.o.d -o CMakeFiles/offscreen.dir/offscreen.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/examples/offscreen.c

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/offscreen.dir/offscreen.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/examples/offscreen.c > CMakeFiles/offscreen.dir/offscreen.c.i

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/offscreen.dir/offscreen.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/examples/offscreen.c -o CMakeFiles/offscreen.dir/offscreen.c.s

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/flags.make
dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o -MF CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c > CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/deps/glad_gl.c -o CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s

# Object files for target offscreen
offscreen_OBJECTS = \
"CMakeFiles/offscreen.dir/offscreen.c.o" \
"CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o"

# External object files for target offscreen
offscreen_EXTERNAL_OBJECTS =

dependencies/GLFW/examples/offscreen: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/offscreen.c.o
dependencies/GLFW/examples/offscreen: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o
dependencies/GLFW/examples/offscreen: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/build.make
dependencies/GLFW/examples/offscreen: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/examples/offscreen: /usr/lib/libm.so
dependencies/GLFW/examples/offscreen: /usr/lib/librt.a
dependencies/GLFW/examples/offscreen: /usr/lib/libm.so
dependencies/GLFW/examples/offscreen: /usr/lib/libX11.so
dependencies/GLFW/examples/offscreen: dependencies/GLFW/examples/CMakeFiles/offscreen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable offscreen"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/offscreen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/examples/CMakeFiles/offscreen.dir/build: dependencies/GLFW/examples/offscreen
.PHONY : dependencies/GLFW/examples/CMakeFiles/offscreen.dir/build

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples && $(CMAKE_COMMAND) -P CMakeFiles/offscreen.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/examples/CMakeFiles/offscreen.dir/clean

dependencies/GLFW/examples/CMakeFiles/offscreen.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/dependencies/GLFW/examples /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Cmake/build/dependencies/GLFW/examples/CMakeFiles/offscreen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/GLFW/examples/CMakeFiles/offscreen.dir/depend

