# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build

# Include any dependencies generated for this target.
include CMakeFiles/tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tree.dir/flags.make

CMakeFiles/tree.dir/tree-height.cpp.o: CMakeFiles/tree.dir/flags.make
CMakeFiles/tree.dir/tree-height.cpp.o: ../tree-height.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tree.dir/tree-height.cpp.o"
	/usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tree.dir/tree-height.cpp.o -c /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/tree-height.cpp

CMakeFiles/tree.dir/tree-height.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tree.dir/tree-height.cpp.i"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/tree-height.cpp > CMakeFiles/tree.dir/tree-height.cpp.i

CMakeFiles/tree.dir/tree-height.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tree.dir/tree-height.cpp.s"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/tree-height.cpp -o CMakeFiles/tree.dir/tree-height.cpp.s

CMakeFiles/tree.dir/tree-height.cpp.o.requires:

.PHONY : CMakeFiles/tree.dir/tree-height.cpp.o.requires

CMakeFiles/tree.dir/tree-height.cpp.o.provides: CMakeFiles/tree.dir/tree-height.cpp.o.requires
	$(MAKE) -f CMakeFiles/tree.dir/build.make CMakeFiles/tree.dir/tree-height.cpp.o.provides.build
.PHONY : CMakeFiles/tree.dir/tree-height.cpp.o.provides

CMakeFiles/tree.dir/tree-height.cpp.o.provides.build: CMakeFiles/tree.dir/tree-height.cpp.o


# Object files for target tree
tree_OBJECTS = \
"CMakeFiles/tree.dir/tree-height.cpp.o"

# External object files for target tree
tree_EXTERNAL_OBJECTS =

tree.exe: CMakeFiles/tree.dir/tree-height.cpp.o
tree.exe: CMakeFiles/tree.dir/build.make
tree.exe: CMakeFiles/tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tree.dir/build: tree.exe

.PHONY : CMakeFiles/tree.dir/build

CMakeFiles/tree.dir/requires: CMakeFiles/tree.dir/tree-height.cpp.o.requires

.PHONY : CMakeFiles/tree.dir/requires

CMakeFiles/tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tree.dir/clean

CMakeFiles/tree.dir/depend:
	cd /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build /home/Andreyev/01_DS/02_Data_Structures/01_Assignment1/tree_height/build/CMakeFiles/tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tree.dir/depend
