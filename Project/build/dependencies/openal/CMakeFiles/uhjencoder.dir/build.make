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
include dependencies/openal/CMakeFiles/uhjencoder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/openal/CMakeFiles/uhjencoder.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/openal/CMakeFiles/uhjencoder.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/openal/CMakeFiles/uhjencoder.dir/flags.make

dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o: dependencies/openal/CMakeFiles/uhjencoder.dir/flags.make
dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o: /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/utils/uhjencoder.cpp
dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o: dependencies/openal/CMakeFiles/uhjencoder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o -MF CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o.d -o CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o -c /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/utils/uhjencoder.cpp

dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.i"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/utils/uhjencoder.cpp > CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.i

dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.s"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal/utils/uhjencoder.cpp -o CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.s

# Object files for target uhjencoder
uhjencoder_OBJECTS = \
"CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o"

# External object files for target uhjencoder
uhjencoder_EXTERNAL_OBJECTS =

dependencies/openal/uhjencoder: dependencies/openal/CMakeFiles/uhjencoder.dir/utils/uhjencoder.cpp.o
dependencies/openal/uhjencoder: dependencies/openal/CMakeFiles/uhjencoder.dir/build.make
dependencies/openal/uhjencoder: dependencies/openal/libalcommon.a
dependencies/openal/uhjencoder: /usr/lib/libsndfile.so
dependencies/openal/uhjencoder: dependencies/openal/CMakeFiles/uhjencoder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uhjencoder"
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uhjencoder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/openal/CMakeFiles/uhjencoder.dir/build: dependencies/openal/uhjencoder
.PHONY : dependencies/openal/CMakeFiles/uhjencoder.dir/build

dependencies/openal/CMakeFiles/uhjencoder.dir/clean:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal && $(CMAKE_COMMAND) -P CMakeFiles/uhjencoder.dir/cmake_clean.cmake
.PHONY : dependencies/openal/CMakeFiles/uhjencoder.dir/clean

dependencies/openal/CMakeFiles/uhjencoder.dir/depend:
	cd /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal /run/media/gfif/32D0BC88D0BC53B7/Engine-project-/Project/build/dependencies/openal/CMakeFiles/uhjencoder.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dependencies/openal/CMakeFiles/uhjencoder.dir/depend

