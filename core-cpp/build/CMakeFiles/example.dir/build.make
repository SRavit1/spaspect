# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/santript/ImportantProjects/spaspect/core-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/santript/ImportantProjects/spaspect/core-cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example.dir/flags.make

CMakeFiles/example.dir/test.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santript/ImportantProjects/spaspect/core-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example.dir/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/test.cpp.o -c /home/santript/ImportantProjects/spaspect/core-cpp/test.cpp

CMakeFiles/example.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santript/ImportantProjects/spaspect/core-cpp/test.cpp > CMakeFiles/example.dir/test.cpp.i

CMakeFiles/example.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santript/ImportantProjects/spaspect/core-cpp/test.cpp -o CMakeFiles/example.dir/test.cpp.s

CMakeFiles/example.dir/test.cpp.o.requires:

.PHONY : CMakeFiles/example.dir/test.cpp.o.requires

CMakeFiles/example.dir/test.cpp.o.provides: CMakeFiles/example.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/example.dir/test.cpp.o.provides

CMakeFiles/example.dir/test.cpp.o.provides.build: CMakeFiles/example.dir/test.cpp.o


CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o: /usr/local/include/cppflow/src/Model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santript/ImportantProjects/spaspect/core-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o -c /usr/local/include/cppflow/src/Model.cpp

CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/include/cppflow/src/Model.cpp > CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.i

CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/include/cppflow/src/Model.cpp -o CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.s

CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.requires:

.PHONY : CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.requires

CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.provides: CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.requires
	$(MAKE) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.provides.build
.PHONY : CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.provides

CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.provides.build: CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o


CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o: /usr/local/include/cppflow/src/Tensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santript/ImportantProjects/spaspect/core-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o -c /usr/local/include/cppflow/src/Tensor.cpp

CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/include/cppflow/src/Tensor.cpp > CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.i

CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/include/cppflow/src/Tensor.cpp -o CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.s

CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.requires:

.PHONY : CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.requires

CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.provides: CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.requires
	$(MAKE) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.provides.build
.PHONY : CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.provides

CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.provides.build: CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o


# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/test.cpp.o" \
"CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o" \
"CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

example: CMakeFiles/example.dir/test.cpp.o
example: CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o
example: CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o
example: CMakeFiles/example.dir/build.make
example: /usr/local/lib/libtensorflow.so
example: CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/santript/ImportantProjects/spaspect/core-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example.dir/build: example

.PHONY : CMakeFiles/example.dir/build

CMakeFiles/example.dir/requires: CMakeFiles/example.dir/test.cpp.o.requires
CMakeFiles/example.dir/requires: CMakeFiles/example.dir/usr/local/include/cppflow/src/Model.cpp.o.requires
CMakeFiles/example.dir/requires: CMakeFiles/example.dir/usr/local/include/cppflow/src/Tensor.cpp.o.requires

.PHONY : CMakeFiles/example.dir/requires

CMakeFiles/example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example.dir/clean

CMakeFiles/example.dir/depend:
	cd /home/santript/ImportantProjects/spaspect/core-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/santript/ImportantProjects/spaspect/core-cpp /home/santript/ImportantProjects/spaspect/core-cpp /home/santript/ImportantProjects/spaspect/core-cpp/build /home/santript/ImportantProjects/spaspect/core-cpp/build /home/santript/ImportantProjects/spaspect/core-cpp/build/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example.dir/depend

