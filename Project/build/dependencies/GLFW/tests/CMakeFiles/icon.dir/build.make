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
include dependencies/GLFW/tests/CMakeFiles/icon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/tests/CMakeFiles/icon.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/tests/CMakeFiles/icon.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/tests/CMakeFiles/icon.dir/flags.make

dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o: dependencies/GLFW/tests/CMakeFiles/icon.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/icon.c
dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o: dependencies/GLFW/tests/CMakeFiles/icon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o -MF CMakeFiles/icon.dir/icon.c.o.d -o CMakeFiles/icon.dir/icon.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/icon.c

dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icon.dir/icon.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/icon.c > CMakeFiles/icon.dir/icon.c.i

dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icon.dir/icon.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/icon.c -o CMakeFiles/icon.dir/icon.c.s

dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/icon.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/icon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o -MF CMakeFiles/icon.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/icon.dir/__/deps/glad_gl.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c

dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/icon.dir/__/deps/glad_gl.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c > CMakeFiles/icon.dir/__/deps/glad_gl.c.i

dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/icon.dir/__/deps/glad_gl.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c -o CMakeFiles/icon.dir/__/deps/glad_gl.c.s

# Object files for target icon
icon_OBJECTS = \
"CMakeFiles/icon.dir/icon.c.o" \
"CMakeFiles/icon.dir/__/deps/glad_gl.c.o"

# External object files for target icon
icon_EXTERNAL_OBJECTS =

dependencies/GLFW/tests/icon: dependencies/GLFW/tests/CMakeFiles/icon.dir/icon.c.o
dependencies/GLFW/tests/icon: dependencies/GLFW/tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o
dependencies/GLFW/tests/icon: dependencies/GLFW/tests/CMakeFiles/icon.dir/build.make
dependencies/GLFW/tests/icon: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/tests/icon: /usr/lib/libm.so
dependencies/GLFW/tests/icon: /usr/lib/librt.a
dependencies/GLFW/tests/icon: /usr/lib/libm.so
dependencies/GLFW/tests/icon: /usr/lib/libX11.so
dependencies/GLFW/tests/icon: dependencies/GLFW/tests/CMakeFiles/icon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable icon"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/tests/CMakeFiles/icon.dir/build: dependencies/GLFW/tests/icon
.PHONY : dependencies/GLFW/tests/CMakeFiles/icon.dir/build

dependencies/GLFW/tests/CMakeFiles/icon.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -P CMakeFiles/icon.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/tests/CMakeFiles/icon.dir/clean

dependencies/GLFW/tests/CMakeFiles/icon.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests/CMakeFiles/icon.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/GLFW/tests/CMakeFiles/icon.dir/depend
