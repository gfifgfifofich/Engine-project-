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
include dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/flags.make

dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o: dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/flags.make
dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/glew/src/glewinfo.c
dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o: dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o -MF CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o.d -o CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/glew/src/glewinfo.c

dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/glew/src/glewinfo.c > CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i

dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/glew/src/glewinfo.c -o CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s

# Object files for target glewinfo
glewinfo_OBJECTS = \
"CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o"

# External object files for target glewinfo
glewinfo_EXTERNAL_OBJECTS =

bin/glewinfo: dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o
bin/glewinfo: dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/build.make
bin/glewinfo: lib/libGLEW.a
bin/glewinfo: /usr/lib/libSM.so
bin/glewinfo: /usr/lib/libICE.so
bin/glewinfo: /usr/lib/libX11.so
bin/glewinfo: /usr/lib/libXext.so
bin/glewinfo: /usr/lib/libOpenGL.so
bin/glewinfo: /usr/lib/libGLX.so
bin/glewinfo: /usr/lib/libGLU.so
bin/glewinfo: /usr/lib/libSM.so
bin/glewinfo: /usr/lib/libICE.so
bin/glewinfo: /usr/lib/libX11.so
bin/glewinfo: /usr/lib/libXext.so
bin/glewinfo: dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../../bin/glewinfo"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glewinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/build: bin/glewinfo
.PHONY : dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/build

dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake && $(CMAKE_COMMAND) -P CMakeFiles/glewinfo.dir/cmake_clean.cmake
.PHONY : dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/clean

dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/glew/build/cmake /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/glew/build/cmake/CMakeFiles/glewinfo.dir/depend

