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
CMAKE_SOURCE_DIR = "/run/media/gfif/32D0BC88D0BC53B7/CPP clang"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/run/media/gfif/32D0BC88D0BC53B7/CPP clang"

# Include any dependencies generated for this target.
include dependencies/GLFW/tests/CMakeFiles/iconify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/GLFW/tests/CMakeFiles/iconify.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/GLFW/tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/GLFW/tests/CMakeFiles/iconify.dir/flags.make

dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o: dependencies/GLFW/tests/iconify.c
dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/run/media/gfif/32D0BC88D0BC53B7/CPP clang/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o -MF CMakeFiles/iconify.dir/iconify.c.o.d -o CMakeFiles/iconify.dir/iconify.c.o -c "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests/iconify.c"

dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests/iconify.c" > CMakeFiles/iconify.dir/iconify.c.i

dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests/iconify.c" -o CMakeFiles/iconify.dir/iconify.c.s

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: dependencies/GLFW/deps/getopt.c
dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/run/media/gfif/32D0BC88D0BC53B7/CPP clang/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o -MF CMakeFiles/iconify.dir/__/deps/getopt.c.o.d -o CMakeFiles/iconify.dir/__/deps/getopt.c.o -c "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/getopt.c"

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/getopt.c" > CMakeFiles/iconify.dir/__/deps/getopt.c.i

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/getopt.c" -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/flags.make
dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: dependencies/GLFW/deps/glad_gl.c
dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: dependencies/GLFW/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/run/media/gfif/32D0BC88D0BC53B7/CPP clang/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -MF CMakeFiles/iconify.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -c "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/glad_gl.c"

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad_gl.c.i"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/glad_gl.c" > CMakeFiles/iconify.dir/__/deps/glad_gl.c.i

dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad_gl.c.s"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/deps/glad_gl.c" -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.o" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.o" \
"CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

dependencies/GLFW/tests/iconify: dependencies/GLFW/tests/CMakeFiles/iconify.dir/iconify.c.o
dependencies/GLFW/tests/iconify: dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o
dependencies/GLFW/tests/iconify: dependencies/GLFW/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o
dependencies/GLFW/tests/iconify: dependencies/GLFW/tests/CMakeFiles/iconify.dir/build.make
dependencies/GLFW/tests/iconify: dependencies/GLFW/src/libglfw3.a
dependencies/GLFW/tests/iconify: /usr/lib/libm.so
dependencies/GLFW/tests/iconify: /usr/lib/librt.a
dependencies/GLFW/tests/iconify: /usr/lib/libm.so
dependencies/GLFW/tests/iconify: /usr/lib/libX11.so
dependencies/GLFW/tests/iconify: dependencies/GLFW/tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/run/media/gfif/32D0BC88D0BC53B7/CPP clang/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable iconify"
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iconify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/GLFW/tests/CMakeFiles/iconify.dir/build: dependencies/GLFW/tests/iconify
.PHONY : dependencies/GLFW/tests/CMakeFiles/iconify.dir/build

dependencies/GLFW/tests/CMakeFiles/iconify.dir/clean:
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : dependencies/GLFW/tests/CMakeFiles/iconify.dir/clean

dependencies/GLFW/tests/CMakeFiles/iconify.dir/depend:
	cd "/run/media/gfif/32D0BC88D0BC53B7/CPP clang" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/run/media/gfif/32D0BC88D0BC53B7/CPP clang" "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" "/run/media/gfif/32D0BC88D0BC53B7/CPP clang" "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests" "/run/media/gfif/32D0BC88D0BC53B7/CPP clang/dependencies/GLFW/tests/CMakeFiles/iconify.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : dependencies/GLFW/tests/CMakeFiles/iconify.dir/depend

