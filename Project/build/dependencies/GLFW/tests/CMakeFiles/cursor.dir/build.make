# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
include dependencies/GLFW/tests/CMakeFiles/cursor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/tests/CMakeFiles/cursor.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/tests/CMakeFiles/cursor.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/tests/CMakeFiles/cursor.dir/flags.make

dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o: dependencies/GLFW/tests/CMakeFiles/cursor.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/cursor.c
dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o: dependencies/GLFW/tests/CMakeFiles/cursor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o -MF CMakeFiles/cursor.dir/cursor.c.o.d -o CMakeFiles/cursor.dir/cursor.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/cursor.c

dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cursor.dir/cursor.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/cursor.c > CMakeFiles/cursor.dir/cursor.c.i

dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cursor.dir/cursor.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests/cursor.c -o CMakeFiles/cursor.dir/cursor.c.s

dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/cursor.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/cursor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o -MF CMakeFiles/cursor.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/cursor.dir/__/deps/glad_gl.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c

dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cursor.dir/__/deps/glad_gl.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c > CMakeFiles/cursor.dir/__/deps/glad_gl.c.i

dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cursor.dir/__/deps/glad_gl.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c -o CMakeFiles/cursor.dir/__/deps/glad_gl.c.s

# Object files for target cursor
cursor_OBJECTS = \
"CMakeFiles/cursor.dir/cursor.c.o" \
"CMakeFiles/cursor.dir/__/deps/glad_gl.c.o"

# External object files for target cursor
cursor_EXTERNAL_OBJECTS =

dependencies/GLFW/tests/cursor: dependencies/GLFW/tests/CMakeFiles/cursor.dir/cursor.c.o
dependencies/GLFW/tests/cursor: dependencies/GLFW/tests/CMakeFiles/cursor.dir/__/deps/glad_gl.c.o
dependencies/GLFW/tests/cursor: dependencies/GLFW/tests/CMakeFiles/cursor.dir/build.make
dependencies/GLFW/tests/cursor: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/tests/cursor: /usr/lib/libm.so
dependencies/GLFW/tests/cursor: /usr/lib/librt.a
dependencies/GLFW/tests/cursor: /usr/lib/libm.so
dependencies/GLFW/tests/cursor: /usr/lib/libX11.so
dependencies/GLFW/tests/cursor: dependencies/GLFW/tests/CMakeFiles/cursor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable cursor"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cursor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/tests/CMakeFiles/cursor.dir/build: dependencies/GLFW/tests/cursor
.PHONY : dependencies/GLFW/tests/CMakeFiles/cursor.dir/build

dependencies/GLFW/tests/CMakeFiles/cursor.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests && $(CMAKE_COMMAND) -P CMakeFiles/cursor.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/tests/CMakeFiles/cursor.dir/clean

dependencies/GLFW/tests/CMakeFiles/cursor.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/tests/CMakeFiles/cursor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/GLFW/tests/CMakeFiles/cursor.dir/depend

