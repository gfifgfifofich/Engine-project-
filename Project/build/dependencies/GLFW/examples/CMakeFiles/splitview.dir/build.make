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
include dependencies/GLFW/examples/CMakeFiles/splitview.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/examples/CMakeFiles/splitview.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/examples/CMakeFiles/splitview.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/examples/CMakeFiles/splitview.dir/flags.make

dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o: dependencies/GLFW/examples/CMakeFiles/splitview.dir/flags.make
dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/examples/splitview.c
dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o: dependencies/GLFW/examples/CMakeFiles/splitview.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o -MF CMakeFiles/splitview.dir/splitview.c.o.d -o CMakeFiles/splitview.dir/splitview.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/examples/splitview.c

dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/splitview.dir/splitview.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/examples/splitview.c > CMakeFiles/splitview.dir/splitview.c.i

dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/splitview.dir/splitview.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/examples/splitview.c -o CMakeFiles/splitview.dir/splitview.c.s

dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o: dependencies/GLFW/examples/CMakeFiles/splitview.dir/flags.make
dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o: dependencies/GLFW/examples/CMakeFiles/splitview.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o -MF CMakeFiles/splitview.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/splitview.dir/__/deps/glad_gl.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c

dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/splitview.dir/__/deps/glad_gl.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c > CMakeFiles/splitview.dir/__/deps/glad_gl.c.i

dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/splitview.dir/__/deps/glad_gl.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/deps/glad_gl.c -o CMakeFiles/splitview.dir/__/deps/glad_gl.c.s

# Object files for target splitview
splitview_OBJECTS = \
"CMakeFiles/splitview.dir/splitview.c.o" \
"CMakeFiles/splitview.dir/__/deps/glad_gl.c.o"

# External object files for target splitview
splitview_EXTERNAL_OBJECTS =

dependencies/GLFW/examples/splitview: dependencies/GLFW/examples/CMakeFiles/splitview.dir/splitview.c.o
dependencies/GLFW/examples/splitview: dependencies/GLFW/examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.o
dependencies/GLFW/examples/splitview: dependencies/GLFW/examples/CMakeFiles/splitview.dir/build.make
dependencies/GLFW/examples/splitview: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/examples/splitview: /usr/lib/libm.so
dependencies/GLFW/examples/splitview: /usr/lib/librt.a
dependencies/GLFW/examples/splitview: /usr/lib/libm.so
dependencies/GLFW/examples/splitview: /usr/lib/libX11.so
dependencies/GLFW/examples/splitview: dependencies/GLFW/examples/CMakeFiles/splitview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable splitview"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/splitview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/examples/CMakeFiles/splitview.dir/build: dependencies/GLFW/examples/splitview
.PHONY : dependencies/GLFW/examples/CMakeFiles/splitview.dir/build

dependencies/GLFW/examples/CMakeFiles/splitview.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples && $(CMAKE_COMMAND) -P CMakeFiles/splitview.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/examples/CMakeFiles/splitview.dir/clean

dependencies/GLFW/examples/CMakeFiles/splitview.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/GLFW/examples /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/GLFW/examples/CMakeFiles/splitview.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/GLFW/examples/CMakeFiles/splitview.dir/depend

